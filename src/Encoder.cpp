#include "Encoder.hpp"

Encoder::Encoder(const size_t _constraint, const std::vector<std::vector<bool>> &polys) : constraint(_constraint) {

  if (polys.size() == 0 || _constraint == 0 || _constraint > MEM)
    throw std::invalid_argument("Bad polynom sz (not 1 - 32)");

  register_mask = (1U << (constraint - 1)) - 1;
  for (const auto &poly : polys) {
    if (poly.size() != constraint) {
      throw std::invalid_argument("Polynoms have different sz");
    }

    std::bitset<MEM> mask = 0;

    for (uint8_t i = 0; i < constraint; ++i) {
      mask[MEM - 1 - i] = poly[i];
    }

    polynom_masks.push_back(mask);
  }
}

void Encoder::update_state(const bool bit) {
  shift_register >>= 1;
  shift_register |= (static_cast<int32_t>(bit) << (MEM - 1));
}

void Encoder::reset() {
  shift_register = 0U;
}

std::vector<bool> Encoder::encode_bits(const std::vector<bool> &bits) noexcept {
  std::vector<bool> output;
  for (auto elem : bits) {
    update_state(elem);
    for (const auto &mask : polynom_masks) {
      std::bitset<MEM> result = shift_register & mask;
      output.push_back(result.count() % 2);
    }
  }

  return std::move(output);
}

std::vector<bool> operator>>(const std::vector<bool> &input, Encoder &encoder) noexcept {
  return encoder.encode_bits(input);
};
