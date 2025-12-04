#include "../input_helper.h"


int ctoi(char c) 
{
    return c - '0';
}

void part_1(const std::vector<std::string>& list)
{
    int total = 0;
    
    for(auto const& val : list)
    {
        int tens_digit = 0, ones_digit = 0;
        std::size_t tens_index;

        for(std::size_t i = 0; i <= val.size() - 2; ++i)
        {
            int temp = ctoi(val[i]);

            if(tens_digit < temp)
            {
                tens_digit = temp;
                tens_index = i;
            }
        }

        for(std::size_t j = tens_index + 1; j != val.size(); ++j)
        {
            int temp = ctoi(val[j]);

            if(ones_digit < temp)
                ones_digit = temp;
        }

        total += tens_digit * 10 + ones_digit;            
    }
    std::cout << "Result part 1: " << total << std::endl;
}

void part_2(const std::vector<std::string>& list)
{
    long long int total = 0;

    for(auto const& val : list)
    {
        int billions_digit = 0;
        std::size_t billions_index;

        for(std::size_t i = 0; i <= val.size() - 12; ++i)
        {
            int temp = ctoi(val[i]);

            if(billions_digit < temp)
            {
                billions_digit = temp;
                billions_index = i;
            }
        }
        
        int remaining_digits = 11;
        long long int battery_val = 0;
        std::size_t start_index = billions_index + 1;
        int other_digit = ctoi(val[start_index]);

        while(remaining_digits > 0)
        {
            for(std::size_t j = start_index; j < val.size() - remaining_digits; ++j)
            {
                int temp = ctoi(val[j + 1]);

                if(other_digit < temp)
                {
                    other_digit = temp;
                    start_index = j + 1;
                }
            }
            battery_val += other_digit * std::pow(10, --remaining_digits);
            other_digit = 0;
        }
        total += billions_digit * std::pow(10, 11) + battery_val;         
    }
    std::cout << "Result part 2: " << total << std::endl;
}

int main()
{
    auto list = InputHelper::read_file3("day_3_input.txt");

    part_1(list);
    part_2(list);

    return 0;
}