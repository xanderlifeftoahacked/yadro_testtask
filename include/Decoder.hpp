#pragma once

#include "Common.hpp"
#include <array>
#include <bitset>
#include <cstdint>
#include <limits>

class Decoder {
public:
  using state_t = uint16_t;
  struct transition {
    state_t next_state;
    uint32_t output;
  };

  Decoder(uint8_t k, const std::vector<std::vector<bool>> &gen);
  std::vector<bool> decode(const std::vector<bool> &encoded) const noexcept;

private:
  struct trace {
    state_t prev;
    bool input;
  };

  static constexpr uint32_t INF = std::numeric_limits<uint32_t>::max();
  uint8_t constraint;
  size_t num_outputs;
  size_t num_states;
  std::vector<std::bitset<MEM>> polynoms;
  std::vector<std::array<transition, 2>> transitions;

  void init_polynoms(const std::vector<std::vector<bool>> &gen);
  void init_transitions() noexcept;
  uint32_t branch_metric(uint32_t received, uint32_t expected) const noexcept;
  void
  update_metrics(const std::vector<uint32_t> &rec,
                 std::vector<std::vector<uint32_t>> &metrics,
                 std::vector<std::vector<trace>> &traceback) const noexcept;
  state_t get_best_state(const std::vector<std::vector<uint32_t>> &metrics,
                         size_t steps) const noexcept;
  std::vector<bool>
  traceback_decode(const std::vector<std::vector<trace>> &traceback,
                   state_t best_state, size_t steps) const noexcept;
  std::vector<uint32_t>
  extract_received(const std::vector<bool> &encoded) const noexcept;
};

std::vector<bool> operator>>(const std::vector<bool> &input,
                             Decoder &decoder) noexcept;
