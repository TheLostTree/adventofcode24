#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
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

    vector<int> list1;
    vector<int> list2;

    int int1, int2;
    while(input >> int1 >> int2){
        list1.push_back(int1);
        list2.push_back(int2);
    }


    sort(list1.begin(), list1.end());
    sort(list2.begin(), list2.end());

    int total = 0;
    int idx = 0;
    while(idx < list1.size()){
        total += abs(list1[idx] - list2[idx]);
        idx++;
    }

    cout << total << endl;


}
int occurrences(vector<int>& v, int num){
    int t = 0;
    for(int i : v){
        if(i == num) t++;
    }
    return t;
}
void part2(){
    std::ifstream input(INPUTFILE);
    if(!input.is_open()){
        std::exit(-1);
    }

    vector<int> list1;
    vector<int> list2;

    int int1, int2;
    while(input >> int1 >> int2){
        list1.push_back(int1);
        list2.push_back(int2);
    }

    int total = 0;
    for(int i : list1){
        total += i * occurrences(list2, i);
    }

    cout << total << endl;
}
int main(){
    part1();
    part2();
} 
