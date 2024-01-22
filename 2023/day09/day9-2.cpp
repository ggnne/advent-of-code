
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>

typedef long long int L;


std::vector<std::vector<L>> getInput(std::ifstream& fin){

    std::string line;
    std::stringstream ss;
    std::vector<std::vector<L>> reports;

    L t;
    std::vector<L> tv;
    while(getline(fin, line)){
        ss << line;
        while (ss >> t){
            tv.push_back(t);
        }
        reports.push_back(tv);
        tv.clear();
        ss.clear();
    }

    return reports;
}


int binomialCoeff(int n, int k)
{
    int C[n + 1][k + 1];
    
    for (int i = 0; i <= n; ++i){
        for (int j = 0; j <= std::min(i, k); ++j){
            if (j == 0 || j == i){
                C[i][j] = 1;
            } else {
                C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
            }
        }
    }

    return C[n][k];
}


L diff(std::vector<L>::iterator end, int k){
    L out = 0;
    int sign = -1;
    for (int t = 0; t < k + 1; ++t){
        sign *= -1;
        out += sign * binomialCoeff(k, t) * *(end - t - 1);
    }
    return out;
}


L extrapolate(std::vector<L> v){

    L out = 0;
    for (int i  = 0; i < v.size(); ++i){
        L D = diff(v.end(), i);
        out += D;
        if (D == 0){
            bool stop = 0;
            for (int j = 1; j < v.size() - i; ++j){
                if (diff(v.end()-j, i) != 0) 
                    break;
            if (stop)
                break;
            }
        }
    }

    return out;
}

int main(int argc, char** argv){

    std::ifstream fin(argv[1], std::ios::in);

    std::vector<std::vector<L>> reports;

    reports = getInput(fin);

    fin.close();

    L solution = 0, last;
    for (int i = 0; i < reports.size(); ++i){
        std::reverse(reports[i].begin(), reports[i].end()); // REALLY?!
        last = extrapolate(reports[i]);
        solution += last;
    }

    std::cout << solution << std::endl;

    return 0;
}