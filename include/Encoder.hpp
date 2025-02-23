#pragma once
#include <bitset>
#include <cstdint>
#include <stdexcept>
#include <vector>

class Encoder {
private:
  static constexpr size_t MEM = 32;
  std::bitset<MEM> shift_register;
  std::vector<std::bitset<MEM>> polynom_masks;
  uint32_t register_mask;
  uint8_t constraint;
  void update_state(const bool);

public:
  Encoder(const size_t, const std::vector<std::vector<bool>> &);
  void reset();
  std::vector<bool> encode_bits(const std::vector<bool> &) noexcept;
};
