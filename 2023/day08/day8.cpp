
/* 
RL

AAA = (BBB, CCC)
BBB = (DDD, EEE)
CCC = (ZZZ, GGG)
DDD = (DDD, DDD)
EEE = (EEE, EEE)
GGG = (GGG, GGG)
ZZZ = (ZZZ, ZZZ)

Starting with AAA, you need to look up the next element based on the next left/right instruction 
in your input. In this example, start with AAA and go right (R) by choosing the right element of 
AAA, CCC. Then, L means to choose the left element of CCC, ZZZ. By following the left/right instructions, 
you reach ZZZ in 2 steps.

Of course, you might not find ZZZ right away. If you run out of left/right instructions, 
repeat the whole sequence of instructions as necessary: RL really means RLRLRLRLRLRLRLRL... 
and so on. For example, here is a situation that takes 6 steps to reach ZZZ:

LLR

AAA = (BBB, BBB)
BBB = (AAA, ZZZ)
ZZZ = (ZZZ, ZZZ)

Starting at AAA, follow the left/right instructions. How many steps are required to reach ZZZ?
*/

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>


int main(int argc, char** argv){

    std::ifstream fin(argv[1], std::ios::in);
    
    std::string directions, line;
    getline(fin, directions);
    getline(fin, line);

    std::map<std::string, std::pair<std::string, std::string>> map;
    
    std::string loc, left, right;
    while (getline(fin, line)){
        loc = line.substr(0, 3);
        left = line.substr(7, 3);
        right = line.substr(12, 3);
        map.insert({loc, std::make_pair(left, right)});
    } 

    fin.close();
    
    std::string start = "NHA";
    std::string end = "DDZ";

    loc = start;
    int steps = 1;
    while (loc != end){
        for (int i = 0; i < directions.size(); ++i){
            if (directions[i] == 'L'){
                loc = map[loc].first;
            } else {
                loc = map[loc].second;
            }
            if (loc == end) break;
            steps++;
        }
    }

    std::cout << steps << std::endl;

    return 0;
}







