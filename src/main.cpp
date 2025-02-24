#include "Channel.hpp"
#include "Encoder.hpp"
#include "Decoder.hpp"
#include "utils.hpp"

int main() {
  Encoder coder(7, {{1, 1, 0, 1, 1, 0, 1}, {1, 0, 0, 1, 1, 1, 1}});
  //  Decoder decoder(7, {{1, 1, 0, 1, 1, 0, 1}, {1, 0, 0, 1, 1, 1, 1}});

  Channel channel(0.05f);

  std::vector<bool> bits = {1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0};

  std::vector<bool> decoded;

  //  bits >> coder >> channel >> decoder >> decoded;

  for (auto bit : decoded) {
    std::cout << bit << ' ';
  }
  std::cout << std::endl;

  return 0;
}
