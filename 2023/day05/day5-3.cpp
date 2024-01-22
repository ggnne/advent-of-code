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

Range operator+(const Range &r, const L &a){
    Range newR(r.lo + a, r.hi + a);
    return newR;
}

Range operator+(const L &a, const Range &r){
    return (r + a);
}

std::ostream &operator<<(std::ostream &out, const std::vector<Range> &v){
    for (int i = 0; i < v.size(); ++i){
        out << v[i] << " ";
    }
    return out;
}

void sortRangeVec(std::vector<Range> &v){
        std::sort(v.begin(), v.end(), [](const Range &left, const Range &right) {return left.lo < right.lo;});
}

struct RMap{
    RMap();
    RMap(std::vector<std::vector<L>> v);
    std::vector<Range> from;
    std::vector<L> shifts;
    std::vector<Range> apply(const Range &R);
    std::vector<Range> apply(const std::vector<Range> &v);
};

RMap::RMap(){}

std::ostream &operator<<(std::ostream &out, const RMap &rm) {
    for (int i = 0; i < rm.from.size(); ++i){
        out << rm.from[i] << "(" << rm.shifts[i] << ")" << std::endl;
    }
    return out;
}

RMap::RMap(std::vector<std::vector<L>> v){

    from.clear();
    shifts.clear();

    std::sort(v.begin(), v.end(), [](const std::vector<L> &left, const std::vector<L> &right) {return left[1] < right[1];});
    L shift;
    for (int i = 0; i < v.size(); ++i){

        if ((i == 0) && (v[i][1] > 0)) {
            Range lft(0, v[i][1]-1);
            from.push_back(lft);
            shifts.push_back(0);
        }

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
    Range inter, shifted;
    L shift;

    for (int i = 0; i < (this->from).size(); ++i){
        inter = (R && (this->from)[i]);
        if (!inter.empty){
            inters.push_back(inter);
            shift = (this->shifts)[i];
            shifted = inter + shift;
            out.push_back(shifted);
        }
    }

    if (inters.size() > 0){
                
        if (inters[inters.size()-1].hi < R.hi){
            Range right(inters[inters.size()-1].hi + 1, R.hi);
            fillGaps.push_back(right);
        }
 
        for (int i = 1; i < inters.size(); ++i){
            if ( inters[i].lo - inters[i-1].hi > 1){
                Range mid(inters[i-1].hi + 1, inters[i].lo - 1);
                fillGaps.push_back(mid);
            }
        }

    } else {

        fillGaps.push_back(R);

    }

    out.insert(out.end(), fillGaps.begin(), fillGaps.end());
    sortRangeVec(out);

    return out;
}

std::vector<Range> RMap::apply(const std::vector<Range> &v){
    std::vector<Range> out;
    std::vector<Range> temp;
    for (const Range &r : v){
        temp = apply(r);
        out.insert(out.end(), temp.begin(), temp.end());
        temp.clear();
    }
    sortRangeVec(out);
    return out;
}

// Read Input

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

    std::vector<Range> seedV, lastV;
    for (int i = 0; i < seedsRanges.size(); ++i){

        seedV.push_back(seedsRanges[i]);

        for (int j = 0; j < almanac.size(); ++j){
            seedV = almanac[j].apply(seedV);
        }

        lastV.push_back(seedV[0]);
        seedV.clear();
    }

    sortRangeVec(lastV);
    std::cout << lastV[0].lo << std::endl;
    
    return 0;
}