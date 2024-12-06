#include <fstream>
#include <iostream>
#include <regex>
// #define TEST
#ifdef TEST
    #define INPUTFILE "test.txt"
#else
    #define INPUTFILE "input.txt"
#endif
using namespace std;

void part1(){
    std::ifstream input(INPUTFILE);
    if(!input.is_open()){
        std::exit(-1);
    }

    std::regex regex("mul\\((\\d{1,3}),(\\d{1,3})\\)");
    std::string s;
    string temp;
    while(input >> temp){
        s+=temp;
    }
    auto words_begin = std::sregex_iterator(s.begin(), s.end(), regex);
    auto words_end = std::sregex_iterator();

    int64_t total = 0;
    for(auto i = words_begin; i != words_end; i++){
        auto match = *i;
        cout << match.str() << endl;
    
        if(match.size() < 3) continue;
        cout << "group 1: " <<  match[1].str() << endl;
        cout << "group 2: " <<  match[2].str() << endl;

        total += std::stoi(match[1].str()) * std::stoi(match[2].str());
    }
    std::print("total: {}\n", total);
    cout << total << endl;

    
}
void part2(){
    std::ifstream input(INPUTFILE);
    if(!input.is_open()){
        std::exit(-1);
    }

    std::regex mul_regex("mul\\((\\d{1,3}),(\\d{1,3})\\)");
    std::regex do_regex("do\\(\\)");
    std::regex dont_regex("don't\\(\\)");
    std::string s;


    string temp;
    while(input >> temp){
        s+=temp;
    }
    vector<int> do_pos;
    vector<int> dont_pos;

    {
        auto words_begin = std::sregex_iterator(s.begin(), s.end(), do_regex);
        auto words_end = std::sregex_iterator();
        for(auto i = words_begin; i != words_end; i++){
            auto match = *i;
            do_pos.push_back(match.position());
        }
    }

    {
        auto words_begin = std::sregex_iterator(s.begin(), s.end(), dont_regex);
        auto words_end = std::sregex_iterator();
        for(auto i = words_begin; i != words_end; i++){
            auto match = *i;
            dont_pos.push_back(match.position());
        }
    }

    auto words_begin = std::sregex_iterator(s.begin(), s.end(), mul_regex);
    auto words_end = std::sregex_iterator();

    

    int64_t total = 0;

    
    for(auto i = words_begin; i != words_end; i++){
        auto match = *i;
        cout << match.str() << endl;
    
        if(match.size() < 3) continue;
        cout << "group 1: " <<  match[1].str() << endl;
        cout << "group 2: " <<  match[2].str() << endl;
        auto silly = match.position();

        int last_dont_pos = 0;
        for(auto dont_poses : dont_pos){
            if(dont_poses > silly) break;
            last_dont_pos = dont_poses;
        }

        int last_do_pos = 0;
        for(auto do_poses : do_pos){
            if(do_poses > silly) break;
            last_do_pos = do_poses;
        }

        


        // cout << "silly: " << silly << endl;
        // cout << "last_do_pos: " << last_do_pos << endl;
        // cout << "last_dont_pos: " << last_dont_pos << endl;
        if(last_do_pos >= last_dont_pos) total += std::stoi(match[1].str()) * std::stoi(match[2].str());
    }
    std::print("total: {}\n", total);
    cout << total << endl;
}
int main(){

    // auto start = std::chrono::steady_clock::now();
    // part1();
    // std::print("It took {} ms to run\n", std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start).count());
    part2();
} 
