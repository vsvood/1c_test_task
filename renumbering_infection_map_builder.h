#pragma once

#include <map>

#include "infection_map.hpp"

/**
 * Infection map works with cities numbered 0, 1, ..., number_of_cities-1,
 * so we need a converter, or builder to work with raw input
*/
class RenumberingInfectionMapBuilder
{
public:
    /**
     * Add adge to map
     * 
     * Converts and remember the edge for further building map
     * 
     * @param u index of first city
     * @param v index of first city
    */
    void AddEdge(size_t u, size_t v)
    {
        edges_.push_back(std::make_pair(Convert(u), Convert(v)));
    }

    /**
     * Get Infection Map corresponding to input
     * 
     * @returns InfectionMap build from source
    */
    InfectionMap Get()
    {
        auto infection_map = InfectionMap(counter_);
        for (auto [u, v] : edges_)
        {
            infection_map.AddConnection(u, v);
            infection_map.AddConnection(v, u);
        }
        return infection_map;
    }

    /**
     * Get reverse converter from Infection Map indices to original
     * 
     * @returns std::vector<size_t> - original indexes of city_i
    */
    std::vector<size_t> GetReverseConverter()
    {
        return reverse_converter_;
    }

private:
    size_t Convert(size_t v)
    {
        if (!converter_.contains(v))
        {
            converter_[v] = counter_;
            reverse_converter_.push_back(v);
            return counter_++;
        }

        return converter_[v];
    }

    size_t counter_ = 0;
    std::map<size_t, size_t> converter_;
    std::vector<size_t> reverse_converter_;
    std::vector<std::pair<size_t, size_t>> edges_;
};