#pragma once

#include <array>
#include <vector>

class RadixHeap
{
private:
    static constexpr int bits = 64;
    int m_size;
    long long last_extracted;

    void refill();
    int find_bucket(long long key);

    std::vector<long long> min_value;
    std::vector<std::vector<std::pair<long long, int>>> buckets;
    
public:
    RadixHeap();
    bool empty();
    void push(long long key, int node);
    std::pair<long long, int> pop();
};