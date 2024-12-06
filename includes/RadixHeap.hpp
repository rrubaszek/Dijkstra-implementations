#pragma once

#include <array>
#include <vector>

class RadixHeap
{
public:
    RadixHeap();

    bool empty();
    void push(long long key, int node);
    std::pair<long long, int> pop();

private:
    static constexpr int bits = 64;
    std::vector<std::vector<std::pair<long long, int>>> buckets;
    std::vector<long long> min_value;
    long long last_extracted;
    int m_size;
    int find_bucket(long long key);
    void refill();
};