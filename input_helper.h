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

using lazy = long long int;

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

    /////////////////////////////////////////////// DAY 3 AND DAY 4 ///////////////////////////////////////////////

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
            std::string token;

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
};

#endif // INPUT_HELPER_H
