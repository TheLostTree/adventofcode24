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

void part1(){
    std::ifstream input(INPUTFILE);
    if(!input.is_open()){
        std::exit(-1);
    }
    std::vector<int> v;
    std::string line;

    int total = 0;

    while(std::getline(input, line)){
        int max = 0;
        int min = 0;
        v.clear();
        istringstream s;
        s.str(line);
        int a;
        while(s >> a){
            v.push_back(a);
        }
        
        for(uint i = 0; i + 1 < v.size(); i++){
            auto diff = v[i+1] - v[i];
            if(!diff) {
                max = 0; min = 0;
                break;
            }
            max = std::max(diff, max);
            min = std::min(diff, min);
            
        }

        if((max == 0) != (min == 0)){
            auto interesting = (min == 0) ? max : min;
            if (std::abs(interesting) <=3 ) total++;
        }

    }
    cout << "part 1: " << total << endl;

}
void part2(){
    std::ifstream input(INPUTFILE);
    if(!input.is_open()){
        std::exit(-1);
    }

    std::vector<int> v;
    std::string line;

    int total = 0;

    while(std::getline(input, line)){
        
        v.clear();
        istringstream s;
        s.str(line);
        int a;
        while(s >> a){
            v.push_back(a);
        }

        for(int skip = 0; skip < v.size(); skip++){
            int max = 0;
            int min = 0;
            std::vector<int> indexes;
            for(int i = 0; i < v.size(); i++){
                if(i == skip) continue;
                indexes.push_back(i);
            }


            for(uint i = 0; i + 1 < indexes.size(); i++){
                int idx = indexes[i];
                int next_idx = indexes[i+1];

                auto diff = v[next_idx] - v[idx];
                if(!diff) {
                    max = 0; min = 0;
                    break;
                }
                max = std::max(diff, max);
                min = std::min(diff, min);
                
            }

            if((max == 0) != (min == 0)){
                auto interesting = (min == 0) ? max : min;
                if (std::abs(interesting) <=3 ) {
                    total++;
                    break;
                }
        }
        }

    }
    cout << "part 2: " << total << endl;
}
int main(){
    part1();
    part2();
} 
