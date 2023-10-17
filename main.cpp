#include "infection_map.hpp"
#include "renumbering_infection_map_builder.h"

#include <iostream>


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

    std::cout << result.size() << '\n';

    for (auto v : result)
    {
        std::cout << reverse_converter[v] << " ";
    }
    std::cout << '\n';
}