#include <fstream>
#include <iostream>
#define TEST
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
}
void part2(){
    std::ifstream input(INPUTFILE);
    if(!input.is_open()){
        std::exit(-1);
    }
}
int main(){
    part1();
    part2();
} 
