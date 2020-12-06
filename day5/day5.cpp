#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

int main() {
    std::ifstream ifs("input");
    std::string input;
    std::vector<int> ids;
    while (std::getline(ifs, input)) {
        std::vector<int> rows(127);
        std::vector<int> columns(8);
        std::iota(rows.begin(), rows.end(), 0);
        std::iota(columns.begin(), columns.end(), 0);
        for (char c : input) {
            if (c == 'F') {
                rows.erase(rows.begin() + rows.size() / 2, rows.end());
            }
            if (c == 'B') {
                rows.erase(rows.begin(), rows.begin() + rows.size() / 2);
            }
            if (c == 'R') {
                columns.erase(columns.begin(),
                              columns.begin() + columns.size() / 2);
            }
            if (c == 'L') {
                columns.erase(columns.begin() + columns.size() / 2,
                              columns.end());
            }
        }
        int id = (rows[0] + 1) * 8 + columns[0];
        ids.push_back(id);
    }
    std::sort(ids.begin(), ids.end());
    std::cout << ids[ids.size() - 1] << "\n";

    std::vector<int> results;
    std::adjacent_difference(ids.begin(), ids.end(),
                             std::back_inserter(results));
    auto it = std::find_if(results.begin(), results.end(),
                           [](int i) { return i > 1; });
    while (it != results.end()) {
        int id_candidate = ids[it - results.begin() - 1] + 1;
        if (id_candidate >= ids[0] && id_candidate <= ids[ids.size() - 1])
            std::cout << id_candidate;
        it = std::find_if(it + 1, results.end(), [](int i) { return i > 1; });
    }
}
