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

}

int main()
{
    auto list = InputHelper::read_file3("day_3_input.txt");

    part_1(list);

    return 0;
}