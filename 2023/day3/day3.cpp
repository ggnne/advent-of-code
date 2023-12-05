/* 
The engine schematic (your puzzle input) consists of a visual representation of the engine.
There are lots of numbers and symbols you don't really understand, but apparently any number adjacent to a symbol,
even diagonally, is a "part number" and should be included in your sum. (Periods (.) do not count as a symbol.)

Here is an example engine schematic:

467..114..
...*......
..35..633.
......#...
617*......
.....+.58.
..592.....
......755.
...$.*....
.664.598..

In this schematic, two numbers are not part numbers because they are not adjacent to a symbol:
114 (top right) and 58 (middle right). Every other number is adjacent to a symbol and so is a part number; their sum is 4361.

Of course, the actual engine schematic is much larger. What is the sum of all of the part numbers in the engine schematic?
 */

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <utility>
#include <locale>
#include <set>
#include <map>


std::vector<std::vector<int>> getOffsetCoords(std::vector<int> coord){

    std::vector<std::vector<int>> rose = {{1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}};
    std::vector<std::vector<int>> out;

    int x, y;
    for (int i = 0; i < rose.size(); ++i){
        x = coord[0] + rose[i][0];
        y = coord[1] + rose[i][1];
        std::vector<int> newcoord = {x, y};
        out.push_back(newcoord);
    }

    return out;
}



int main(int argc, char** argv){

    std::fstream fin(argv[1], std::fstream::in);
        
    std::vector<std::vector<char>> table;
    std::vector<char> row;

    std::string tempstr;
    std::vector<int> nums;
    std::vector<std::set<std::vector<int>>> nums_coords;
    std::set<std::vector<int>> tempset;

    char ch;
    int N = 0, M = 0, sum = 0, n;
    while (fin >> std::noskipws >> ch) {

        if (std::isdigit(ch)){
            
            std::vector<int> coord = {N, M};
            auto offset = getOffsetCoords(coord);
            for (const auto &c : offset){
                tempset.insert(c);
            }
            tempstr += ch;

        } else {

            if (tempstr.size() > 0){
                n = std::stoi(tempstr);
                nums.push_back(n);
                nums_coords.push_back(tempset);
                tempstr.clear();
                tempset.clear();
            }

            if (ch == '\n'){
                N++;
                M = 0;
                table.push_back(row);
                row.clear();
                continue;
            }
        }
        
        row.push_back(ch);
        M++;
    
    }

    N++;
    table.push_back(row);

    for (int i = 0; i < nums.size(); ++i){

        n = nums[i];
        tempset = nums_coords[i];
        bool add = 0;

        for (auto it = tempset.begin(); it != tempset.end(); ++it){

            auto coord = *it;
            int x = coord[0], y = coord[1];

            if (x >= 0 && y >= 0 && x < N  && y < M){
                ch = table[x][y];
                if (!std::isdigit(ch) && (ch != '.')){
                    add = 1;
                    break;
                } 
            }
        }

        if (add){
            sum += n;
        }
    }    

    std::cout << sum << std::endl;

    return 0;
 }