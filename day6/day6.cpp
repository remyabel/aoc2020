#include <algorithm>
#include <bitset>
#include <fstream>
#include <iostream>
#include <set>

int part1(std::string answer) {
    std::bitset<26> bs;
    for (auto c : answer) {
        bs[c - 'a'] = true;
    }
    return bs.count();
}

int part2(std::string answer, int person) {
    std::set<char> answers;
    int sum = 0;
    for (auto c : answer) {
        answers.insert(c);
    }
    for (auto c : answers) {
        if (person == std::count(answer.begin(), answer.end(), c))
            ++sum;
    }
    return sum;
}

int main() {
    std::ifstream ifs("input");
    std::string input;
    std::string answers;
    int sum_part1 = 0;
    int sum_part2 = 0;
    int person = 0;
    while (std::getline(ifs, input)) {
        answers += input;
        ++person;
        if (input.size() == 0) {
            sum_part1 += part1(answers);
            sum_part2 += part2(answers, --person);
            answers = "";
            person = 0;
        }
    }
    sum_part1 += part1(answers);
    sum_part2 += part2(answers, person);
    std::cout << sum_part1 << " " << sum_part2;
}
