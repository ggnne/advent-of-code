#include <iostream>
#include <vector>
#include <fstream>
#include <string>

int main(int argc, char **argv)
{
    std::fstream fin(argv[1], std::fstream::in);

    char ch;
    int i, t, sum=0;
    std::vector<int> temp;

    while ((fin >> std::noskipws >> ch))
    {   
        if (ch != '\n'){
            i = static_cast<int>(ch - '0');
            if (i >= 0 && i <= 9){
                temp.push_back(i);
            }
        } else {
            t = std::stoi(std::to_string(temp[0]) + std::to_string(temp[temp.size() - 1]));
            sum += t;
            temp.clear();
        }
    }

    t = std::stoi(std::to_string(temp[0]) + std::to_string(temp[temp.size() - 1]));
    sum += t;
    temp.clear();
 
    std::cout << sum << std::endl;

    fin.close();

    return 0;
}
