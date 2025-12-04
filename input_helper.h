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
        long long int first;
        long long int last;
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
                long long int first = std::stoll(token.substr(0, dash));
                long long int last  = std::stoll(token.substr(dash + 1));
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
};

#endif // INPUT_HELPER_H
