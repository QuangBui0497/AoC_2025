#include "../input_helper.h"

long long int count_digits(long long int num)
{
    long long int digits = 0;
    while(num > 0)
    {
        num /= 10;
        ++digits;
    }
    return digits;
}

void helper(long long int first, long long int last, long long int digits, long long int& total)
{
    for(long long int i = first; i <= last; ++i)
    {
        long long int pow_result = std::pow(10, digits / 2);
        long long int quotient  = i / pow_result;
        long long int remainder = static_cast<long long int>(i % pow_result);

        if(quotient == remainder)
            total += i;
    }
}

void helper_2(long long int first, long long int last, long long int& total)
{
    for(long long int num = first; num <= last; ++num)
    {
        long long int digits = count_digits(num);

        for(long long int pattern_length = 1; pattern_length <= digits / 2; ++pattern_length)
        {
            long long int pattern_count = digits / pattern_length;

            if(pattern_count < 2 || digits % pattern_length != 0)
                continue;

            bool is_repeated = true;

            if(digits % pattern_length == 0)
            {
                long long int pow_result = std::pow(10, pattern_length);
                long long int quotient = num;
                long long int remainder = static_cast<long long int>(num % pow_result);
                
                while(quotient > 0)
                {
                    if(quotient % pow_result != remainder)
                    {
                        is_repeated = false;
                        break;
                    }
                    quotient /= pow_result;
                }
            }

            if(is_repeated)
            {
                total += num;
                break; // Once per number
            }
        }
    }
}

void part_1(const std::vector<InputHelper::ID>& list)
{
    long long int total = 0;

    for(auto const& pair : list)
    {
        long long int digits_first = count_digits(pair.first);
        long long int digits_last = count_digits(pair.last);

        if((digits_first % 2) != 0 && (digits_last % 2) != 0)
            continue;

        if((digits_first % 2) != 0)
        {
            // If the first number has an odd number of digits but the last number has an even number of digits,
            // skip everything with odd digit length. Jump to the first number that has the same even digit count
            // as the last number.
            //
            // Example: For range 998–1012, 998 has 3 digits (odd), 1012 has 4 digits (even).
            // So we skip 998–999 and start checking from 1000.

            long long int first = std::pow(10, digits_first); 
            helper(first, pair.last, digits_last, total);
        }
        else
        {
            helper(pair.first, pair.last, digits_first, total);
        }
    }

    std::cout << "Result part 1: " << total << std::endl;
}

void part_2(const std::vector<InputHelper::ID>& list)
{
    long long int total = 0;

    for(auto const& pair : list)
        helper_2(pair.first, pair.last, total);

    std::cout << "Result part 2: " << total << std::endl;
}

int main()
{
    auto list = InputHelper::read_file2("day_2_input.txt");

    part_1(list);
    part_2(list);

    return 0;
}