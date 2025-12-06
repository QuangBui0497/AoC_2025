#include "../input_helper.h"

std::vector<std::vector<lazy>> transform(const std::vector<std::vector<lazy>>& list)
{
    std::vector<std::vector<lazy>> transformed_list;
    
    int rows = list.size();
    int cols = list[0].size();

    transformed_list.resize(cols);

    for (auto& row : transformed_list)
        row.resize(rows);

    for(std::size_t row = 0; row != list.size(); ++row)
    {
        for(std::size_t col = 0; col != list[row].size(); ++col)
        {
            transformed_list[col][row] = list[row][col];
        }
    }
    return transformed_list;
}

void part_1(const std::vector<std::vector<lazy>>& list)
{
    auto transformed_list = transform(list);

    lazy total = 0;

    for(std::size_t row = 0; row != transformed_list.size(); ++row)
    {
        lazy plus_total = 0;
        lazy mult_total = 1;

        std::size_t last_index = transformed_list[row].size() - 1;

        for(std::size_t col = 0; col != transformed_list[row].size() - 1; ++col)
        {
            if(transformed_list[row][last_index] == -1)
                plus_total += transformed_list[row][col];

            if(transformed_list[row][last_index] == -2)
                mult_total *= transformed_list[row][col];
        }
        
        if(mult_total > 1)
            total += plus_total + mult_total;
        else
            total += plus_total;
    }
    std::cout << "Result part 1: " << total << std::endl;
}

int main()
{
    auto list = InputHelper::read_file5("day_6_input.txt");

    part_1(list);

    // transform(list);

    return 0;
}