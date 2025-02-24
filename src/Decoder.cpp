#include "Decoder.hpp"
#include <algorithm>
#include <stdexcept>

void Decoder::init_polynoms(const std::vector<std::vector<bool>> &gen) {
  if (gen.size() == 0 || constraint == 0 || constraint > MEM)
    throw std::invalid_argument("Bad polynom sz (not 1 - 32)");

  for (const auto &poly : gen) {
    if (poly.size() != constraint)
      throw std::invalid_argument("Polynoms have different sz");
  }

  for (const auto &v : gen) {
    std::bitset<MEM> bs;
    for (uint8_t i = 0; i < constraint; ++i)
      bs[constraint - 1 - i] = v[i];
    polynoms.emplace_back(bs);
  }
}

void Decoder::init_transitions() noexcept {
  transitions.resize(num_states);

  for (state_t s = 0; s < num_states; ++s) {
    std::array<transition, 2> trans_arr;

    for (int input = 0; input < 2; ++input) {
      state_t full = (static_cast<state_t>(input) << (constraint - 1)) | s;
      state_t next_state = full >> 1;
      uint32_t out = 0;

      for (size_t i = 0; i < num_outputs; ++i) {
        auto poly = polynoms[i].to_ulong();
        auto bits = full & poly;
        bool parity = (std::bitset<MEM>(bits).count() & 1) != 0;
        if (parity)
          out |= (1u << i);
      }

      trans_arr[input] = {next_state, out};
    }

    transitions[s] = trans_arr;
  }
}

uint32_t Decoder::branch_metric(uint32_t received,
                                uint32_t expected) const noexcept {
  uint32_t diff = received ^ expected;
  std::bitset<32> bs(diff);
  return bs.count();
}

void Decoder::update_metrics(
    const std::vector<uint32_t> &rec,
    std::vector<std::vector<uint32_t>> &metrics,
    std::vector<std::vector<trace>> &traceback) const noexcept {
  size_t steps = rec.size();
  metrics[0][0] = 0;

  for (size_t t = 0; t < steps; ++t) {
    for (state_t s = 0; s < num_states; ++s) {
      if (metrics[t][s] == INF)
        continue;

      for (int input = 0; input < 2; ++input) {
        const transition &trans = transitions[s][input];
        state_t ns = trans.next_state;

        uint32_t candidate =
            metrics[t][s] + branch_metric(rec[t], trans.output);
        if (candidate < metrics[t + 1][ns]) {
          metrics[t + 1][ns] = candidate;
          traceback[t + 1][ns] = {s, static_cast<bool>(input)};
        }
      }
    }
  }
}

Decoder::state_t
Decoder::get_best_state(const std::vector<std::vector<uint32_t>> &metrics,
                        size_t steps) const noexcept {
  state_t best_state = 0;
  uint32_t best_metric = INF;

  for (state_t s = 0; s < num_states; ++s) {
    if (metrics[steps][s] < best_metric) {
      best_metric = metrics[steps][s];
      best_state = s;
    }
  }

  return best_state;
}

std::vector<bool>
Decoder::traceback_decode(const std::vector<std::vector<trace>> &traceback,
                          state_t best_state, size_t steps) const noexcept {
  std::vector<bool> decoded;
  decoded.reserve(steps);
  state_t cur_state = best_state;

  for (size_t t = steps; t > 0; --t) {
    trace tr = traceback[t][cur_state];
    decoded.emplace_back(tr.input);
    cur_state = tr.prev;
  }

  std::reverse(decoded.begin(), decoded.end());
  return decoded;
}

std::vector<uint32_t>
Decoder::extract_received(const std::vector<bool> &encoded) const noexcept {
  size_t steps = encoded.size() / num_outputs;
  std::vector<uint32_t> rec(steps, 0);

  for (size_t t = 0; t < steps; ++t) {
    uint32_t r = 0;
    for (size_t i = 0; i < num_outputs; ++i) {
      if (encoded[t * num_outputs + i])
        r |= (1u << i);
    }
    rec[t] = r;
  }

  return rec;
}

Decoder::Decoder(uint8_t k, const std::vector<std::vector<bool>> &gen)
    : constraint(k), num_outputs(gen.size()),
      num_states(1 << (constraint - 1)) {
  init_polynoms(gen);
  init_transitions();
}

std::vector<bool>
Decoder::decode(const std::vector<bool> &encoded) const noexcept {
  size_t steps = encoded.size() / num_outputs;
  std::vector<uint32_t> rec = extract_received(encoded);
  std::vector<std::vector<uint32_t>> metrics(
      steps + 1, std::vector<uint32_t>(num_states, INF));
  std::vector<std::vector<trace>> traceback(
      steps + 1, std::vector<trace>(num_states, {0, false}));
  update_metrics(rec, metrics, traceback);
  state_t best_state = get_best_state(metrics, steps);
  return traceback_decode(traceback, best_state, steps);
}

std::vector<bool> operator>>(const std::vector<bool> &input,
                             Decoder &decoder) noexcept {
  return decoder.decode(input);
}
