#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>

int main() {
    std::ifstream ifs("input");
    int valid = 0;
    int min;
    int max;
    char c;
    char s[100];
    std::string input;
    while (std::getline(ifs, input)) {
        std::sscanf(input.data(), "%i-%i %c: %99s", &min, &max, &c, s);
        int count = std::count(s, s + std::strlen(s), c);
        if (count >= min && count <= max) {
            ++valid;
        }
    }
    std::cout << "part1: " << valid << "\n";

    ifs.clear();
    ifs.seekg(0);
    valid = 0;
    while (std::getline(ifs, input)) {
        std::sscanf(input.data(), "%i-%i %c: %99s", &min, &max, &c, s);
        if ((s[min - 1] == c && s[max - 1] != c) ||
            (s[min - 1] != c && s[max - 1] == c)) {
            ++valid;
        }
    }
    std::cout << "part2: " << valid << "\n";
}
