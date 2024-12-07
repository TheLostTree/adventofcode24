#include <fstream>
#include <iostream>
// #define TEST
#ifdef TEST
#define INPUTFILE "test.txt"
#else
#define INPUTFILE "input.txt"
#endif
#include <sstream>
using namespace std;

struct rule {
    int first;
    int second;
};

ostream& operator<<(ostream& s, rule& rule) {
    std::print(s, "{} | {}", rule.first, rule.second);
    return s;
}
void part1() {
    std::ifstream input(INPUTFILE);
    if (!input.is_open()) {
        std::exit(-1);
    }

    std::string line;
    // rules
    std::vector<rule> rules;
    while (std::getline(input, line) && line.length()) {
        istringstream s(line);
        int a, b;
        char c;
        s >> a >> c >> b;  // num|num
        rules.push_back({a, b});
    }
    // updates
    int total = 0;
    while (std::getline(input, line)) {
        std::vector<int> nums;
        istringstream s(line);
        std::string a;
        while (std::getline(s, a, ',')) {
            nums.push_back(std::stoi(a));
        }

        bool bad = false;
        for (rule r : rules) {
            // cout << "testing rule: " << r << endl;
            auto first_idx_iter = std::find(nums.begin(), nums.end(), r.first);
            auto second_idx_iter = std::find(nums.begin(), nums.end(), r.second);
            if (first_idx_iter == nums.end() || second_idx_iter == nums.end()) {
                continue;
            };
            if (second_idx_iter < first_idx_iter) {
                // illegal!
                bad = true;
                break;
            }
        }
        if (!bad) {
            // std::println("yay!");
            // std::println("{}, middle {}",line, nums.at(nums.size()/2));
            total += nums.at(nums.size() / 2);
        } else {
            // std::println("sad!");
            // std::println("{}",line);
        }
    }
    cout << total << endl;
}
#include <algorithm>
#include <unordered_map>



void part2() {
    std::ifstream input(INPUTFILE);
    if (!input.is_open()) {
        std::exit(-1);
    }

    std::string line;
    // rules
    std::vector<rule> rules;
    while (std::getline(input, line) && line.length()) {
        istringstream s(line);
        int a, b;
        char c;
        s >> a >> c >> b;  // num|num
        rules.push_back({a, b});
    }
    // updates
    int total = 0;
    while (std::getline(input, line)) {
        std::vector<int> nums;
        istringstream s(line);
        std::string a;
        while (std::getline(s, a, ',')) {
            nums.push_back(std::stoi(a));
        }

        bool bad = false;
        std::vector<rule> broken_rules;
        for (rule r : rules) {
            // cout << "testing rule: " << r << endl;
            auto first_idx_iter = std::find(nums.begin(), nums.end(), r.first);
            auto second_idx_iter = std::find(nums.begin(), nums.end(), r.second);
            if (first_idx_iter == nums.end() || second_idx_iter == nums.end()) {
                continue;
            };
            if (second_idx_iter < first_idx_iter) {
                // illegal!
                bad = true;
                // break;
                broken_rules.push_back(r);
            }
        }
        if (bad) {
            // std::println("yay!");


            //thank you for letting me avoid implementing topological sort
            //https://www.reddit.com/r/adventofcode/comments/1h71eyz/comment/m0o045w/?utm_source=share&utm_medium=web3x&utm_name=web3xcss&utm_term=1&utm_content=share_button
            std::sort(nums.begin(), nums.end(), [&broken_rules](int a,int b){
                for(auto r : broken_rules){
                    if(a == r.first && b == r.second){
                        return -1;
                    }
                }
                return 0;
            });



            std::println("{}, middle {}", line, nums.at(nums.size() / 2));
            std::println("{}, middle {}\n", nums, nums.at(nums.size() / 2));
            total += nums.at(nums.size() / 2);
        } else {
            // std::println("sad!");
            // std::println("{}",line);
        }
    }
    cout << total << endl;
}
int main() {
    // part1();
    part2();

    std::vector<rule> rules = {{29, 13}, {49, 13}, {47, 29}};
}
