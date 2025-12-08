#ifndef INPUT_HELPER_H
#define INPUT_HELPER_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <cstdlib>
#include <math.h>
#include <unordered_map>
#include <algorithm>
#include <utility>

struct JunctionBox;
struct Edge;

using lazy = long long int;
using lazy_matrix = std::vector<std::vector<lazy>>;
using lazy_vector = std::vector<lazy>;
using lazy_box = std::vector<JunctionBox>;
using lazy_edge = std::vector<Edge>;
using lazy_matrix_str = std::vector<std::vector<std::string>>;

struct JunctionBox
{
    lazy m_x, m_y, m_z;
};

struct Edge 
{
    Edge(std::size_t index_1, std::size_t index_2, lazy dist)
        : m_box_1_index{index_1}, m_box_2_index{index_2}, m_dist{dist} {}

    std::size_t m_box_1_index, m_box_2_index;
    lazy m_dist;
};

struct UnionFind
{
    UnionFind(int n)
    {
        parent.resize(n);
        circuit_size_list.resize(n, 1);
        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }

    lazy_vector parent;
    lazy_vector circuit_size_list;
    lazy_edge edge_list;

    int find(std::size_t a)
    {
        if (parent[a] != a)
            parent[a] = find(parent[a]);
        return parent[a];
    }

    void merge(std::size_t a, std::size_t b)
    {
        a = find(a);
        b = find(b);

        if (a == b) 
            return;

        if (circuit_size_list[a] < circuit_size_list[b])
        {
            parent[a] = b;
            circuit_size_list[b] += circuit_size_list[a];
        }
        else
        {
            parent[b] = a;
            circuit_size_list[a] += circuit_size_list[b];
        }
    }

    void merge_2(Edge edge)
    {
        std::size_t a = find(edge.m_box_1_index);
        std::size_t b = find(edge.m_box_2_index);

        if (a == b) 
            return;

        if (circuit_size_list[a] < circuit_size_list[b])
        {
            parent[a] = b;
            circuit_size_list[b] += circuit_size_list[a];
        }
        else
        {
            parent[b] = a;
            circuit_size_list[a] += circuit_size_list[b];
        }

        edge_list.push_back(edge);
    }
};

class InputHelper
{
    /////////////////////////////////////////////// DAY 1 ///////////////////////////////////////////////
public:

    struct Command {
        char dir;   
        int value;  
    };

    static std::vector<Command> read_file(const std::string& filename)
    {
        std::ifstream in(filename);
        if (!in) 
        {
            throw std::runtime_error("Failed to open file: " + filename);
        }

        std::vector<Command> commands;
        std::string line;

        while (std::getline(in, line)) 
        {
            if (line.empty()) continue;          
            if (line.back() == '\r')             
                line.pop_back();

            char dir = line[0];                  
            int value = std::stoi(line.substr(1));

            commands.push_back({ dir, value });
        }

        return commands;
    }

    /////////////////////////////////////////////// DAY 2 ///////////////////////////////////////////////

    struct ID {
        lazy first;
        lazy last;
    };

    static std::vector<ID> read_file2(const std::string& filename)
    {
        std::ifstream in(filename);
        if (!in) 
        {
            throw std::runtime_error("Failed to open file: " + filename);
        }

        std::vector<ID> commands;
        std::string line;

        while (std::getline(in, line)) 
        {
            if (line.empty()) continue;          
            if (line.back() == '\r')             
                line.pop_back();

            std::stringstream ss(line);
            std::string token;

            while (std::getline(ss, token, ','))
            {
                auto dash = token.find('-');
                lazy first = std::stoll(token.substr(0, dash));
                lazy last  = std::stoll(token.substr(dash + 1));
                commands.push_back({ first, last });
            }
        }

        return commands;
    }

    /////////////////////////////////////////////// DAY 3 & DAY 4 & DAY 7 ///////////////////////////////////////////////

    static std::vector<std::string> read_file3(const std::string& filename)
    {
        std::ifstream in(filename);
        if (!in) 
        {
            throw std::runtime_error("Failed to open file: " + filename);
        }

        std::vector<std::string> commands;
        std::string line;

        while (std::getline(in, line)) 
        {
            if (line.empty()) continue;          
            if (line.back() == '\r')             
                line.pop_back();

            std::stringstream ss(line);

            commands.push_back(line);
        }

        return commands;
    }

    /////////////////////////////////////////////// DAY 5 ///////////////////////////////////////////////

    static std::pair<std::vector<std::pair<lazy, lazy>>, std::vector<lazy> > read_file4(const std::string& filename)
    {
        std::ifstream in(filename);
        if (!in) 
        {
            throw std::runtime_error("Failed to open file: " + filename);
        }

        std::vector<std::pair<lazy, lazy>> id_range;
        std::vector<lazy> ingredient_id;
        std::string line;

        while (std::getline(in, line)) 
        {
            if (line.empty()) continue;          
            if (line.back() == '\r')             
                line.pop_back();

            std::stringstream ss(line);

            while (std::getline(ss, line))
            {
                auto dash = line.find('-');
                if(dash != std::string::npos)
                {
                    lazy first = std::stoll(line.substr(0, dash));
                    lazy last  = std::stoll(line.substr(dash + 1));
                    id_range.push_back({first, last});
                }
                else
                {
                    ingredient_id.push_back(std::stoll(line));
                }
            }
        }

        return std::pair{id_range, ingredient_id};
    }

    /////////////////////////////////////////////// DAY 6 ///////////////////////////////////////////////

    static std::pair<lazy_matrix, lazy_matrix_str> read_file5(const std::string& filename)
    {
        std::ifstream in(filename);
        if (!in) 
        {
            throw std::runtime_error("Failed to open file: " + filename);
        }

        lazy_matrix part_1_list;
        lazy_matrix_str part_2_list;
        std::vector<lazy> row_of_num_part_1;
        

        std::string line;

        while (std::getline(in, line)) 
        {
            if (line.empty()) continue;          
            if (line.back() == '\r' || line.back() == '\t')             
                line.pop_back();

            std::stringstream ss(line);
            std::string token;

            std::vector<std::string> row_of_num_part_2;

            for (size_t i = 0; i < line.size(); ++i)
            {
                char c = line[i];

                if (c == ' ')
                    row_of_num_part_2.push_back("0");
                else if (c == '+')
                    row_of_num_part_2.push_back("-1");
                else if (c == '*')
                    row_of_num_part_2.push_back("-2");
                else
                    row_of_num_part_2.push_back(std::string{c});
            }

            part_2_list.push_back(row_of_num_part_2);
            row_of_num_part_2.clear();

            while (ss >> token)
            {
                if(token == "+")
                {
                    row_of_num_part_1.push_back(-1);
                    continue;
                }

                if(token == "*")
                {
                    row_of_num_part_1.push_back(-2);
                    continue;
                }

                int num = std::stoi(token);
                row_of_num_part_1.push_back(num);
            }
            part_1_list.push_back(row_of_num_part_1);
            row_of_num_part_1.clear();
        }
        return {part_1_list, part_2_list};
    }

    /////////////////////////////////////////////// DAY 8 ///////////////////////////////////////////////

    static lazy_box read_file6(const std::string& filename)
    {
        std::ifstream in(filename);
        if (!in) 
        {
            throw std::runtime_error("Failed to open file: " + filename);
        }

        lazy_box boxes;
        lazy_vector coordinate;

        std::string line;

        while (std::getline(in, line)) 
        {
            if (line.empty()) continue;          
            if (line.back() == '\r')             
                line.pop_back();

            std::stringstream ss(line);
            std::string token;

            while (std::getline(ss, token, ','))
            {
                coordinate.push_back(std::stoll(token));
            }
            // create box
            JunctionBox box;
            box.m_x = coordinate[0];
            box.m_y = coordinate[1];
            box.m_z = coordinate[2];

            boxes.push_back(box);
            coordinate.clear();
        }

        return boxes;
    }
};

#endif // INPUT_HELPER_H
