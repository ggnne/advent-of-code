#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <map>

typedef long long int L;

void setData(std::ifstream& fin, std::string& s, std::vector<int>& p, int part){

    s.clear();
    p.clear();

    std::string line, left, right;
    
    getline(fin, line);
    left = line.substr(0, line.find(' '));
    right = line.substr(line.find(' ') + 1, line.size());

    while (left[0] == '.'){
        left.erase(0, 1);
    }

    s = left[0];
    for (int i = 1; i < left.size(); ++i){
        if (left[i-1] != '.' || left[i] != '.'){
            s += left[i];
        }
    }
    left = s;

    std::stringstream ss(right);
    for (int i; ss >> i;){
        p.push_back(i);
        if (ss.peek() == ','){
            ss.ignore();
        }
    }

    if (part == 2){

        size_t pl = p.size();
        for (int i = 0; i < 5; ++i){

            s += '?' + left;

            for (int j = 0; j < pl; ++j){
                p.push_back(p[j]);
            }

        }
    }

    if (s[s.size()-1] != '.'){
        s += '.';
    }

}

typedef long long int L;

L arrCount(const std::string& s, const std::vector<int>& p, int i, int j, int c){

    L N = 0;
    int I = s.size(), J = p.size();

    if (i < I){

        if (s[i] == '#'){

            if (c < p[j]){
                N += arrCount(s, p, i + 1, j, c + 1);
            }

        } else if (s[i] == '.'){
            
            if (c == 0){
                N += arrCount(s, p, i + 1, j, c);
            } else if (c == p[j] && j < J){
                N += arrCount(s, p, i + 1, j + 1, 0);
            } else if (c == p[j] && j == J - 1){
                N += arrCount(s, p, i + 1, j, 0);
            }
        
        } else {
        
            if (c < p[j]){
                N += arrCount(s, p, i + 1, j, c + 1);
            }
            if (c == 0){
                N += arrCount(s, p, i + 1, j, c);
            } else if (c == p[j] && j < J){
                N += arrCount(s, p, i + 1, j + 1, 0);
            } else if (c == p[j] && j == J - 1){
                N += arrCount(s, p, i + 1, j, 0);
            }

        }

    } else {

        if (j == J){
            return 1;
        }

    }

    return N;
}

int main(int argc, char** argv){

    std::ifstream fin(argv[1], std::ios::in);
    int part = std::stoi(argv[2]);

    std::string springs;
    std::vector<int> pattern;
    L sum = 0;

    while (fin.peek() != EOF){

        setData(fin, springs, pattern, part);
        L N = arrCount(springs, pattern, 0, 0, 0);
        sum += N;

    }

    std::cout << sum << std::endl;

    return 0;
}