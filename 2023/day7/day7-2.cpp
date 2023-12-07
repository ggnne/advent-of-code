/* 
To make things a little more interesting, the Elf introduces one additional rule. 
Now, J cards are jokers - wildcards that can act like whatever card would make the hand the strongest type possible.

To balance this, J cards are now the weakest individual cards, weaker even than 2. 
The other cards stay in the same order: A, K, Q, T, 9, 8, 7, 6, 5, 4, 3, 2, J.

J cards can pretend to be whatever card is best for the purpose of determining hand type; 
for example, QJJQ2 is now considered four of a kind. 
However, for the purpose of breaking ties between two hands of the same type, 
J is always treated as J, not the card it's pretending to be: JKKK2 is weaker than QQQQ2 because J is weaker than Q.

Now, the above example goes very differently:

32T3K 765
T55J5 684
KK677 28
KTJJT 220
QQQJA 483

    32T3K is still the only one pair; it doesn't contain any jokers, so its strength doesn't increase.
    KK677 is now the only two pair, making it the second-weakest hand.
    T55J5, KTJJT, and QQQJA are now all four of a kind! T55J5 gets rank 3, QQQJA gets rank 4, and KTJJT gets rank 5.

With the new joker rule, the total winnings in this example are 5905.

Using the new joker rule, find the rank of every hand in your set. What are the new total winnings?
*/

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <tuple>
#include <map>
#include <algorithm>

typedef long long int L;

template<class T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& v){
    for (int i = 0; i < v.size(); ++i){
        out << v[i] << " ";
    }
    return out;
}

struct Card {
    Card(char ch);
    char c;
    int n;
};

Card::Card(char ch){
    c = ch;
    // std::vector<char> map = {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'}; old rule
    std::vector<char> map = {'J', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'Q', 'K', 'A'};
    n = std::find(map.begin(), map.end(), c) - map.begin();
}

bool operator<(const Card& a, const Card& b){
    return a.n < b.n;
}

bool operator==(const Card& a, const Card& b){
    return a.n == b.n;
}

bool operator!=(const Card& a, const Card& b){
    return a.n != b.n;
}

struct Hand{
    Hand(std::string s);
    std::string str;
    std::vector<Card> cvec;
    std::map<char, int> cmap;
    int type;
};

Hand::Hand(std::string s){
    
    str = s;
    
    int runProd = 1;

    for (int i = 0; i < str.size(); ++i){
        Card c(str[i]);
        cvec.push_back(c);
        if (cmap.count(str[i])){
            runProd /= cmap[str[i]]++;
            runProd *= cmap[str[i]];
        } else {
            cmap.insert({str[i], 1});
        }
    }
    
    if (cmap.count('J')){

    }


    size_t size = cmap.size();
    switch (cmap.size()){

        case 1:
            type = 6;
            break;
        case 2:
            type = size + 3 - (runProd == 6);
            if (cmap.count('J')){
                type = 6;
            }
            break;
        case 3:
            type = size - (runProd == 4);
            if (cmap.count('J')){
                
                if (type == 2 && cmap['J'] == 1){
                    type = 4;
                } else {
                    type = 5;
                }

            }
            break;
        case 4:
            type = 1 + cmap.count('J') * 2;
            break;
        default:
            type = 0 + cmap.count('J');
    }
}

bool operator<(const std::vector<Card>& a, const std::vector<Card>& b){
    for (int i = 0; i < a.size(); ++i){
        if (a[i] != b[i]){
            return a[i] < b[i];
        }
    }
    return 0;
}

bool operator<(const Hand& a, const Hand& b){
    return (a.type < b.type) ? 1 : ((a.type == b.type) ? (a.cvec < b.cvec) : 0);
}

std::ostream& operator<<(std::ostream& out, const Hand& h){
    out << h.str << "(" << h.type << ")";
    return out;
}

typedef std::tuple<std::vector<Hand>, std::map<std::string, L>> inputVectors;
inputVectors readInput(std::ifstream& fin){

    std::string line, strHand;
    std::stringstream ss;
    std::vector<Hand> hands;
    std::map<std::string, L> handToBid;

    L bid;
    while(getline(fin, line)){
        strHand = line.substr(0, line.find(" "));
        Hand h(strHand);
        hands.push_back(h);
        line.erase(0, strHand.size() + 1);
        ss << line;
        ss >> bid;
        handToBid.insert({strHand, bid});
        ss.clear();
    }

    inputVectors p(hands, handToBid);
    return p;
}


int main(int argc, char** argv){

    std::ifstream fin(argv[1], std::ios::in);

    std::vector<Hand> hands;
    std::map<std::string, L> handToBid;

    tie(hands, handToBid) = readInput(fin);

    fin.close();

    std::sort(hands.begin(), hands.end());

    L solution = 0;
    for (int i = 0; i < hands.size(); ++i){
        solution += (handToBid[hands[i].str] * (i + 1));
    }

    std::cout << solution << std::endl;

    return 0;
}