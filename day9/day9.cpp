#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <vector>

bool has_sum(long long n, const std::vector<int> &preamble) {
    for (auto i = 0; i < preamble.size(); ++i) {
        for (auto j = i; j < preamble.size(); ++j) {
            if (preamble[i] + preamble[j] == n && preamble[i] != preamble[j]) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    std::ifstream ifs("input");
    long long n;
    int index = 0;
    int preamble_size = 25;
    std::vector<int> preamble;
    int invalid_number;
    while (ifs >> n) {
        if (index >= preamble_size) {
            if (!has_sum(n, std::vector<int>{
                                preamble.begin() + index - preamble_size,
                                preamble.begin() + index + preamble_size})) {
                invalid_number = n;
                break;
            }
        }
        ++index;
        preamble.push_back(n);
    }
    std::cout << invalid_number << "\n";
    std::vector<int> sum_range;
    int sum;
    int start_index = 0;
    while (sum != invalid_number) {
        sum_range.clear();
        sum = 0;
        for (auto i = start_index; i < preamble.size(); ++i) {
            if (preamble[i] >= invalid_number || sum >= invalid_number)
                break;
            sum += preamble[i];
            sum_range.push_back(preamble[i]);
        }
        ++start_index;
    }
    std::cout << *std::min_element(sum_range.begin(), sum_range.end()) +
                     *std::max_element(sum_range.begin(), sum_range.end());
}
