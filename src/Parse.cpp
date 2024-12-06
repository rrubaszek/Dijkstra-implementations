#include "Parse.hpp"

#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <filesystem>
#include <unordered_map>

std::string Parse::find_file(const std::string& filename)
{
    auto path = std::filesystem::current_path();
    std::filesystem::recursive_directory_iterator iter(path);
    std::filesystem::path target_file(filename);

    for (; iter != std::filesystem::recursive_directory_iterator(); ++iter) 
    {
        if (iter->path().filename() == target_file.filename()) 
        {
            return iter->path().string();
        }
    }
    return std::string();
}

std::string Parse::parse_data(const std::string& filename, Graph& g)
{
    std::ifstream in_file(filename);
    if (!in_file.is_open()) 
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        exit(1);
    }

    int u, v, E, V;
    long long weight;
    long long weight_min = std::numeric_limits<int>::max();
    long long weight_max = -1;
    char type;
    std::string line, problem;
    while (std::getline(in_file, line)) 
    {
        std::istringstream iss(line);

        if (line[0] == 'p') 
        {
            iss >> type >> problem >> V >> E;             
        }

        if (line[0] == 'a') 
        {
            iss >> type >> u >> v >> weight;
            weight_max = std::max(weight, weight_max);
            weight_min = std::min(weight, weight_min);
            g.add_edge(u, v, weight);
        }
    }

    assert(V > 0 && E > 0 && weight_max > -1);

    g.set_properties(V, E, weight_max, weight_min);

    in_file.close();

    return (problem + " " + std::to_string(V) + " " + std::to_string(E) + " ");
}

std::vector<int> Parse::parse_input(const std::string& filename)
{
    std::vector<int> sources;
    std::ifstream in_file(filename);
    if (!in_file.is_open()) 
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        exit(1);
    }

    int source;
    char type;
    std::string line;
    while (std::getline(in_file, line)) 
    {
        std::istringstream iss(line);
        if (line[0] == 's') 
        {
            iss >> type >> source;
            sources.push_back(source);
        } 
    }

    assert(sources.size() != 0);

    in_file.close();

    return sources;
}

std::vector<std::pair<int, int>> Parse::parse_input_pairs(const std::string& filename)
{
    std::vector<std::pair<int, int>> sources;
    std::ifstream in_file(filename);
    if (!in_file.is_open()) 
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        exit(1);
    }

    int source, dest;
    char type;
    std::string line;
    while (std::getline(in_file, line)) 
    {
        std::istringstream iss(line);
        if (line[0] == 'q') 
        {
            iss >> type >> source >> dest;
            sources.emplace_back(source, dest);
        }
    }

    assert(sources.size() != 0);

    in_file.close();

    return sources;
}