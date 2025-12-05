#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>



long long CheckNeighboors(std::vector<std::string>& grid, int rows, int cols)
{
    long long goodRolls = 0;
    std::vector<std::pair<int, int>> neighborOffsets =
    {
        {-1, 0},    // Directly above
        {1, 0},     // Directly below
        {0, -1},    // To the left
        {0, 1},     // To the right
        {-1, -1},   // Diagonal upper left
        {-1, 1},    // Diagonal upper right
        {1, -1},    // Diagonal lower left
        {1, 1}      // Diagonal lower right
    };

    for(int i = 0; i < rows; ++i)
    {
        for(int j = 0; j < cols; ++j)
        {
            if(grid[i][j] != '@') continue;

            int neighborRolls = 0;
            
            for(const auto& offset: neighborOffsets)
            {
                int ri = i + offset.first;
                int rj = j + offset.second;
                    
                if(ri < 0 || rj < 0 || ri >= rows || rj >= cols) continue;
                    
                if(grid[ri][rj] == '@') ++neighborRolls;
            }
            if(neighborRolls < 4) ++goodRolls;
        }
    }
    return goodRolls;
}

long long CheckNeighboorsZusatz(std::vector<std::string>& grid, int rows, int cols)
{
    long long totalRemoved = 0;
    
    std::vector<std::pair<int, int>> neighborOffsets =
    {
        {-1, 0},    // Directly above
        {1, 0},     // Directly below
        {0, -1},    // To the left
        {0, 1},     // To the right
        {-1, -1},   // Diagonal upper left
        {-1, 1},    // Diagonal upper right
        {1, -1},    // Diagonal lower left
        {1, 1}      // Diagonal lower right
    };

    while(true)
    {
        std::vector<std::pair<int, int>> toRemove;
        
        for(int i = 0; i < rows; ++i)
        {
            for(int j = 0; j < cols; ++j)
            {
                if(grid[i][j] != '@') continue;

                int neighborRolls = 0;
                
                for(const auto& offset: neighborOffsets)
                {
                    int ri = i + offset.first;
                    int rj = j + offset.second;
                        
                    if(ri < 0 || rj < 0 || ri >= rows || rj >= cols) continue;
                        
                    if(grid[ri][rj] == '@') ++neighborRolls;
                }
                if(neighborRolls < 4) toRemove.push_back({i, j});
            }
        }
        if(toRemove.empty()) break;

        for(auto [r, c] : toRemove)
        {
            grid[r][c] = '.';
            ++totalRemoved;
        }
    }
    return totalRemoved;
}

int main()
{
    std::string filename = "Day4_input.txt";
    std::ifstream file (filename);

    if(!file.is_open())
    {
        std::cerr << "Couldnt find file";
        return 1;
    }

    std::vector<std::string> grid;
    std::string line;
    while(std::getline(file, line))
    {
        if(line.empty()) continue;
        grid.push_back(line);
    }
    
    int rows = grid.size();
    int cols = grid[0].size();
    
    long long result = CheckNeighboors(grid, rows, cols);
    long long resultZusatz = CheckNeighboorsZusatz(grid, rows, cols);

    std::cout << "Part 1: " << result << std::endl;
    std::cout << "Part 2: " << resultZusatz << std::endl;
}