#pragma once

#include <vector>
#include <cstddef>

/**
 * This class represents state of map during the epidemy
*/
class InfectionMap
{
public:
    InfectionMap(size_t number_of_cities) : number_of_cities_(number_of_cities),
                                            edges_(number_of_cities),
                                            city_status_(number_of_cities, Status::kHealthy){};

    /**
     * add a link between two cities
     * 
     * add a link between two cities through which the disease can spread
     * 
     * @param u index of first city, expected to be in range [0, number_of_cities-1]
     * @param v index of first city, expected to be in range [0, number_of_cities-1]
    */
    void AddConnection(size_t u, size_t v);

    /**
     * Infect all cities
     * 
     * Tries to find min number of initialy infected cities to infect all
     * 
     * @returns std::vector<size_t> - indexes of initially infected cities
    */
    std::vector<size_t> InfectAll();

private:
    enum class Status
    {
        kHealthy,
        kAtRisk,
        kAtRiskNow,
        kInfected,
    };

    std::pair<size_t, size_t> DFS(size_t v, std::vector<Status>& status);

    size_t number_of_cities_;
    std::vector<std::vector<size_t>> edges_;

    std::vector<Status> city_status_;
};
