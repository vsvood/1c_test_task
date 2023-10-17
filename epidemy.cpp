#include "epidemy.hpp"

#include <iostream>
#include <map>

void InfectionMap::AddConnection(size_t u, size_t v)
{
    edges_[u].push_back(v);
}

std::vector<size_t> InfectionMap::InfectAll()
{
    size_t infected_count = 0;
    std::vector<size_t> initial_cities;

    while (infected_count < number_of_cities_)
    {
        size_t best_v, best_infected = 0, best_at_risk = 0;

        for (size_t v = 0; v < number_of_cities_; ++v)
        {
            if (city_status_[v] == Status::kInfected)
                continue;

            std::vector<Status> copy = city_status_;
            copy[v] = Status::kInfected;

            auto [infected, at_risk] = DFS(v, copy);
            ++infected;

            if (infected > best_infected || (infected == best_infected && at_risk > best_at_risk))
            {
                best_v = v;
                best_infected = infected;
                best_at_risk = at_risk;
            }
        }

        initial_cities.push_back(best_v);
        DFS(best_v, city_status_);
        infected_count += best_infected;
    }

    return initial_cities;
}

std::pair<size_t, size_t> InfectionMap::DFS(size_t v, std::vector<Status> &status)
{
    int infected = 0;
    int at_risk = 0;
    for (auto u : edges_[v])
    {
        switch (status[u])
        {
        case Status::kHealthy:
            status[u] = Status::kAtRiskNow;
            ++at_risk;
            break;

        case Status::kAtRisk:
        {
            status[u] = Status::kInfected;
            ++infected;
            auto [infection, risk] = DFS(u, status);
            infected += infection;
            at_risk += risk;
            break;
        }

        case Status::kAtRiskNow:
        {
            status[u] = Status::kInfected;
            ++infected;
            --at_risk;
            auto [infection, risk] = DFS(u, status);
            infected += infection;
            at_risk += risk;
            break;
        }

        case Status::kInfected:
            break;

        default:
            break;
        }
    }

    return {infected, at_risk};
}

class RenumberingInfectionMapBuilder
{
public:
    void AddEdge(size_t u, size_t v)
    {
        edges_.push_back(std::make_pair(Convert(u), Convert(v)));
    }

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

int main()
{
    int M;
    std::cin >> M;
    size_t u, v;

    auto builder = RenumberingInfectionMapBuilder();

    for (int i = 0; i < M; ++i)
    {
        std::cin >> u >> v;
        builder.AddEdge(u, v);
    }


    auto infection_map = builder.Get();
    auto reverse_converter = builder.GetReverseConverter();


    auto result = infection_map.InfectAll();

    std::cout << result.size();

    for (auto v : result)
    {
        std::cout << reverse_converter[v] << ' ';
    }
}