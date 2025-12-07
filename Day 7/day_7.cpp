#include "../input_helper.h"

void print(const std::vector<std::string>& list)
{
    for(auto const& str : list)
    {
        std::cout << str << std::endl;
    }
}

void part_1(std::vector<std::string> list)
{
    std::size_t mid_index = list[0].size() / 2;
    list[1][mid_index] = '|';
    list[2][mid_index - 1] = '|';
    list[2][mid_index + 1] = '|';

    int split_count = 1;

    for(std::size_t row = 3; row != list.size(); ++row)
    {
        for(std::size_t col = 0; col != list[row].size(); ++col)
        {

            // No beam, no split
            if(list[row][col] == '^' && list[row - 1][col] != '|')
                continue;

            if(list[row - 1][col] == '|' && list[row][col] != '^')
                list[row][col] = '|';

            if(list[row][col] == '^')
            {
                list[row][col - 1] = '|';
                list[row][col + 1] = '|';
                ++split_count;
            }
        }
    }
    print(list);
    std::cout << "Result part 1: " << split_count << std::endl;
}

int main()
{
    auto list_1 = InputHelper::read_file3("day_7_input.txt");
    part_1(list_1);

    return 0;
}