#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

long long SumOfAnswers(std::vector<std::string>& grid, std::vector<std::pair<int, int>>& NumBlocks, int rows, int cols)
{
    long long totalSum = 0;

    for(const auto& [startCol, endCol] : NumBlocks)
    {
        std::vector<int> numbers;
        char op;
        for(int r = 0; r < rows; ++r)
        {
            std::string currentNum;

            for(int c = startCol; c <= endCol; ++c)
            {
                if(grid[r][c] != ' ' && grid[r][c] != '*' && grid[r][c] != '+')
                {
                    currentNum.push_back(grid[r][c]);
                }
                else if(grid[r][c] == '*') op = '*';
                else if(grid[r][c] == '+') op = '+';
            }
            if(!currentNum.empty()) numbers.push_back(std::stoi(currentNum));
        }
        if(op == '*')
        {
            long long erg = 1;
            for(auto& num : numbers)
            {
                erg *= num;
            }
            totalSum += erg;
        }
        else if(op == '+')
        {
            long long erg = 0;
            for(auto& num : numbers)
            {
                erg += num;
            }
            totalSum += erg;
        }
    }
    return totalSum;
}


int main()
{
    std::string filename = "Day6_input.txt";
    std::ifstream file (filename);

    if(!file.is_open())
    {
        std::cerr << "Couldnt find file";
        return 1;
    }   

    std::string line;
    std::vector<std::string> grid;

    while(std::getline(file, line))
    {
        if(line.empty()) continue;
        grid.push_back(line);
    }
    int rows = grid.size();
    int cols = grid[0].size();

    std::vector<bool> colEmpty(cols, true);

    for(int c = 0; c < cols; ++c)
    {
        for(int r = 0; r < rows; ++r)
        {
            if(grid[r][c] != ' ')
            {
                colEmpty[c] = false;
                break;
            }
        }
    }

    std::vector<std::pair<int, int>> NumBlocks;
    bool inBlock = false;
    int startCol = 0;

    for(int c = 0; c < cols; ++c)
    {
        if(!colEmpty[c])
        {
            if(!inBlock)
            {
                inBlock = true;
                startCol = c;
            }
        }
        else
        {
            if(inBlock)
            {
                NumBlocks.push_back({startCol, c - 1});
                inBlock = false;
            }
        }
    }
    if(inBlock)
    {
        NumBlocks.push_back({startCol, cols - 1});
    }


    std::cout << "Part 1: " << SumOfAnswers(grid, NumBlocks, rows, cols) << std::endl;

    for(const auto& c : NumBlocks)
    {
        // For DB: std::cout << "[ " << c.first << ", " << c.second << " ]" << std::endl;
    }
}