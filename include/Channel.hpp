#pragma once
#include <random>
#include <stdexcept>

class Channel {
 private:
  double probability;
  std::mt19937 generator;
  std::uniform_real_distribution<double> distribution;

 public:
  Channel(double);
  std::vector<bool> add_noise(const std::vector<bool> &) noexcept;
};
std::vector<bool> operator>>(const std::vector<bool> &, Channel &) noexcept;
