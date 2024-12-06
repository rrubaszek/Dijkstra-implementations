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

// std::vector<long long> Graph::dial(int source)
// {
//     std::vector<long long> distances(V + 1, std::numeric_limits<long long>::max());
//     distances[source] = 0;

//     long long max_possible_bucket = weight_max * V;
//     std::vector<std::list<long long>> buckets(weight_max + 1);
//     buckets[0].push_back(source);

//     for(long long i = 0; i <= weight_max; i++)
//     {
//         while(!buckets[i].empty()) 
//         {
//             long long u = buckets[i].front();
//             buckets[i].pop_front();

//             for (const auto& edge : list[u]) 
//             {
//                 long long v = edge.first;
//                 long long weight = edge.second;

//                 if (distances[u] + weight < distances[v]) 
//                 {
//                     distances[v] = distances[u] + weight;
//                     buckets[std::min(weight_max, distances[v])].push_back(v);
//                 }
//             }
//         }
//     }
//     return distances;
// }

std::vector<long long> Graph::dial(int source)
{
    if (source < 1 || source > V) 
        throw std::out_of_range("Source node out of bounds");

    long long max_possible_bucket = weight_max * V;
    assert(max_possible_bucket >= 1);

    std::unordered_map<long long, std::vector<int>> buckets;

    std::vector<long long> distances (V + 1, std::numeric_limits<long long>::max());
    std::vector<bool> visited_nodes (V + 1, false);

    distances.at(source) = 0;
    visited_nodes.at(source) = true;
    buckets[0].push_back(source);   

    long long bucket_index = 0;
    while (!buckets.empty()) 
    {
        // Find the next non-empty bucket
        while (bucket_index < weight_max && buckets.find(bucket_index) == buckets.end()) {
            bucket_index++;
        }
        // while (bucket_index < max_possible_bucket && buckets[bucket_index].empty()) 
        // {
        //     bucket_index++;
        // }
        if (bucket_index >= weight_max) break;

        for (int u : buckets[bucket_index])
        {
            // if (visited_nodes.at(u)) continue;

            // visited_nodes.at(u) = true;

            // if (distances.at(u) < bucket_index) continue;

            for (const auto& [v, weight] : list.at(u))
            {
                long long new_dist = distances.at(u) + weight;
                assert(new_dist >= 0);

                if (new_dist < distances.at(v)) 
                {
                    distances.at(v) = new_dist;
                    bucket_index = new_dist;
                    buckets[std::min(weight_max, new_dist)].push_back(v);
                }
            }
        }

        buckets.erase(bucket_index); 
    }

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