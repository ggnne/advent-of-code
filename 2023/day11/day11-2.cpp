
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

typedef long long int L;

std::vector<std::string> readInput(std::ifstream& fin){
    
    std::vector<std::string> table;
    std::string line;

    while (getline(fin, line)){

        table.push_back(line);
    }

    fin.close();

    return table;
}


int main(int argc, char** argv){

    std::ifstream fin(argv[1], std::ios::in);
    std::vector<std::string> table = readInput(fin);

    int N = table.size(), M = table[0].size();

    std::vector<L> H(M, std::stoi(argv[2]));
    std::vector<L> V(N, std::stoi(argv[2]));
    std::vector<std::vector<L>> galaxies;

    for (int i = 0; i < N; ++i){
        for (int j = 0; j < M; ++j){
            if (table[i][j] == '#'){
                H[j] = 1;
                V[i] = 1;
                std::vector<L> coord = {i, j};
                galaxies.push_back(coord);
            }
        }
    }

    for (int i = 1; i < H.size(); ++i)
        H[i] += H[i-1];

    for (int i = 1; i < V.size(); ++i)
        V[i] += V[i-1];

    L sum = 0, d, h1, h2, v1, v2;
    for (int i = 0; i < galaxies.size()-1; ++i){

        h1 = galaxies[i][1];
        v1 = galaxies[i][0];

        for (int j = i + 1; j < galaxies.size(); ++j){

            h2 = galaxies[j][1];
            v2 = galaxies[j][0];
            d = abs(H[h1] - H[h2]) + abs(V[v1] - V[v2]);
            sum += d;
        }

    }

    std::cout << sum << std::endl;

    return 0;
}