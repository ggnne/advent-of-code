
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <climits>
#include <cassert>

typedef unsigned long long int L;

std::vector<std::string> readBLock(std::ifstream &fin){

    std::string line;
    std::vector<std::string> block;
    while (std::getline(fin, line) && line.size() > 0){
        block.push_back(line);
    }
    return block;
}

std::vector<L> getSeeds(std::ifstream &fin){
    
    auto block = readBLock(fin);
    auto line = block[0];

    line = line.erase(0, line.find(": ") + 2);

    std::stringstream ss(line);
    
    L seed;
    std::vector<L> seeds;
    while(ss >> seed){
        seeds.push_back(seed);
    }

    return seeds;
}

std::vector<std::vector<std::vector<L>>> getAlmanac(std::ifstream &fin){

    L n;
    std::vector<std::vector<std::vector<L>>> almanac;
    std::vector<std::vector<L>> map;
    std::vector<L> row;
    std::stringstream ss;
    std::vector<std::string> block;

    block = readBLock(fin);
    while (block.size() > 0){

        for (int i = 1; i < block.size(); ++i){
            ss << block[i];
            while (ss >> n){
                row.push_back(n);
            }
            map.push_back(row);
            row.clear();
            ss.clear();
        }
        almanac.push_back(map);
        map.clear();
        block = readBLock(fin);
    }
    
    return almanac;
}


L testSeed(L seed, std::vector<std::vector<std::vector<L>>> &almanac){
    
    for (auto m : almanac){
        for (auto r : m){
            if (seed >= r[1] && seed <= (r[1] + r[2])){
                seed = r[0] + (seed - r[1]);
                break;
            }
        }
    }
    return seed;
}


int main(int argc, char** argv){

    std::ifstream fin(argv[1], std::ios::in);

    auto seeds = getSeeds(fin);
    
    assert(seeds.size() > 0);

    auto almanac = getAlmanac(fin);

    L minLoc = ULLONG_MAX, loc;
    for (long long seed : seeds){
        loc = testSeed(seed, almanac); 
        minLoc = (loc < minLoc) ? loc : minLoc;
    }
    std::cout << minLoc << std::endl;
    
    return 0;
}