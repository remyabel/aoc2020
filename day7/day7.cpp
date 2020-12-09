#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

std::map<std::string, std::vector<std::pair<int, std::string>>> bags_map;

std::string ltrim(std::string s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
                                    [](char ch) { return !std::isspace(ch); }));
    return s;
}

bool contains_shiny_bag(std::string bag) {
    for (auto child_bag : bags_map[bag]) {
        if (contains_shiny_bag(child_bag.second) ||
            bag.find("shiny gold") != std::string::npos)
            return true;
    }
    return false;
}

int count_bags(std::string bag) {
    int temp = 0;
    for (auto child_bag : bags_map[bag]) {
        temp += child_bag.first;
        temp += count_bags(child_bag.second) * child_bag.first;
    }
    return temp;
}

int main() {
    std::fstream ifs("input");
    std::string input;

    while (std::getline(ifs, input)) {
        std::string parent_bag = ltrim(input.substr(0, input.find("bags") - 1));
        std::string bags =
            input.substr(input.find("contain") + std::strlen("contain"));
        bags.erase(std::remove(bags.begin(), bags.end(), '.'), bags.end());
        std::istringstream iss(bags);
        if (bags != "no other bags") {
            std::string child_bag;
            std::string child_bag_input;
            std::vector<std::pair<int, std::string>> children;
            while (std::getline(iss, child_bag_input, ',')) {
                std::istringstream iss2(child_bag_input);
                int n;
                iss2 >> n;
                std::getline(iss2, child_bag);
                child_bag = child_bag.substr(0, child_bag.find("bag") - 1);
                children.push_back({n, ltrim(child_bag)});
            }
            bags_map[parent_bag] = std::move(children);
        }
    }
    int count = 0;
    for (auto bag : bags_map) {
        if (contains_shiny_bag(bag.first) && bag.first != "shiny gold")
            ++count;
    }
    std::cout << count << "\n";
    std::cout << count_bags("shiny gold");
}
