#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <vector>

// Shamelessly stolen from khuxkm
std::map<long long, long long> cache;
long long search(long long val, const std::vector<int> &v) {
    if (val == v[v.size() - 1])
        return 1;
    if (cache.count(val))
        return cache[val];
    long long permutations = 0;
    if (std::find(v.begin(), v.end(), val + 1) != v.end())
        permutations += search(val + 1, v);
    if (std::find(v.begin(), v.end(), val + 2) != v.end())
        permutations += search(val + 2, v);
    if (std::find(v.begin(), v.end(), val + 3) != v.end())
        permutations += search(val + 3, v);
    cache[val] = permutations;
    return permutations;
}

int main() {
    std::fstream ifs("input");
    int voltage;
    std::vector<int> v;
    while (ifs >> voltage) {
        v.push_back(voltage);
    }
    std::sort(v.begin(), v.end());
    v.push_back(v[v.size() - 1] + 3);
    std::vector<int> differences;
    std::adjacent_difference(v.begin(), v.end(),
                             std::back_inserter(differences));
    std::cout << std::count(differences.begin(), differences.end(), 1) *
                     std::count(differences.begin(), differences.end(), 3)
              << "\n";
    std::cout << search(0, v);
}
