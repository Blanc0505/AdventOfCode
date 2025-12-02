#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

bool isInvalidID(long long n)
{
    std::string s = std::to_string(n);
    if(s.length() % 2 != 0) return false;

    int half = s.length() / 2;
    std::string firstPart = s.substr(0, half);
    std::string secondPart = s.substr(half);

    if(firstPart == secondPart) return true;

    return false;
}

bool isInvalidIDZusatz(long long n)
{
    std::string s = std::to_string(n);
    int len = s.length();
    if(len == 1) return false;

    std::string block;
    for(int i = 1; i <= len/2; i++)
    {
        bool allSame = true;
        if(len % i != 0) continue;
        block = s.substr(0, i);
        for(int j = i; j <= len - i; j += i)
        {
            std::string current = s.substr(j, i);
            if(current != block) 
            {
                allSame = false;
                break;
            }
        }
        if(allSame) return true;
    }
    return false;
}

int main()
{
    std::string filename = "Day2_input.txt";
    std::ifstream file (filename);
    
    if(!file.is_open())
    {
        std::cerr << "Couldnt open file";
        return 1;
    }

    std::string full_line;
    
    if(!std::getline(file, full_line))
    {
        std::cerr << "Couldnt read line";
        return 1;
    }
    
    std::stringstream ss(full_line);
    std::string rangeStr;

    long long SumInvalidID = 0;

    while(std::getline(ss, rangeStr, ','))
    {
        std::size_t dashPos = rangeStr.find('-');

        std::string startStr = rangeStr.substr(0, dashPos);
        std::string endStr = rangeStr.substr(dashPos + 1);

        long long start = std::stoll(startStr); 
        long long end = std::stoll(endStr);
        
        for(long long id = start; id <= end; id++ )
        {
            // Part 1: if(isInvalidID(id)) SumInvalidID += id;
            // Part 2: if(isInvalidIDZusatz(id)) SumInvalidID += id;
        }
    }   
    
    std::cout << SumInvalidID << std::endl;
}