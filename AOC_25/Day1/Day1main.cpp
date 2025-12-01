#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int wrapOnDial(int oldPos, int distance, bool direction)
{
    // direction = true --> (R)
    // direction = false --> (L)

    int delta = direction ? distance : -distance;

    int newNum = oldPos + delta;
    newNum = (newNum % 100 + 100) % 100;
    return newNum;
}

int wrapOnDialZusatz(int oldPos, int distance, bool direction)
{
    int newPos;
    int countZero = 0;
    int step = direction ? 1 : -1;
    
    int tmp = distance;
    while(tmp != 0)
    {
        newPos = oldPos + step;
        newPos = (newPos % 100 + 100) % 100;
        if(newPos == 0) ++countZero;
        oldPos = newPos;
        tmp--;
    }
    return countZero;
}

int main()
{
    std::string filename = "Day1_input.txt";

    std::ifstream file(filename);
    if(!file.is_open()) 
    {
        std::cerr << "Couldnt open file";
        return 1;
    }
    
    std::string line;
    int position = 50;
    int zeroCountPartOne = 0;
    int zeroCountPartTwo = 0;

    while(std::getline(file, line))
    {
        if(line.empty()) continue;

        char dir = line[0];
        int distance = std::stoi(line.substr(1));
        
        bool direction = (dir == 'R');
        
        zeroCountPartTwo += wrapOnDialZusatz(position, distance, direction); 

        position = wrapOnDial(position, distance, direction);
        if(position == 0) ++zeroCountPartOne;    
    }
    std::cout << zeroCountPartTwo;
}
