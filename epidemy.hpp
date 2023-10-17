#pragma once

#include <vector>
#include <cstddef>

class InfectionMap
{
public:
    InfectionMap(size_t number_of_cities) : number_of_cities_(number_of_cities),
                                            edges_(number_of_cities),
                                            city_status_(number_of_cities, Status::kHealthy){};

    void AddConnection(size_t u, size_t v);
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
