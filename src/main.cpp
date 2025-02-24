#include "Decoder.hpp"
#include "Encoder.hpp"
#include "gnuplot-iostream.h"
#include "utils.hpp"

#include <cstdlib>
#include <iostream>
#include <random>
#include <tuple>

int main() {
  std::random_device rd;
  std::mt19937 dev(rd());

  Gnuplot plot;
  plot << "set size ratio -1\n"
       << "set xrange [0:1]\n"
       << "set yrange [0:1]\n";

  plot << "plot '-' with linespoints title 'error rate (LTE)',  "
       << "'-' with linespoints title 'error rate (Cassini)'\n";

  std::cout << "LTE POLYNOMS (size = 7)" << std::endl;
  {
    Encoder coder(LTE_constraint, LTE_gens);
    Decoder decoder(LTE_constraint, LTE_gens);
    std::cout << "Measuring... (1000 bits msg, 1000 samples)" << std::endl;
    auto [x, y] = utils::test_codec(coder, decoder, dev, 1000, 1000);
    plot.send1d(std::make_tuple(x, y));
  }

  std::cout << "CASSINI POLYNOMS (size = 15)" << std::endl;
  {
    Encoder coder(CASSINI_constraint, CASSINI_gens);
    Decoder decoder(CASSINI_constraint, CASSINI_gens);
    std::cout << "Measuring... (1000 bits msg, 200 samples)" << std::endl;
    auto [x, y] = utils::test_codec(coder, decoder, dev, 1000, 200);
    plot.send1d(std::make_tuple(x, y));
  }

  std::cout << "Press something to exit..." << std::endl;
  std::cin.get();

  return 0;
}
