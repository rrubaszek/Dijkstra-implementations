#include "Graph.hpp"
#include "RadixHeap.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <list>
#include <limits>
#include <queue>

#include <bits/stdc++.h>

void Graph::set_properties(int V, int E, long long weight_max, long long weight_min)
{
    this->V = V;
    this->E = E;
    this->weight_max = weight_max;
    this->weight_min = weight_min;
}

int Graph::get_edges()
{
    return E;
}

int Graph::get_nodes()
{
    return V;
}

std::pair<long long, long long> Graph::get_min_max_weight()
{
    return std::make_pair(weight_min, weight_max);
}

void Graph::add_edge(int u, int v, long long weight) 
{
    list[u].emplace_back(v, weight);
}

std::vector<long long> Graph::dijkstra(int source)
{
    if (source < 1 || source > V) 
        throw std::out_of_range("Source node out of bounds");

    std::priority_queue<std::pair<long long, int>, 
                        std::vector<std::pair<long long, int>>, 
                        std::greater<std::pair<long long, int>>> queue;

    std::vector<long long> distances (V + 1, std::numeric_limits<long long>::max());

    queue.emplace(0, source);
    distances.at(source) = 0;
    
    long long dist;
    int u;
    while (!queue.empty()) 
    {
        dist = queue.top().first;
        u = queue.top().second;

        queue.pop();

        for(const auto& [v, weight] : list.at(u))
        {
            if (dist + weight < distances.at(v)) 
            {
                distances.at(v) = dist + weight;
                assert(distances.at(v) > 0);

                queue.emplace(distances.at(v), v);
            }
        }
    }

    return distances;
}

std::vector<long long> Graph::dial(int source)
{
    std::vector<long long> distances(V + 1, std::numeric_limits<long long>::max());
    distances[source] = 0;

    //long long max_possible_bucket = weight_max * V;
    std::vector<std::list<int>> buckets (weight_max, std::list<int>());
    buckets[0].push_back(source);

    int last;
    for(int i = 0; i < weight_max; i++)
    {
        while(!buckets[i].empty()) 
        {
            int u = buckets[i].front();
            buckets[i].pop_front();

            for (const auto& [v, weight] : list.at(u)) 
            {
                if (distances[u] + weight < distances.at(v)) 
                {
                    if(distances[v] < std::numeric_limits<long long>::max())
                    {
                        buckets[distances.at(v) % (weight_max)].remove(v);
                    }
                    distances.at(v) = distances.at(u) + weight;
                    buckets[distances.at(v) % (weight_max)].push_back(v);
                }
            }
            last = u;
        }
    }

    std::cout << distances.at(last) << " <- distance\n";
    return distances;
}


std::vector<long long> Graph::radix(int source)
{
    if (source < 1 || source > V) 
        throw std::out_of_range("Source node out of bounds");

    RadixHeap heap;
    std::vector<long long> distances (V + 1, std::numeric_limits<long long>::max());

    distances.at(source) = 0;
    heap.push(0, source);

    while (!heap.empty()) 
    {
        auto [dist, u] = heap.pop();

        assert(u < V + 1);
        assert(dist >= 0);

        if (dist > distances.at(u)) continue;

        for (const auto& [v, weight] : list.at(u))
        {
            long long new_dist = dist + weight;
            assert(new_dist >= 0);
            assert(v < V + 1);

            if (new_dist < distances.at(v)) 
            {
                distances.at(v) = new_dist;
                heap.push(new_dist, v);
            }
        }
    }

    return distances;
}