#include "RadixHeap.hpp"

#include <algorithm>
#include <cmath>
#include <iostream>

RadixHeap::RadixHeap()
{
    buckets.resize(bits + 1);  // 65 buckets for 64-bit integers (huge weights)
    min_value.resize(bits + 1, std::numeric_limits<int>::max());
    last_extracted = 0; 
    m_size = 0;
}

bool RadixHeap::empty() 
{
    return m_size == 0;
}

void RadixHeap::push(long long key, int node)
{
    m_size++;
    int bucket_index = find_bucket(key);
    buckets.at(bucket_index).emplace_back(key, node);
    min_value.at(bucket_index) = std::min(min_value.at(bucket_index), key);
}

std::pair<long long, int> RadixHeap::pop() 
{
    if (buckets[0].empty()) 
    {
        refill();
    }

    auto top = buckets[0].back();
    buckets[0].pop_back();
    last_extracted = top.first;
    m_size--;
    return top;
}

int RadixHeap::find_bucket(long long key) 
{
    return key == last_extracted ? 0 : bits - 1 - __builtin_clz(key ^ last_extracted);
}

void RadixHeap::refill() 
{
    int i = 1;
    while (i < buckets.size() && buckets.at(i).empty()) 
    {
        ++i;
    }

    long long new_min = std::numeric_limits<long long>::max();
    for (const auto& kv : buckets.at(i)) 
    {
        new_min = std::min(new_min, kv.first);
    }

    last_extracted = new_min;

    for (auto& kv : buckets.at(i)) 
    {
        int bucket_index = find_bucket(kv.first);
        buckets[bucket_index].emplace_back(kv);
    }

    buckets.at(i).clear();
}