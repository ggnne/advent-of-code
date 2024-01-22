/* 
In Camel Cards, you get a list of hands, and your goal is to order them based 
on the strength of each hand. A hand consists of five cards labeled one of 
A, K, Q, J, T, 9, 8, 7, 6, 5, 4, 3, or 2. 
The relative strength of each card follows this order, 
where A is the highest and 2 is the lowest.

Every hand is exactly one type. From strongest to weakest, they are:

    6 Five of a kind, where all five cards have the same label: AAAAA
    size 1

    5 Four of a kind, where four cards have the same label and one card has a 
    different label: AA8AA
    size 2, 4*1

    4 Full house, where three cards have the same label, and the remaining 
    two cards share a different label: 23332
    size 2, 3*2

    3 Three of a kind, where three cards have the same label, and the remaining 
    two cards are each different from any other card in the hand: TTT98
    size 3, 3*1*1 = 3

    2 Two pair, where two cards share one label, two other cards share a second label, 
    and the remaining card has a third label: 23432
    size 3, 1*2*2 = 4

    1 One pair, where two cards share one label, and the other three cards have 
    a different label from the pair and each other: A23A4
    size 4

    0 High card, where all cards' labels are distinct: 23456
    1*1*1*1*1, size 5

Hands are primarily ordered based on type; for example, every full house is stronger 
than any three of a kind.

If two hands have the same type, a second ordering rule takes effect. 
Start by comparing the first card in each hand. If these cards are different, 
the hand with the stronger first card is considered stronger. 
If the first card in each hand have the same label, however, 
then move on to considering the second card in each hand. I
f they differ, the hand with the higher second card wins; otherwise, 
continue with the third card in each hand, then the fourth, then the fifth.

So, 33332 and 2AAAA are both four of a kind hands, but 33332 is stronger because 
its first card is stronger. Similarly, 77888 and 77788 are both a full house, 
but 77888 is stronger because its third card is stronger 
(and both hands have the same first and second card).

To play Camel Cards, you are given a list of hands and their corresponding bid 
(your puzzle input). For example:

32T3K 765
T55J5 684
KK677 28
KTJJT 220
QQQJA 483

This example shows five hands; each hand is followed by its bid amount. 
Each hand wins an amount equal to its bid multiplied by its rank, 
where the weakest hand gets rank 1, the second-weakest hand gets rank 2, 
and so on up to the strongest hand. Because there are five hands in this example, 
the strongest hand will have rank 5 and its bid will be multiplied by 5.

So, the first step is to put the hands in order of strength:

    32T3K is the only one pair and the other hands are all a stronger type, so it 
    gets rank 1.
    KK677 and KTJJT are both two pair. Their first cards both have the same label, 
    but the second card of KK677 is stronger (K vs T), so KTJJT gets rank 2 and KK677 
    gets rank 3.
    T55J5 and QQQJA are both three of a kind. QQQJA has a stronger first card, 
    so it gets rank 5 and T55J5 gets rank 4.

32T3K(1) KK677(2) KTJJT(2) T55J5(3) QQQJA(3) 

Now, you can determine the total winnings of this set of hands by adding up the 
result of multiplying each hand's bid with i
ts rank (765 * 1 + 220 * 2 + 28 * 3 + 684 * 4 + 483 * 5). 
So the total winnings in this example are 6440.

Find the rank of every hand in your set. What are the total winnings?
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
    std::vector<char> map = {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};
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
    
    size_t size = cmap.size();
    switch (cmap.size()){

        case 1:
            type = 6;
            break;
        case 2:
            type = size + 3 - (runProd == 6);
            break;
        case 3:
            type = size - (runProd == 4);
            break;
        case 4:
            type = 1;
            break;
        default:
            type = 0;
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