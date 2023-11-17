#pragma once


#include "gCommon.h"

#include <map>
#include <vector>
#include <numeric>
#include <algorithm>
#include <memory>

#include <iostream>

class MemoryPool {
public:

    MemoryPool(size_t initialSize, size_t maxSize)
        : max_size(maxSize)
    {
        allocateBlock(initialSize);
    }

    void* allocate(size_t size, size_t alignment = alignof(std::max_align_t)) {
        size = align(size, alignment);

        auto it = free_blocks.lower_bound(size);
        if (it != free_blocks.end()) {
            void* ptr = it->second.back();
            it->second.pop_back();
            if (it->second.empty()) {
                free_blocks.erase(it);
            }

            LOG.Log(Logger::LogLevel::INFO, "Memory Use", size);
            return ptr;
        }

        if (total_size + size <= max_size) {
            allocateBlock(size);
            auto last = --free_blocks.lower_bound(size);
            void* ptr = last->second.back();
            last->second.pop_back();
            if (last->second.empty()) {
                free_blocks.erase(last);
            }
            return ptr;
        }

        return nullptr;
    }

    void deallocate(void* ptr, size_t size, size_t alignment = alignof(std::max_align_t)) {
        size = align(size, alignment);
        free_blocks[size].push_back(ptr);

        LOG.Log(Logger::LogLevel::INFO, "Memory Free", size);
    }

private:
    size_t align(size_t size, size_t alignment) {
        return (size + alignment - 1) & ~(alignment - 1);
    }

    void allocateBlock(size_t size) {
        std::vector<char> new_block(size);
        blocks.push_back(std::move(new_block));
        free_blocks[size].push_back(blocks.back().data());
        total_size += size;
    }

    size_t max_size;
    size_t total_size = 0;
    std::map<size_t, std::vector<void*>> free_blocks;
    std::vector<std::vector<char>> blocks;
};
