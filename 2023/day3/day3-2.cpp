/* 
The missing part wasn't the only issue - one of the gears in the engine is wrong. 
A gear is any * symbol that is adjacent to exactly two part numbers. Its gear ratio is the result of multiplying those two numbers together.

This time, you need to find the gear ratio of every gear and add them all up so that the engineer can figure out which gear needs to be replaced.

Consider the same engine schematic again:

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

In this schematic, there are two gears. The first is in the top left; it has part numbers 467 and 35, so its gear ratio is 16345. 
The second gear is in the lower right; its gear ratio is 451490. 
(The * adjacent to 617 is not a gear because it is only adjacent to one part number.) Adding up all of the gear ratios produces 467835.

What is the sum of all of the gear ratios in your engine schematic?
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

    std::vector<std::vector<int>> gears_coords;

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

            if (ch == '*'){
                std::vector<int> coord = {N, M};
                gears_coords.push_back(coord);
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

    for (int i = 0; i < gears_coords.size(); ++i){

        auto coord = gears_coords[i];
        int gearratio = 1, counter = 0;

        for (int j = 0; j < nums.size(); ++j){

            n = nums[j];
            auto tempset = nums_coords[j]; 
            if (tempset.count(coord)){
                gearratio *= n;
                counter++;
            }

            if (counter > 3) break;
        }

        if (counter == 2){
            sum += gearratio;
        }
    }

    std::cout << sum << std::endl;

    return 0;
 }