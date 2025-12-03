#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>


int LargestVolt(std::string& s)
{
    int maxJoltage = 0;
    int len = s.length();
    
    for(int i = 0; i < len-1; i++)
    {
        int d1 = s[i] - '0';
        for(int j = i+1; j < len; j++)
        {
            int d2 = s[j] - '0';
            int val = 10 * d1 + d2;
            if(val > maxJoltage)
            {
                maxJoltage = val;
            }
        }
    }
    return maxJoltage;
}

long long LargestVoltZusatz(std::string& s)
{
    int len = s.length();
    int remove = len - 12;
    std::string result;
    
    for(char c : s)
    {
        while(remove > 0 && !result.empty() && result.back() < c)
        {
            result.pop_back();
            remove--;
        }
        result.push_back(c);
    }
    
    result.resize(12);
    long long maxJoltage = 0;
    for(char c : result)
    {
        int d = c - '0';
        maxJoltage = maxJoltage * 10 + d;
    }
    return maxJoltage;
}

int main()
{
    std::string filename = "Day3_input.txt";
    std::ifstream file (filename);

    if(!file.is_open())
    {
        std::cerr << "Couldnt find file";
        return 1;
    }

    std::string line;
    long long totalJoltage = 0;

    while(std::getline(file, line))
    {
        // Part 1: totalJoltage += LargestVolt(line);
        // Part 2: totalJoltage += LargestVoltZusatz(line);
    }

    std::cout << totalJoltage << std::endl;
}
