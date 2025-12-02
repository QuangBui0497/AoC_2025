#include "../input_helper.h"

constexpr int MAX_NUM = 100;
constexpr int MIN_NUM = 0;

constexpr char LEFT = 'L';
constexpr char RIGHT = 'R';

int calculate(int current_point, int temp, const char dir)
{
    if(dir == LEFT)
        return  temp < MIN_NUM ? current_point = std::abs(MAX_NUM - std::abs(temp)) : current_point = temp;
    else
        return temp < MAX_NUM ?  current_point = temp : current_point = temp - MAX_NUM;
}

int reduce(int num, int& pass_zero)
{
    if(num <= MAX_NUM)
        return num;
    ++pass_zero;
    // std::cout << "Count pass zero: " << pass_zero << std::endl;
    return reduce(num - MAX_NUM, pass_zero);
}

int main()
{
    int count_zero = 0;
    int count_pass_zero = 0;

    int current_point = 50;

    auto list = InputHelper::read_file("day_1_input.txt");
    
    for(auto const& pair : list)
    {
        int temp;
        pair.dir == LEFT ? temp = current_point - reduce(pair.value, count_pass_zero) : temp = current_point + reduce(pair.value, count_pass_zero);

        if(temp == MIN_NUM || temp == MAX_NUM) ++count_zero;
        else if((current_point != MIN_NUM && temp < MIN_NUM) || (current_point != MAX_NUM && temp > MAX_NUM) ) ++count_pass_zero;
        
        current_point = calculate(current_point, temp, pair.dir);
    }

    std::cout << "Result: " << count_zero +  count_pass_zero << std::endl;

    return 0;
}