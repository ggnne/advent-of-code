/* 
As the race is about to start, you realize the piece of paper with race times and record distances 
you got earlier actually just has very bad kerning. There's really only one race - ignore the spaces between the numbers on each line.

So, the example from before:

Time:      7  15   30
Distance:  9  40  200

...now instead means this:

Time:      71530
Distance:  940200

Now, you have to figure out how many ways there are to win this single race. 
In this example, the race lasts for 71530 milliseconds and the record distance you need to beat is 940200 millimeters. 
You could hold the button anywhere from 14 to 71516 milliseconds and beat the record, a total of 71503 ways!

How many ways can you beat the record in this one much longer race?
 */

 #include <iostream>
 #include <fstream>
 #include <sstream>
 #include <vector>
 #include <cmath>
 #include <algorithm>
 #include <string>

typedef long long int L;

template<class T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& v){
    for (int i = 0; i < v.size(); ++i){
        out << v[i] << " ";
    }
    return out;
}

std::vector<L> getLineInput(std::ifstream& fin){

    std::string line;
    std::stringstream ss, ss2;
    L n;

    getline(fin, line);
    line = line.erase(0, line.find(":") + 1);
    ss << line;

    std::vector<L> out;
    while(ss >> n){
        ss2 << n;
    }

    std::string strNum;
    ss2 >> strNum;

    n = std::stoll(strNum);
    out.push_back(n);

    return out;
}

std::vector<double> quadraticFormula(L t, L d){

    double a = -1;
    double b = static_cast<double>(t);
    double c = static_cast<double>(-(d + 1));

    double belowRoot = b*b - 4*a*c;
    double sol1, sol2;
    std::vector<double> out;

    if (belowRoot > 0){
        double sqrRoot = std::sqrt(belowRoot);
        sol1 = (-b + sqrRoot) / (2*a);
        sol2 = (-b - sqrRoot) / (2*a);
    } else if (belowRoot == 0) {
        sol1 = (-b / 2*a);
        sol2 = sol1;
    } else {
        return out;
    }

    out.push_back(sol1);
    out.push_back(sol2);
    std::sort(out.begin(), out.end());
    out[0] = std::ceil(out[0]);
    out[1] = std::floor(out[1]);

    return out;
}


L solve(std::vector<L> times, std::vector<L> distances){

    int solution = 1;
    for (int i = 0; i < times.size(); ++i){
        auto v = quadraticFormula(times[i], distances[i]);
        solution *= (v[1] - v[0] + 1);
    }
    return solution;
}


 int main(int argc, char** argv){

    std::ifstream fin(argv[1], std::ios::in);

    std::vector<L> times = getLineInput(fin);
    std::vector<L> distances = getLineInput(fin);

    fin.close();

    std::cout << solve(times, distances) << std::endl;

    return 0;
 }