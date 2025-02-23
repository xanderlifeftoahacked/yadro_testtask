#include "Encoder.hpp"

int main() {
  Encoder coder(1, {{1}});

  std::vector<bool> bits = {0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1};
  auto out = coder.encode_bits(bits);

  return 0;
}
