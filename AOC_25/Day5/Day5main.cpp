#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

bool isFresh(std::vector<std::pair<long long, long long>>& ranges, std::string& s)
{
    long long num = std::stoll(s);

    for(const auto& c : ranges)
    {
        if(num >= c.first && num <= c.second) return true;
    }
    return false;
}


long long isFreshCount(std::vector<std::pair<long long, long long>>& ranges)
{
    long long freshCount = 0;
    
    std::sort(ranges.begin(), ranges.end());
    long long currentStart = ranges[0].first;
    long long currentEnd = ranges[0].second;

    std::vector<std::pair<long long, long long>> sortedRanges;

    for(auto& [s, e] : ranges)
    {
        if(s <= currentEnd)
        {
            currentEnd = std::max(currentEnd, e);
        }
        else 
        {
        sortedRanges.push_back({currentStart, currentEnd});
        currentStart = s;
        currentEnd = e;
        }
    }
    sortedRanges.push_back({currentStart, currentEnd});

    for(const auto& c : sortedRanges)
    {
        // DB: std::cout << "[ " << c.first << ", " << c.second << " ]" << std::endl;
        freshCount += (c.second - c.first) + 1;
    }
    return freshCount;
}


int main()
{

    std::string filename = "Day5_input.txt";
    std::ifstream file (filename);

    if(!file.is_open())
    {
        std::cerr << "Couldnt find file";
        return 1;
    }   

    std::string line;
    std::vector<std::pair<long long, long long>> ranges;
    bool rangeInput = true;
    int freshCount = 0;
    long long freshCountPartTwo = 0;
    while(std::getline(file, line))
    {
        if(line.empty())
        {
            rangeInput = false;
            continue;
        } 

        if(rangeInput)
        {
            std::size_t dashPos = line.find('-');
            std::string StrStartRange = line.substr(0, dashPos);
            std::string StrEndRange = line.substr(dashPos+1);

            long long startRange = std::stoll(StrStartRange);
            long long endRange = std::stoll(StrEndRange);
            
            ranges.push_back({startRange, endRange});
        } 
        else 
        {    
            freshCountPartTwo = isFreshCount(ranges); 
            if(isFresh(ranges, line)) ++freshCount;
        }
    }
    std::cout << "Part 1: " << freshCount << std::endl;
    std::cout << "Part 2: " << freshCountPartTwo << std::endl;
}