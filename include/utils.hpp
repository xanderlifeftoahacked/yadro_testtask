#pragma once
#include <vector>
#include <iostream>

void operator>>(const std::vector<bool>& from, std::vector<bool>& to) {
  to = from;
}
