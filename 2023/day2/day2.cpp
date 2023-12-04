/* 
You play several games and record the information from each game (your puzzle input). 
Each game is listed with its ID number (like the 11 in Game 11: ...) followed by a semicolon-separated
list of subsets of cubes that were revealed from the bag (like 3 red, 5 green, 4 blue).

For example, the record of a few games might look like this:

Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue
Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red
Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red
Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green

In game 1, three sets of cubes are revealed from the bag (and then put back again).

The first set is 3 blue cubes and 4 red cubes; the second set is 1 red cube, 2 green cubes, and 6 blue cubes; the third set is only 2 green cubes.

The Elf would first like to know which games would have been possible if the bag contained only 12 red cubes, 13 green cubes, and 14 blue cubes?
In the example above, games 1, 2, and 5 would have been possible if the bag had been loaded with that configuration.
However, game 3 would have been impossible because at one point the Elf showed you 20 red cubes at once; similarly, game 4 would also have been impossible
because the Elf showed you 15 blue cubes at once. If you add up the IDs of the games that would have been possible, you get 8.

Determine which games would have been possible if the bag had been loaded with only 12 red cubes, 13 green cubes, and 14 blue cubes.
What is the sum of the IDs of those games?
 */

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>


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

int main(int argc, char **argv)
{

    std::ifstream fin(argv[1], std::ios::in);
    std::string line;
    int sum = 0;

    while (getline(fin, line)){

        int gameID = getGameID(line);
        auto strGames = getParsed(line, "; ");
        bool possible = isPossible(strGames);
        if (possible){
            sum += gameID;
        }

    }

    std::cout << sum << std::endl;

    fin.close();

    return 0;
}
