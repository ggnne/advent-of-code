/* 
The pipes are arranged in a two-dimensional grid of tiles:

    | is a vertical pipe connecting north and south.
    - is a horizontal pipe connecting east and west.
    L is a 90-degree bend connecting north and east.
    J is a 90-degree bend connecting north and west.
    7 is a 90-degree bend connecting south and west.
    F is a 90-degree bend connecting south and east.
    . is ground; there is no pipe in this tile.
    S is the starting position of the animal; there is a pipe on this tile, but your sketch doesn't show what shape the pipe has.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <map>


bool check(char from, char to, std::vector<int> vd){

    if (to == '.')
        return 0;

    std::set<char> allowNorth = {'|', 'L', 'J'}, allowSouth = {'|','7','F'}, allowWest = {'-', 'J', '7'}, allowEast = {'-', 'L', 'F'};
    std::set<char> acceptNorth = {'|','7','F'}, acceptSouth = {'|', 'L', 'J'}, acceptWest = {'-', 'L', 'F'}, acceptEast = {'-', 'J', '7'};

    if (vd[0] == 1 && vd[1] == 0)
        return ((from == 'S') || allowSouth.count(from)) && (acceptSouth.count(to));

    if (vd[0] == -1 && vd[1] == 0)
        return ((from == 'S') || allowNorth.count(from)) && (acceptNorth.count(to));

    if (vd[0] == 0 && vd[1] == 1)
        return ((from == 'S') || allowEast.count(from)) && (acceptEast.count(to));

    if (vd[0] == 0 && vd[1] == -1)
        return ((from == 'S') || allowWest.count(from)) && (acceptWest.count(to));

    return 0;
}


int main(int argc, char** argv){

    std::ifstream fin(argv[1], std::ios::in);
    std::string line;
    std::vector<std::string> table;

    int I, J;
    while (std::getline(fin, line)){
        table.push_back(line);
        if (line.find("S") != std::string::npos){
            J = line.find("S");
            I = table.size() -1;
        }
    }

    int grid[table.size()][table[0].size()];
    for (int i = 0; i < table.size(); ++i){
        for (int j = 0; j < table[0].size(); ++j){
            grid[i][j] = 0;
        }
    }

    int maxDist = 0;

    std::queue<std::vector<int>> Q;
    std::vector<std::vector<int>> D = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
    std::set<std::vector<int>> visited;
    
    char from = table[I][J], to;
    std::vector<int> curr = {I, J}, next;
    Q.push(curr);

    while (!Q.empty()){

        curr = Q.front(); 
        Q.pop();
        visited.insert(curr);
        from = table[curr[0]][curr[1]];

        maxDist = std::max(maxDist, grid[curr[0]][curr[1]]);

        for (int k = 0; k < D.size(); ++k){
            next = {curr[0] + D[k][0], curr[1] + D[k][1]};
            to = table[next[0]][next[1]];
            if (check(from, to, D[k]) && !visited.count(next))
                Q.push(next);
                grid[next[0]][next[1]] = grid[curr[0]][curr[1]] + 1;
        }
    }

    std::cout << maxDist << std::endl;

    return 0;
}