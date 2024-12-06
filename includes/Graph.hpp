#pragma once

#include <vector>
#include <unordered_map>

class Graph 
{
private:
    int V, E;
    long long weight_max, weight_min;
    std::unordered_map<int, std::vector<std::pair<int, long long>>> list;
    
public:
    Graph() = default;
    int get_edges();
    int get_nodes();
    std::pair<long long, long long> get_min_max_weight();

    void set_properties(int V, int E, long long weight_max, long long weight_min);

    void add_edge(int u, int v, long long weight);
    
    std::vector<long long> dijkstra(int source);
    std::vector<long long> dial(int source);
    std::vector<long long> radix(int source);
};