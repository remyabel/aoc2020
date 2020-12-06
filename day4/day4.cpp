#include <algorithm>
#include <bitset>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

bool valid_passport(std::string passport) {
    std::bitset<8> passport_fields;
    passport_fields[0] = passport.find("byr") != std::string::npos;
    passport_fields[1] = passport.find("iyr") != std::string::npos;
    passport_fields[2] = passport.find("eyr") != std::string::npos;
    passport_fields[3] = passport.find("hgt") != std::string::npos;
    passport_fields[4] = passport.find("hcl") != std::string::npos;
    passport_fields[5] = passport.find("ecl") != std::string::npos;
    passport_fields[6] = passport.find("pid") != std::string::npos;
    passport_fields[7] = passport.find("cid") != std::string::npos;
    if ((passport_fields[0] && passport_fields[1] && passport_fields[2] &&
         passport_fields[3] && passport_fields[4] && passport_fields[5] &&
         passport_fields[6]) ||
        passport_fields.all()) {
        return true;
    }
    return false;
}

bool valid_passport2(std::string passport) {
    std::istringstream iss(passport);
    std::vector<std::string> results{std::istream_iterator<std::string>{iss},
                                     std::istream_iterator<std::string>()};
    if (!valid_passport(passport))
        return false;
    for (auto field : results) {
        std::string key = field.substr(0, field.find(":"));
        std::string value = field.substr(field.find(":") + 1, field.size());
        if (key == "byr") {
            if (!(value.size() == 4 && std::stoi(value) >= 1920 &&
                  std::stoi(value) <= 2002)) {
                return false;
            }
        }
        if (key == "iyr") {
            if (!(value.size() == 4 && std::stoi(value) >= 2010 &&
                  std::stoi(value) <= 2020)) {
                return false;
            }
        }
        if (key == "eyr") {
            if (!(value.size() == 4 && std::stoi(value) >= 2020 &&
                  std::stoi(value) <= 2030)) {
                return false;
            }
        }
        if (key == "hgt") {
            int height_value = 0;
            auto pos = value.find("cm");
            if (pos != std::string::npos) {
                height_value = std::stoi(value.substr(0, pos));
                if (!(height_value >= 150 && height_value <= 193)) {
                    return false;
                }
            } else {
                pos = value.find("in");
                if (pos != std::string::npos)
                    height_value = std::stoi(value.substr(0, pos));
                if (!(height_value >= 59 && height_value <= 76)) {
                    return false;
                }
            }
        }
        if (key == "hcl") {
            auto pos = value.find("#");
            if (pos == std::string::npos) {
                return false;
            }
            auto hex_value = value.substr(pos + 1);
            if (!std::any_of(hex_value.begin(), hex_value.end(), [](char c) {
                    return std::isdigit(c) || (c >= 'a' && c <= 'f');
                })) {
                return false;
            }
        }
        if (key == "ecl") {
            if (!(value == "amb" || value == "blu" || value == "brn" ||
                  value == "gry" || value == "grn" || value == "hzl" ||
                  value == "oth")) {
                return false;
            }
        }
        if (key == "pid") {
            if (!(value.size() == 9 &&
                  std::all_of(value.begin(), value.end(),
                              [](char c) { return std::isdigit(c); }))) {
                return false;
            }
        }
    }

    return true;
}

int main() {
    std::ifstream ifs("input");
    std::string input;
    std::string passport;

    int valid = 0;
    int valid2 = 0;
    while (std::getline(ifs, input)) {
        passport += " " + input;
        if (input.size() == 0 || input.size() == 1) {
            if (valid_passport(passport)) {
                ++valid;
            }
            if (valid_passport2(passport)) {
                ++valid2;
            }
            passport = "";
        }
    }
    if (valid_passport(passport)) {
        ++valid;
    }
    if (valid_passport2(passport)) {
        ++valid2;
    }
    std::cout << valid << " " << valid2;
}
