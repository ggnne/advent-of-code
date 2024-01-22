
/* 
After examining the maps a bit longer, your attention is drawn to a curious fact: 
the number of nodes with names ending in A is equal to the number ending in Z! 
If you were a ghost, you'd probably just start at every node that ends with A 
and follow all of the paths at the same time until they all simultaneously end up 
at nodes that end with Z.

For example:

LR

11A = (11B, XXX)
11B = (XXX, 11Z)
11Z = (11B, XXX)
22A = (22B, XXX)
22B = (22C, 22C)
22C = (22Z, 22Z)
22Z = (22B, 22B)
XXX = (XXX, XXX)

Here, there are two starting nodes, 11A and 22A (because they both end with A). 
As you follow each left/right instruction, use that instruction to simultaneously 
navigate away from both nodes you're currently on. Repeat this process until all of 
the nodes you're currently on end with Z. (If only some of the nodes you're on end with Z, 
they act like any other node and you continue as normal.) 
In this example, you would proceed as follows:

    Step 0: You are at 11A and 22A.
    Step 1: You choose all of the left paths, leading you to 11B and 22B.
    Step 2: You choose all of the right paths, leading you to 11Z and 22C.
    Step 3: You choose all of the left paths, leading you to 11B and 22Z.
    Step 4: You choose all of the right paths, leading you to 11Z and 22B.
    Step 5: You choose all of the left paths, leading you to 11B and 22C.
    Step 6: You choose all of the right paths, leading you to 11Z and 22Z.

So, in this example, you end up entirely on nodes that end in Z after 6 steps.

Simultaneously start on every node that ends with A. How many steps does 
it take before you're only on nodes that end with Z?
*/

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <queue>
#include <algorithm>

typedef long long int L;

L gcd(L a, L b){
    L t;
    while (b != 0){
        t = b;
        b = a % b;
        a = t;
    }
    return a;
}

L lcm(std::vector<L>& v){
    L out = v[0];
    for (int i = 1; i < v.size(); ++i){
        out = (v[i] * out) / (gcd(v[i], out));
    }
    return out;
}


int main(int argc, char** argv){

    std::ifstream fin(argv[1], std::ios::in);
    
    std::string directions, line;
    getline(fin, directions);
    getline(fin, line);

    std::map<std::string, std::pair<std::string, std::string>> map;
    
    std::string loc, left, right;
    std::vector<std::string> start;
    while (getline(fin, line)){
        loc = line.substr(0, 3);
        left = line.substr(7, 3);
        right = line.substr(12, 3);
        map.insert({loc, std::make_pair(left, right)});
        if (loc[2] == 'A'){
            start.push_back(loc);
        }
    } 

    fin.close();

    std::vector<L> stepsV;
    for (int n = 0; n < start.size(); ++n){
        loc = start[n];
        L steps = 0;
        while (loc[2] != 'Z'){
            for (L i = 0; i < directions.size(); ++i){
                if (directions[i] == 'L'){
                    loc = map[loc].first;
                } else {
                    loc = map[loc].second;
                }
                steps++;
                if (loc[2] == 'Z') break;
            }
        }
        stepsV.push_back(steps);
    }

    std::sort(stepsV.rbegin(), stepsV.rend());

    std::cout << lcm(stepsV) << std::endl;

    return 0;
}







