#include "../input_helper.h"

void part_1(const std::vector<std::pair<lazy, lazy>>& list_1, const std::vector<lazy>& list_2)
{
    int total_fresh = 0;

    std::unordered_map<lazy, int> fresh_list;

    for(auto const& pair : list_1)
    {
        lazy diff = pair.second - pair.first + 1; // Inclusive

        for(auto const& val : list_2)
        {
            if(fresh_list.contains(val) || val > pair.second || val < pair.first || pair.second - val > diff)
                continue;

            if(pair.second - val <= diff)
            {
                ++fresh_list[val];
                ++total_fresh;
            }
        }
    }
    std::cout << "Result part 1: " << total_fresh << std::endl;
}

std::pair<lazy, lazy> merge(const std::pair<lazy, lazy>& current_interval, const std::pair<lazy, lazy>& next_interval, std::vector<std::pair<lazy, lazy>>& merged_list)
{
    std::size_t current_index = merged_list.size() - 1;

    if(current_interval.second < next_interval.first)
    {
        merged_list.push_back(next_interval);
        current_index = merged_list.size() - 1;
    }
    else if(current_interval.first < next_interval.first && current_interval.second >= next_interval.first && current_interval.second <= next_interval.second)
    {
        merged_list[current_index] = {current_interval.first, next_interval.second};
    }
    else if(current_interval.first <= next_interval.first && current_interval.second >= next_interval.second)
    {
        merged_list[current_index] = {current_interval.first, current_interval.second};
    }
    else if(next_interval.first <= current_interval.first && next_interval.second >= current_interval.second)
    {
        merged_list[current_index] = {next_interval.first, next_interval.second};
    }

    return merged_list[current_index];
}   

void part_2(std::vector<std::pair<lazy, lazy>> list)
{
    lazy total_fresh_id = 0;   
    std::vector<std::pair<lazy, lazy>> merged_list;
    std::sort(list.begin(), list.end());

    std::pair<lazy, lazy> current_interval = {list[0].first, list[0].second};
    merged_list.push_back(current_interval);

    for(std::size_t i = 1; i < list.size(); ++i)
    {
        std::pair<lazy, lazy> next_interval = {list[i].first, list[i].second};
        current_interval = merge(current_interval, next_interval, merged_list);
    }

    for(auto const& val : merged_list)
        total_fresh_id += val.second - val.first + 1;
    
    std::cout << "Result part 2: " << total_fresh_id << std::endl;
}

int main()
{
    auto id_range = InputHelper::read_file4("day_5_input.txt").first;
    auto ingredient_it = InputHelper::read_file4("day_5_input.txt").second;

    part_1(id_range, ingredient_it);
    part_2(id_range);

    return 0;
}