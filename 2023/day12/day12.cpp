#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

bool check(const std::string& s, const std::vector<int>& v){

    bool cflag = 0;
    int c = 0;
    std::vector<int> cv;

    for (int i = 0; i < s.size(); ++i){

        if (s[i] == '#'){
            if (cflag){
                c++;
            }
            else {
                cflag = !cflag;
                c = 1;
            }
        } else {
            if (cflag){
                cflag = !cflag;
                cv.push_back(c);
                c = 0;
            }
        }
    }
    if (s[s.size()-1] == '#')
        cv.push_back(c);

    if (cv.size() != v.size())
        return 0;

    return cv == v;

}

int main(int argc, char** argv){

    std::ifstream fin(argv[1], std::ios::in);

    std::string line, left, right, token;
    std::vector<int> nums;
    std::stringstream ss, sss;
    std::vector<std::string> lv;
    std::vector<std::vector<int>> rv;
    std::vector<int> rvsum;

    int n, sn = 0;
    while(getline(fin, line)){
        
        left = line.substr(0, line.find(" "));
        right = line.substr(line.find(" ") + 1, line.size());

        lv.push_back(left);
        ss << right;
        while(getline(ss, token, ',')){
            sss << token;
            sss >> n;
            sn += n;
            nums.push_back(n);
            sss.clear();
        }
        rv.push_back(nums);
        rvsum.push_back(sn);
        sn = 0;
        ss.clear();
        nums.clear();
    }   


    int sol = 0;
    for (int i = 0; i < lv.size(); ++i){
        
        std::vector<int> qpos;
        int qc = 0, hc = 0;
        for (int j = 0; j < lv[i].size(); ++j){
            if (lv[i][j] == '?'){
                qpos.push_back(j);
                qc++;
            } else if (lv[i][j]== '#'){
                hc++;
            }
        }   

        std::string tempS = lv[i];
        std::string permS = std::string(rvsum[i] - hc, '#') + std::string(qc - (rvsum[i] - hc), '.');
        do {
            for (int j = 0; j < qpos.size(); ++j){
                tempS[qpos[j]] = permS[j];
            }
            sol += static_cast<int>(check(tempS, rv[i]));
        } while(std::next_permutation(permS.begin(), permS.end()));
    }

    std::cout << sol << std::endl;

    return 0;
}