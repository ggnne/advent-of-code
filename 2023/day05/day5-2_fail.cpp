#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <queue>
#include <cassert>

typedef long long int L;

struct Range{
    Range();
    Range(L a, L b);
    L lo;
    L hi;
    bool empty;
    void setHiLo(L a, L b);
};

Range::Range(){
    empty = 1;
}

Range::Range(L a, L b){
    lo = (a < b) ? a : b;
    hi = (lo == a) ? b : a;
    empty = 0;
}

void Range::setHiLo(L a, L b){
    lo = (a < b) ? a : b;
    hi = (lo == a) ? b : a;
    empty = 0;
}

Range operator&&(const Range &a, const Range &b){

    Range newR;
    if ((a.hi >= b.lo) && (a.lo <= b.hi)){
        L newLo = std::max(a.lo, b.lo);
        L newHi = std::min(a.hi, b.hi);
        newR.setHiLo(newLo, newHi);
    }

    return newR;
}

std::ostream &operator<<(std::ostream &out, const Range &r) {
    if (r.empty){
        return out << "[, ]";
    } else {
        return out << "[" << r.lo << ", " << r.hi << "]";
    }
}

struct RMap{
    RMap();
    RMap(std::vector<std::vector<L>> v);
    std::vector<Range> from;
    std::vector<L> shifts;
    std::vector<Range> apply(const Range &R);
};

RMap::RMap(){}

std::ostream &operator<<(std::ostream &out, const RMap &rm) {
    for (int i = 0; i < rm.from.size(); ++i){
        out << rm.from[i] << "(" << rm.shifts[i] << ")" << " ";
    }
    return out;
}

RMap::RMap(std::vector<std::vector<L>> v){

    from.clear();

    std::sort(v.begin(), v.end(), [](const std::vector<L> &left, const std::vector<L> &right) {return left[1] < right[1];});
    L shift;
    for (int i = 0; i < v.size(); ++i){
        Range f(v[i][1], v[i][1] + v[i][2] - 1);
        shift = v[i][0] - v[i][1];
        from.push_back(f);
        shifts.push_back(shift);
    }

}

std::vector<Range> RMap::apply(const Range &R){

    std::vector<Range> inters;
    std::vector<Range> out;
    std::vector<Range> fillGaps;
    Range inter;
    L shift;

    for (int i = 0; i < (this->from).size(); ++i){
        inter = (R && (this->from)[i]);
        if (!inter.empty){
            inters.push_back(inter);
            shift = (this->shifts)[i];
            inter.setHiLo(inter.lo + shift, inter.hi + shift);
            out.push_back(inter);
        }
    }

    if (inters.size() > 0){

        if (out[0].lo > R.lo){
            Range left(R.lo, out[0].lo - 1);
            // std::cout << R << " " << left << std::endl;
            fillGaps.push_back(left);
        }
                
        if (out[out.size()-1].hi < R.hi){
            Range right(out[out.size()-1].hi + 1, R.hi);
            // std::cout << R << " " << right << std::endl;
            fillGaps.push_back(right);
        }

        for (int i = 1; i < out.size(); ++i){
            if (out[i-1].hi < out[i].lo){
                Range mid(out[i-1].hi + 1, out[i].lo - 1);
                // std::cout << R << " " << mid << std::endl;
                fillGaps.push_back(mid);
            }
        }

    } else {

        fillGaps.push_back(R);

    }

    out.insert(out.end(), fillGaps.begin(), fillGaps.end());
    std::sort(out.begin(), out.end(), [](const Range &left, const Range &right) {return left.lo < right.lo;});

    return out;
}


std::vector<std::string> readBLock(std::ifstream &fin){

    std::string line;
    std::vector<std::string> block;
    while (std::getline(fin, line) && line.size() > 0){
        block.push_back(line);
    }
    return block;
}

std::vector<Range> getSeedsRanges(std::ifstream &fin){

    std::vector<std::string> block = readBLock(fin);
    block[0].erase(0, block[0].find(" ") + 1);

    std::stringstream ss(block[0]);
    std::vector<Range> seedsRanges;
    L seed, offset;
    while(ss >> seed){
        ss >> offset;
        Range r(seed, seed + offset);
        seedsRanges.push_back(r);
    }
    block.clear();
    block.shrink_to_fit();
    
    return seedsRanges;
}


std::vector<RMap> getAlmanac(std::ifstream &fin){

    std::vector<RMap> almanac;
    std::vector<std::vector<L>> vecMap;
    std::vector<L> row;
    L num;
    
    std::stringstream ss;
    std::vector<std::string> block;
    block = readBLock(fin);
    while (block.size() > 0){
        for (int i = 1; i < block.size(); ++i){
            ss << block[i];
            while (ss >> num){
                row.push_back(num);
            }
            vecMap.push_back(row);
            row.clear();
            ss.clear();
        }
        RMap map(vecMap);
        vecMap.clear();
        almanac.push_back(map);
        block = readBLock(fin);
    }
    return almanac;
}

int main(int argc, char** argv){

    std::ifstream fin(argv[1], std::ios::in);
    
    std::vector<Range> seedsRanges = getSeedsRanges(fin);
    std::vector<RMap> almanac = getAlmanac(fin);

    fin.close();

    std::queue<Range> Q, emtptyQ;
    size_t Qsize;
    RMap map;
    Range next;
    std::vector<Range> vec;

    for (auto &seed : seedsRanges){
        
        Q.push(seed);

        for (int i = 0; i < almanac.size(); ++i){

            map = almanac[i];
            Qsize = Q.size();

            for (int j = 0; j < Qsize; ++j){
                
                next = Q.front();
                Q.pop();

                vec = map.apply(next);
                for(auto it = vec.begin(); it != vec.end(); ++it){
                    Q.push(*it);
                vec.clear();
                }    
            }
        }

        Q.swap(emtptyQ);
    }

    return 0;
}