
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <vector>
#include <cmath>

std::vector<std::string> readInput(std::ifstream& fin){
    
    std::vector<std::string> table;
    std::string line;

    while (getline(fin, line)){

        if (line.find('#') == std::string::npos)
            table.push_back(line);

        table.push_back(line);
    }

    std::vector<int> colsToAdd;
    for (int j = 0; j < table[0].size(); ++j){
        bool hasG = 0;
        for (int i = 0; i < table.size(); ++i){
            if (table[i][j] == '#'){
                hasG = 1;
                break;
            }
        }
        if (!hasG)
            colsToAdd.push_back(j);
    }   

    int added = 0;
    for (const auto& s : colsToAdd){
        for (int i = 0; i < table.size(); ++i){
            table[i].insert(table[i].begin() + s + added, '.');
        }
        added++;
    }   

    colsToAdd.clear();
    colsToAdd.shrink_to_fit();
    fin.close();

    return table;
}

int main(int argc, char** argv){

    std::ifstream fin(argv[1], std::ios::in);
    std::vector<std::string> table = readInput(fin);

    int N = table.size(), M = table[0].size();
    std::vector<std::vector<int>> galaxies;
    std::vector<int> coord;
    for (int i = 0; i < N; ++i){
        for (int j = 0; j < M; ++j){
            if (table[i][j] == '#'){
                coord = {i, j};
                galaxies.push_back(coord);
            }
        }
    }

    int d;    
    int sum  = 0, pairs = 0;
    for (int i = 0; i < galaxies.size() - 1; ++i){

        auto start = galaxies[i];
        
        for (int j = i + 1; j < galaxies.size(); ++j){

            auto to = galaxies[j];
            d = abs(start[0] - to[0]) + abs(start[1] - to[1]);
            sum += d;
            pairs++;
        }
    }

    std::cout << sum << std::endl;

    return 0;
}