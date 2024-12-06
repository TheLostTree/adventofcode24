#include <fstream>
#include <iostream>
// #define TEST
#ifdef TEST
    #define INPUTFILE "test.txt"
#else
    #define INPUTFILE "input.txt"
#endif
using namespace std;

ostream& operator<<(ostream& stream, std::vector<char>& board){
    for(char& c : board){
        stream << c << " ";
    }
    return stream;
}

ostream& operator<<(ostream& stream, std::vector<std::vector<char>>& board){
    for(std::vector<char>& line : board){
        stream << line << endl;
    }
    return stream;
}

char xmas[] = {'X', 'M', 'A', 'S'};

char check_letter(vector<vector<char>>& board, uint y, uint x){
    if(y >= board.size() || y < 0) return 0;
    if(x < 0 || (board.size() && (x >= board[0].size()))) return 0;
    return board[y][x];
}

int get_xmas_count(vector<vector<char>>& board, uint y, uint x){
    int xmas_count = 0;
    for(int ydir = -1; ydir < 2; ydir++){
        for(int xdir = -1; xdir < 2; xdir++){
            if(ydir == 0 && xdir == 0) continue;
            int test_y = y;
            int test_x = x;
            int matches = 0;
            for(uint letter_idx = 0; letter_idx < 4; letter_idx++){
                char letter = check_letter(board, test_y, test_x);
                // std::println("letter at {} {} is {}", x ,y, letter);
                if(xmas[letter_idx] == letter){
                    test_y += ydir;
                    test_x += xdir;
                    matches++;
                }else{
                    break;
                }
            }

            xmas_count += matches == 4 ? 1 : 0;
        }
    }
    return xmas_count;
}
struct point{
    int y;
    int x;
};


int get_mas_in_x_count(vector<vector<char>>& board, uint y, uint x){
    //x+1 and y+1 is in bounds
    //x-1 and y-1 is in bounds 
    

    //if 'A'
    //find 'M' dir
    //assert there are two 'M' dirs
    //assert that the opposite of the 'M' dir has an 'S'
    std::vector<point> m_dirs;

    point diags[] = {
        {-1,-1},{-1,1},{1,1},{1,-1}
    };
    if(check_letter(board, y, x) == 'A'){
        for(uint i = 0; i < 4; i++){
            int ydir = diags[i].y;
            int xdir = diags[i].x;
            if('M' == check_letter(board, y + ydir, x + xdir)){
                if('S' == check_letter(board , y - ydir, x - xdir)){
                    m_dirs.push_back({ydir,xdir});
                }
            }
            
        }
    }else{
        return 0;
    }

    if(m_dirs.size() == 2){
        // cout << "y x " << y <<" " << x << endl;
        return 1;
    }

    
    return 0;
}


void part1(){
    std::ifstream input(INPUTFILE);
    if(!input.is_open()){
        std::exit(-1);
    }

    std::vector<std::vector<char>> board;

    std::string s;
    while(std::getline(input, s)){
        std::vector<char> line;
        for(char ch : s){
            line.push_back(ch);
        }
        board.push_back(line);
    }

    uint y = 0;
    uint x = 0;


    cout << board << endl;

    int total = 0;

    for(uint y_idx = 0; y_idx < board.size(); y_idx++){
        for(uint x_idx = 0; board.size() && x_idx < board[0].size(); x_idx++){
            total += get_xmas_count(board, x_idx, y_idx);
        }
    }

    std::println("there are {} xmases", total);
}
void part2(){
    std::ifstream input(INPUTFILE);
    if(!input.is_open()){
        std::exit(-1);
    }


    std::vector<std::vector<char>> board;

    std::string s;
    while(std::getline(input, s)){
        std::vector<char> line;
        for(char ch : s){
            line.push_back(ch);
        }
        board.push_back(line);
    }

    uint y = 0;
    uint x = 0;


    cout << board << endl;

    int total = 0;

    for(uint y_idx = 1; y_idx+1 < board.size(); y_idx++){
        for(uint x_idx = 1; board.size() && x_idx+1 < board[0].size(); x_idx++){
            total += get_mas_in_x_count(board, x_idx, y_idx);
        }
    }

    std::println("there are {} xmases", total);
}
int main(){
    part1();
    part2();
} 
