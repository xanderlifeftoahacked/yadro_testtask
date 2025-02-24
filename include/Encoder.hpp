#pragma once
#include "Common.hpp"
#include <bitset>
#include <cstdint>
#include <vector>

class Encoder {
private:
  std::bitset<MEM> shift_register;
  std::vector<std::bitset<MEM>> polynoms;
  const uint8_t constraint;
  void update_state(const bool);

public:
  Encoder(const size_t, const std::vector<std::vector<bool>> &);
  void reset();
  std::vector<bool> encode_bits(const std::vector<bool> &) noexcept;
};

std::vector<bool> operator>>(const std::vector<bool> &, Encoder &) noexcept;
