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

void Graph::print_graph() {}

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
    
    long long curr_dist;
    int curr_node;
    while (!queue.empty()) 
    {
        curr_dist = queue.top().first;
        curr_node = queue.top().second;

        queue.pop();

        for(const auto& [next_node, weight] : list.at(curr_node))
        {
            if (curr_dist + weight < distances.at(next_node)) 
            {
                distances.at(next_node) = curr_dist + weight;
                assert(distances.at(next_node) > 0);

                queue.emplace(distances.at(next_node), next_node);
            }
        }
    }

    return distances;
}

std::vector<long long> Graph::dial(int source)
{
    if (source < 1 || source > V) 
        throw std::out_of_range("Source node out of bounds");

    long long max_possible_bucket = weight_max * V;
    assert(max_possible_bucket >= 1);

    std::unordered_map<long long, std::vector<int>> buckets;
    // buckets.reserve(max_possible_bucket + 1);

    std::vector<long long> distances (V + 1, std::numeric_limits<long long>::max());
    std::vector<bool> visited_buckets (V + 1, false);

    distances.at(source) = 0;
    visited_buckets.at(source) = true;
    buckets[0].push_back(source);

    int bucket_index = 0;
    while (!buckets.empty()) 
    {
        // Find the next non-empty bucket
        while (buckets[bucket_index].empty() && bucket_index < max_possible_bucket) 
        {
            bucket_index++;
        }
        if (bucket_index >= max_possible_bucket) break;

        // std::vector<int> current_bucket = std::move(buckets[bucket_index]);
        // buckets.erase(bucket_index);

        for (int u : buckets.at(bucket_index))
        {
            // if (distances.at(u) < bucket_index) continue;
            if (visited_buckets.at(u)) continue;

            visited_buckets.at(u) = true;

            for (const std::pair<int, long long>& edge : list.at(u))
            {
                long long new_distance = distances.at(u) + edge.second;
                if (new_distance < distances.at(edge.first)) 
                {
                    distances.at(edge.first) = new_distance;
                    bucket_index = new_distance;
                    buckets[new_distance].push_back(edge.first);
                }
            }
        }

        buckets.erase(bucket_index);

        // for (int u : current_bucket) 
        // {
        //     if (distances[u] < bucket_index) continue; // Skip stale entries

        //     for (const auto& [v, weight] : list[u]) 
        //     {
        //         long long new_distance = distances[u] + weight;
        //         assert(new_distance >= 1);

        //         if (new_distance < distances[v]) 
        //         {
        //             distances[v] = new_distance;
        //             buckets[new_distance].push_back(v);
        //         }
        //     }
        // }
    }

    return distances;
}

std::vector<long long> Graph::radix(int source)
{
    if (source < 1 || source > V) 
        throw std::out_of_range("Source node out of bounds");

    RadixHeap heap;
    std::vector<long long> dist (V + 1, std::numeric_limits<long long>::max());

    dist.at(source) = 0;
    heap.push(0, source);

    while (!heap.empty()) 
    {
        auto [current_dist, current_node] = heap.pop();

        assert(current_node <= V);

        if (current_dist > dist.at(current_node)) continue;

        for (const auto& [neighbor, weight] : list.at(current_node))
        {
            long long new_dist = current_dist + (long long)weight;
            assert(new_dist >= 1);

            if (new_dist < dist.at(neighbor)) 
            {
                dist.at(neighbor) = new_dist;
                heap.push(new_dist, neighbor);
            }
        }
    }

    return dist;
}