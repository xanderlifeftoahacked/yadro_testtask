#include "Channel.hpp"
#include <stdexcept>

Channel::Channel(double _probability, std::mt19937 &gen)
    : probability{_probability}, generator{gen} {
  if (_probability < 0.0 || _probability > 1.0) {
    throw std::invalid_argument("Bad probability (should be in [0, 1])");
  }
}

std::vector<bool> Channel::add_noise(const std::vector<bool> &input) noexcept {
  std::vector<bool> output;
  output.reserve(input.size());

  for (bool bit : input) {
    if (distribution(generator) < probability)
      output.emplace_back(!bit);
    else
      output.emplace_back(bit);
  }

  return output;
};

std::vector<bool> operator>>(const std::vector<bool> &input,
                             Channel &channel) noexcept {
  return channel.add_noise(input);
}
