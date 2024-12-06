#pragma once

#include <vector>
#include <unordered_map>

class Graph 
{
public:
    Graph() = default;
    void add_edge(int u, int v, long long weight);
    void print_graph();
    int get_edges();
    int get_nodes();
    std::pair<long long, long long> get_min_max_weight();
    void set_properties(int V, int E, long long weight_max, long long weight_min);
    std::vector<long long> dijkstra(int source);
    std::vector<long long> dial(int source);
    std::vector<long long> radix(int source);

private:
    std::unordered_map<int, std::vector<std::pair<int, long long>>> list;
    int V, E;
    long long weight_max, weight_min;
};