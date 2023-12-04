#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>


int main(int argc, char **argv)
{

    std::map<std::string, int> dic = {{"one", 1}, {"two", 2}, {"three", 3}, {"four", 4}, {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}};
    int lengths[] = {3, 4, 5};

    std::ifstream fin(argv[1], std::ios::in);
    std::string line, sub;
    std::vector<int> temp;

    int t, num, sum=0;

    while (std::getline(fin, line)){

        for (int i = 0; i < line.size(); ++i){
            
            t = static_cast<int>(line.at(i) - '0');
            if (t >= 1 && t <=9){
                temp.push_back(t);
            } else {
                for (int j = 0; j < 3; ++j){
                    if (lengths[j] <= line.size() - i){
                        sub = line.substr(i, lengths[j]);
                        if (dic.count(sub)){
                            temp.push_back(dic[sub]);
                            break;
                        }
                    }
                }
            }

        }

        num = temp[0]*10 + temp[temp.size() - 1];
        sum += num;
        temp.clear();
    }

    std::cout << sum << std::endl;

    fin.close();

    return 0;
}
