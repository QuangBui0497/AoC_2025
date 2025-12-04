#include "../input_helper.h"

void part_1(const std::vector<std::string>& list)
{
    int total_roll = 0;

    for(int row = 0; row != list.size(); ++row)
    {
        for(int col = 0; col != list[row].size(); ++col)
        {
            if(list[row][col] != '@')
                continue;

            int neighbor_count = 0;

            for(int row_dir = -1; row_dir <= 1; ++row_dir)
            {
                for(int col_dir = -1; col_dir <= 1; ++col_dir)
                {
                    if (row_dir == 0 && col_dir == 0) 
                        continue;

                    int row_pos = row_dir + row;
                    int col_pos = col_dir + col;

                    if(row_pos < 0 || row_pos >= list.size() || col_pos < 0 || col_pos >= list[row].size())
                        continue;
                    
                    if(list[row_pos][col_pos] == '@')
                        ++neighbor_count;
                }
            }
           
            if(neighbor_count < 4)
                ++total_roll;
        }
    }

    std::cout << "Result part 1: " << total_roll << std::endl;
}

int main()
{
    auto list = InputHelper::read_file3("day_4_input.txt");

    part_1(list);

    return 0;
}