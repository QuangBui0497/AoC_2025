#include "../input_helper.h"

const int ATTEMPT = 1000;

lazy get_dist(const JunctionBox& box_1, const JunctionBox& box_2)
{
    lazy dx = box_1.m_x - box_2.m_x;
    lazy dy = box_1.m_y - box_2.m_y;
    lazy dz = box_1.m_z - box_2.m_z;
    return dx*dx + dy*dy + dz*dz;
}

lazy_edge create_edge_list(const lazy_box& list)
{
    lazy_edge edge_list;
    for(std::size_t i = 0; i != list.size(); ++i)
    {
        for(std::size_t j = i + 1; j != list.size(); ++j)
        {
            edge_list.emplace_back(i, j, get_dist(list[i], list[j]));
        }
    }

    std::sort(edge_list.begin(), edge_list.end(),
        [](const Edge& a, const Edge& b) {
        return a.m_dist < b.m_dist;
    });

    return edge_list;
}

void part_1(const lazy_box& list)
{
    auto edge_list = create_edge_list(list);
    UnionFind solve(list.size());

    int count = 0;
    for(const auto& edge : edge_list)
    {
        if(count == ATTEMPT) break;
        solve.merge(edge.m_box_1_index, edge.m_box_2_index);
        ++count;
    }

    auto circuit_size_list = solve.circuit_size_list;
    auto size = circuit_size_list.size();
    std::sort(circuit_size_list.begin(), circuit_size_list.end());

    lazy result = circuit_size_list[size - 1] * circuit_size_list[size - 2] * circuit_size_list[size - 3];

    std::cout << "Result part 1: " << result << std::endl;
}

void part_2(const lazy_box& list)
{
    auto edge_list = create_edge_list(list);
    UnionFind solve(list.size());

    for(const auto& edge : edge_list)
        solve.merge_2(edge);

    auto final_edge = solve.edge_list.back();

    lazy result = list[final_edge.m_box_1_index].m_x * list[final_edge.m_box_2_index].m_x;

    std::cout << "Result part 2: " << result << std::endl;
}

int main()
{
    auto list = InputHelper::read_file6("day_8_input.txt");
    part_1(list);
    part_2(list);

    return 0;
}