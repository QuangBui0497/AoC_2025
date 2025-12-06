#include "../input_helper.h"

const std::string PAD_STR = "0";
const std::string PLUS_STR  = "-1";
const std::string MULT_STR  = "-2";

const int PLUS  = -1;
const int MULT  = -2;
const int ERR  = -3;

template <typename T>
void print(const T& list)
{
    for(auto const& vec : list)
    {
        for(std::size_t i = 0; i != vec.size(); ++i)
        {
            if(vec[i] == "0")
                continue;
            std::cout << vec[i] << " ";
        }
        std::cout << std::endl;
    }
}

template <typename T>
T transform(const T& list)
{
    T transformed_list;
    
    int rows = list.size();
    int cols = 0;

    for (auto& row : list)
        if (row.size() > cols)
            cols = row.size();

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

lazy get_num(const std::vector<std::string>& list)
{
    std::string result;
    for(auto &val : list)
    {
        if(val == PAD_STR || val == PLUS_STR || val == MULT_STR)
            continue;
        result += val;  
    }
    return result != "" ? std::stoll(result) : ERR;
}

void part_1(const lazy_matrix& list)
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
            if(transformed_list[row][last_index] == PLUS)
                plus_total += transformed_list[row][col];

            if(transformed_list[row][last_index] == MULT)
                mult_total *= transformed_list[row][col];
        }
        
        if(mult_total > 1)
            total += plus_total + mult_total;
        else
            total += plus_total;
    }
    std::cout << "Result part 1: " << total << std::endl;
}

void part_2(const lazy_matrix_str& list)
{
    auto transformed_list = transform(list);

    lazy total = 0;
    lazy plus_total = 0;
    lazy mult_total = 1;
    std::string op;
    std::string prev_op;
    bool get_op = false;

    for(const auto& vec : transformed_list)
    {
        if(!get_op)
        {
            op = vec[vec.size() - 1];
            get_op = !get_op;
        }

        lazy num = get_num(vec);

        if(num == ERR)
        {
            if(mult_total > 1)
                total += plus_total + mult_total;
            else
                total += plus_total;

            plus_total = 0;
            mult_total = 1;
            get_op = !get_op;
            continue;
        }

        if(op == PLUS_STR)
        {
            plus_total += num;  
            prev_op = op; 
        }

        if(op == MULT_STR)
        {
            mult_total *= num;
            prev_op = op;
        }
    }
    if(mult_total > 1)
        total += plus_total + mult_total;
    else
        total += plus_total;
    std::cout << "Result part 2: " << total << std::endl;
}

int main()
{
    auto list_1 = InputHelper::read_file5("day_6_input.txt").first;
    auto list_2 = InputHelper::read_file5("day_6_input.txt").second;

    part_1(list_1);
    part_2(list_2);

    return 0;
}