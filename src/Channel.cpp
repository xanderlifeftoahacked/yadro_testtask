#include "Channel.hpp"
#include <iostream>

Channel::Channel(double _probability) : probability{_probability}, generator{std::random_device{}()} {
  if (_probability < 0.0 || _probability > 1.0) {
    throw std::invalid_argument("Bad probability (should be in [0, 1])");
  }
}

std::vector<bool> Channel::add_noise(const std::vector<bool> &input) noexcept {
  std::vector<bool> output;
  output.reserve(input.size());

  for (bool bit : input) {
    if (distribution(generator) < probability) {
      output.push_back(!bit);
      std::cout << "ERROR!\n";
    } else {
      output.push_back(bit);
    }
  }
  return std::move(output);
};

std::vector<bool> operator>>(const std::vector<bool> &input, Channel &channel) noexcept {
  return std::move(channel.add_noise(input));
}
