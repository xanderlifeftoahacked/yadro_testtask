#pragma once
#include "Channel.hpp"
#include "Decoder.hpp"
#include "Encoder.hpp"
#include <cassert>
#include <cstdlib>
#include <vector>

void operator>>(const std::vector<bool> &from, std::vector<bool> &to) {
  to = from;
}

namespace utils {
std::vector<bool> generate_message(size_t sz) {
  std::vector<bool> bits(sz);
  for (size_t i = 0; i < bits.size(); ++i) {
    bits[i] = std::rand() & 2;
  }

  return bits;
}

size_t count_diff(const std::vector<bool> &v1, const std::vector<bool> &v2) {
  size_t ans = 0;

  for (size_t i = 0; i < std::min(v1.size(), v2.size()); ++i) {
    if (v1[i] != v2[i])
      ++ans;
  }
  return ans + std::max(v1.size(), v2.size()) - std::min(v1.size(), v2.size());
}

std::pair<std::vector<double>, std::vector<double>>
test_codec(Encoder &coder, Decoder &decoder, std::mt19937 &dev, size_t msg_sz,
           size_t samples) {

  std::vector<double> x, y;

  for (size_t proc = 1; proc <= samples; ++proc) {
    Channel channel(1.f * proc / samples, dev);
    std::vector<bool> decoded, message = utils::generate_message(msg_sz);
    std::vector<bool> after_channel, after_coder;

    message >> coder >> after_coder;
    after_coder >> channel >> after_channel;
    after_channel >> decoder >> decoded;

    float real_prob = 1.f * utils::count_diff(after_coder, after_channel) /
                      after_coder.size();
    float error_rate =
        1.f * utils::count_diff(message, decoded) / message.size();

    x.emplace_back(real_prob);
    y.emplace_back(error_rate);
  }

  return {x, y};
}
} // namespace utils
