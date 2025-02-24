#pragma once
#include <cstddef>
#include <vector>

constexpr inline size_t MEM = 16;
const inline size_t LTE_constraint = 7;
const inline std::vector<std::vector<bool>> LTE_gens = {
    {1, 0, 1, 1, 0, 1, 1}, {1, 1, 1, 0, 1, 0, 1}, {1, 1, 1, 1, 0, 0, 1}};

const inline size_t CASSINI_constraint = 15;
const inline std::vector<std::vector<bool>> CASSINI_gens = {
    {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1},
    {1, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1},
    {1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1},
    {1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1},
    {1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1},
    {1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1}};
