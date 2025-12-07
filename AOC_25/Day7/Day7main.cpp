#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

long long CountTotalSplits(std::vector<std::string>& grid, std::vector<std::vector<bool>>& visitedGrid, std::vector<std::pair<int, int>>& beamPos, int rows, int cols)
{
    long long totalSplits = 0;
    while(!beamPos.empty())
    {
        auto [r, c] = beamPos.back();
        beamPos.pop_back();

        int newR = r + 1;
        int newC = c;

        if(newR >= rows || newC >= cols || newR < 0 || newC < 0) continue;

        char cell = grid[newR][newC];
        if(cell == '.')
        {
            if(visitedGrid[newR][newC] == true) continue;
            visitedGrid[newR][newC] = true;
            beamPos.push_back({newR, newC});
        } 
        else if(cell == '^')
        {
            totalSplits++;
            if(newC-1 >= 0 && !visitedGrid[newR][newC-1]) 
            {
                visitedGrid[newR][newC-1] = true;
                beamPos.push_back({newR, newC-1});
            }
            if(newC+1 < cols && !visitedGrid[newR][newC+1])
            {
                visitedGrid[newR][newC+1] = true;
                beamPos.push_back({newR, newC+1});
            } 
        }
    }
    return totalSplits;
}


long long CountTotalTimelines(std::vector<std::string>& grid, std::vector<std::pair<int, int>>& beamPos, int rows, int cols)
{
    long long totalTimelines = 0;
    std::vector<std::vector<long long>> ways(rows, std::vector<long long>(cols, 0));

    auto [S_row, S_col] = beamPos.back();
    ways[S_row][S_col] = 1;

    for(int r = 0; r < rows; ++r)
    {
        for(int c = 0; c < cols; ++c)
        {
            long long cw = ways[r][c];

            if(cw == 0) continue;

            int newR = r + 1;
            int newC = c;

            if(newR >= rows)
            {
                totalTimelines += cw;
                continue;
            }

            char cell = grid[newR][newC];

            if(cell == '.')
            {
                ways[newR][newC] += cw;
            }
            else if(cell == '^')
            {
                if(newC-1 >= 0)
                {
                    ways[newR][newC-1] += cw;
                }
                else
                {
                    totalTimelines += cw;
                }

                if(newC+1 < cols)
                {
                    ways[newR][newC+1] += cw;
                }
                else
                {
                    totalTimelines += cw;
                }
            }
        }
    }
    return totalTimelines;
}



int main()
{
    std::string filename = "Day7_input.txt";
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


    std::vector<std::pair<int, int>> beamPos;
    for(int r = 0; r < rows; ++r)
    {
        for(int c = 0; c < cols; ++c)
        {
            if(grid[r][c] == '.') continue;
            else if(grid[r][c] == '^') continue;
            else if(grid[r][c] == 'S')
            {
                beamPos.push_back({r, c});
                break;
            }
        }
    }
    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));

    long long partOne = CountTotalSplits(grid, visited, beamPos, rows, cols);
    long long partTwo = CountTotalTimelines(grid, beamPos, rows, cols);

    std::cout << "Part 1: " <<  partOne << std::endl;
    std::cout << "Part 2: " << partTwo << std::endl;
}