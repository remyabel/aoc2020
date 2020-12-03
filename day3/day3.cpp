#include <iostream>
#include <fstream>
#include <vector>

int find_trees(int x_slope, int y_slope, std::vector<std::string> const& grid) {
    int index = 0;
    int tree_count = 0;
    std::pair<int, int> coords = {0, 0};
    while (index < grid.size()) {
        coords.first += x_slope;
        if (coords.first >= grid[index].size())
            coords.first -= grid[index].size();
        coords.second += y_slope;
        if (coords.second < grid.size()) {
            if (grid[coords.second][coords.first] == '#')
                ++tree_count;
        }
        ++index;
    }
    return tree_count;
}

int main() {
    std::ifstream ifs("input");
    std::string input;
    std::vector<std::string> grid;
    while (std::getline(ifs, input)) {
        grid.push_back(input);
    }
    std::cout << find_trees(3, 1, grid) << "\n";
    std::cout << find_trees(1, 1, grid) *
        find_trees(3, 1, grid) * 
        find_trees(5, 1, grid) *
        find_trees(7, 1, grid) *
        find_trees(1, 2, grid);
}
