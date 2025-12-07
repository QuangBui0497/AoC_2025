#include "../input_helper.h"

void print(const std::vector<std::string>& list)
{
    for(auto const& str : list)
    {
        std::cout << str << std::endl;
    }
}

void print_2(const std::vector<std::vector<lazy>>& list)
{
    for(auto const& vec : list)
    {
        for(auto const& val : vec)
        {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
}

void part_1(std::vector<std::string> list)
{
    std::size_t mid_index = list[0].size() / 2;
    list[1][mid_index] = '|';

    int split_count = 0;

    for(std::size_t row = 2; row != list.size(); ++row)
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
    // Such a beauty!
    print(list);
    std::cout << "Result part 1: " << split_count << std::endl;
}

void part_2(std::vector<std::string> list)
{
    std::size_t rows = list.size();
    std::size_t cols = list[0].size();

    std::vector<std::vector<lazy>> count_list(rows, std::vector<lazy>(cols, 0));

    std::size_t s_index = list[0].find('S');
    count_list[1][s_index] = 1;

    for(std::size_t row = 2; row != rows; ++row)
    {
        for(std::size_t col = 0; col != cols; ++col)
        {
            lazy above_splitter = count_list[row - 1][col];

            if(above_splitter == 0)
                continue;

            if(list[row][col] == '^')
            {
                count_list[row][col - 1] += above_splitter;
                count_list[row][col + 1] += above_splitter;
            }
            else
            {
                count_list[row][col] += count_list[row - 1][col];
            }
        }
    }

    lazy total = 0;

    for(auto &val : count_list.back())
        total += val;

    // This prints chaos ~.~
    // print_2(count_list); 

    std::cout << "Result part 2: " << total << std::endl;
}

int main()
{
    auto list = InputHelper::read_file3("day_7_input.txt");
    part_1(list);
    part_2(list);
    return 0;
}