/* 
The Elf says they've stopped producing snow because they aren't getting any water!
He isn't sure why the water stopped; however, he can show you how to get to the water source to check it out for yourself. 
It's just up ahead!

As you continue your walk, the Elf poses a second question: in each game you played, what is the fewest number of cubes of each color 
that could have been in the bag to make the game possible?

Again consider the example games from earlier:

Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue
Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red
Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red
Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green

    In game 1, the game could have been played with as few as 4 red, 2 green, and 6 blue cubes. 
    If any color had even one fewer cube, the game would have been impossible.
    Game 2 could have been played with a minimum of 1 red, 3 green, and 4 blue cubes.
    Game 3 must have been played with at least 20 red, 13 green, and 6 blue cubes.
    Game 4 required at least 14 red, 3 green, and 15 blue cubes.
    Game 5 needed no fewer than 6 red, 3 green, and 2 blue cubes in the bag.

The power of a set of cubes is equal to the numbers of red, green, and blue cubes multiplied together. 
The power of the minimum set of cubes in game 1 is 48. In games 2-5 it was 12, 1560, 630, and 36, respectively. 
Adding up these five powers produces the sum 2286.

For each game, find the minimum set of cubes that must have been present. What is the sum of the power of these sets?
 */

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>
#include <numeric>
#include <functional>


int getGameID(std::string &s){

    std::string strGameID = s.substr(0, s.find(": "));
    s = s.erase(0, strGameID.size() + 2);
    strGameID = strGameID.erase(0, strGameID.find(" "));
    int gameID = std::stoi(strGameID);
    return gameID;

}

std::vector<std::string> getParsed(std::string &s, std::string sep){
    
    std::string sub;
    std::vector<std::string> subvec;
    size_t pos = s.find(sep);

    while (pos != std::string::npos){
        sub = s.substr(0, pos);
        subvec.push_back(sub);
        s.erase(0, pos + sep.size());
        pos = s.find(sep);
    }
    subvec.push_back(s);
    s.erase(0, s.size());
    
    return subvec;
}

bool isPossible(std::vector<std::string> game){

    std::map<std::string, int> limits = {{"red", 12}, {"green", 13}, {"blue", 14}};

    bool possible = 1;
    int n;

    for (auto trial : game){
        auto cubes = getParsed(trial, ", ");
        for (auto c : cubes){
            for (auto it = limits.begin(); it != limits.end(); ++it){
                size_t pos = (c.find(it->first));
                if (pos != std::string::npos){
                    c.erase(pos-1, c.size());
                    n = std::stoi(c);
                    if (n > limits[it->first]){
                        possible = 0;
                        break;
                    }
                }
            }
            if (!possible) break;
        }
        if (!possible) break;
    }

    return possible;
}


std::vector<int> getMinSet(std::vector<std::string> game){

    std::vector<std::string> colors = {"red", "green", "blue"};
    std::vector<int> minSet = {0, 0, 0};
    int n;
    
    for (auto trial : game){

        auto cubes = getParsed(trial, ", ");
        for (auto c : cubes){

            for (int i = 0; i < colors.size(); ++i){
                size_t pos = (c.find(colors[i]));
                if (pos != std::string::npos){
                    c.erase(pos-1, c.size());
                    n = std::stoi(c);
                    minSet[i] = (n > minSet[i]) ? n : minSet[i];
                    break;
                }

            }

        }

    }

    return minSet;
}


long long getCubesPower(std::vector<int> minSet){
    auto p = std::accumulate(minSet.begin(), minSet.end(), 1, std::multiplies<>());
    return p;
}


int main(int argc, char **argv)
{

    std::ifstream fin(argv[1], std::ios::in);
    std::string line;
    long long sum = 0;

    while (getline(fin, line)){

        int gameID = getGameID(line);
        auto strGames = getParsed(line, "; ");
        auto minSet = getMinSet(strGames);
        auto cp = getCubesPower(minSet);
        sum += cp;

    }

    std::cout << sum << std::endl;

    fin.close();

    return 0;
}
