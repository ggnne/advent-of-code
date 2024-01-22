/* 
For example:

Time:      7  15   30
Distance:  9  40  200

This document describes three races:

    The first race lasts 7 milliseconds. The record distance in this race is 9 millimeters.
    The second race lasts 15 milliseconds. The record distance in this race is 40 millimeters.
    The third race lasts 30 milliseconds. The record distance in this race is 200 millimeters.

Your toy boat has a starting speed of zero millimeters per millisecond. 
For each whole millisecond you spend at the beginning of the race holding down the button, 
the boat's speed increases by one millimeter per millisecond.

So, because the first race lasts 7 milliseconds, you only have a few options:

    Don't hold the button at all (that is, hold it for 0 milliseconds) at the start of the race. The boat won't move; it will have traveled 0 millimeters by the end of the race.
    Hold the button for 1 millisecond at the start of the race. Then, the boat will travel at a speed of 1 millimeter per millisecond for 6 milliseconds, reaching a total distance traveled of 6 millimeters.
    Hold the button for 2 milliseconds, giving the boat a speed of 2 millimeters per millisecond. It will then get 5 milliseconds to move, reaching a total distance of 10 millimeters.
    Hold the button for 3 milliseconds. After its remaining 4 milliseconds of travel time, the boat will have gone 12 millimeters.
    Hold the button for 4 milliseconds. After its remaining 3 milliseconds of travel time, the boat will have gone 12 millimeters.
    Hold the button for 5 milliseconds, causing the boat to travel a total of 10 millimeters.
    Hold the button for 6 milliseconds, causing the boat to travel a total of 6 millimeters.
    Hold the button for 7 milliseconds. That's the entire duration of the race. You never let go of the button. The boat can't move until you let go of the button. Please make sure you let go of the button so the boat gets to move. 0 millimeters.

Since the current record for this race is 9 millimeters, there are actually 4 different ways you could win: you could hold the button for 2, 3, 4, or 5 milliseconds at the start of the race.

In the second race, you could hold the button for at least 4 milliseconds and at most 11 milliseconds and beat the record, a total of 8 different ways to win.

In the third race, you could hold the button for at least 11 milliseconds and no more than 19 milliseconds and still beat the record, a total of 9 ways you could win.

To see how much margin of error you have, determine the number of ways you can beat the record in each race; in this example, if you multiply these values together, you get 288 (4 * 8 * 9).

Determine the number of ways you could beat the record in each race. What do you get if you multiply these numbers together?
 */

 #include <iostream>
 #include <fstream>
 #include <sstream>
 #include <vector>
 #include <cmath>
 #include <algorithm>

template<class T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& v){
    for (int i = 0; i < v.size(); ++i){
        out << v[i] << " ";
    }
    return out;
}

std::vector<int> getLineInput(std::ifstream& fin){

    std::string line;
    std::stringstream ss;
    int n;

    getline(fin, line);
    line = line.erase(0, line.find(":") + 1);
    ss << line;

    std::vector<int> out;
    while(ss >> n){
        out.push_back(n);
    }

    return out;
}

std::vector<double> quadraticFormula(int t, int d){

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


int solve(std::vector<int> times, std::vector<int> distances){

    int solution = 1;
    for (int i = 0; i < times.size(); ++i){
        auto v = quadraticFormula(times[i], distances[i]);
        solution *= (v[1] - v[0] + 1);
    }
    return solution;
}


 int main(int argc, char** argv){

    std::ifstream fin(argv[1], std::ios::in);

    std::vector<int> times = getLineInput(fin);
    std::vector<int> distances = getLineInput(fin);

    fin.close();

    std::cout << solve(times, distances) << std::endl;

    return 0;
 }