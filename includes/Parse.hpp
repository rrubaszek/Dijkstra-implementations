#pragma once 

#include "Graph.hpp"

#include <string>
#include <vector>

class Parse
{
public:
    Parse() = default;
    std::string find_file(const std::string& filename);
    std::string parse_data(const std::string& filename, Graph& g);
    std::vector<int> parse_input(const std::string& filename);
    std::vector<std::pair<int, int>> parse_input_pairs(const std::string& filename);
};