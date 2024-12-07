#include <fstream>
#include <iostream>
// #define TEST
#ifdef TEST
    #define INPUTFILE "test.txt"
#else
    #define INPUTFILE "input.txt"
#endif
using namespace std;

enum Tile{
    Invalid,
    Nothing,
    Wall,
    Walked
};

struct IntTuple{
    int y;
    int x;
};

struct WallHistoryItem{
    IntTuple pos;
    IntTuple approach_dir;
};

IntTuple operator+(IntTuple lhs, IntTuple rhs){
    return {lhs.y + rhs.y, lhs.x + rhs.x};
}

IntTuple operator-(IntTuple lhs, IntTuple rhs){
    return {lhs.y - rhs.y, lhs.x - rhs.x};
}



template<typename T>
ostream& operator<<(ostream& stream, std::vector<T> vec){
    for(auto iter = vec.begin(); iter != vec.end(); iter++){
        cout << *iter << (iter + 1 == vec.end() ? "" : " ");
    }
    return stream;
}

ostream& operator<<(ostream& stream, IntTuple& tuple){
    return stream << "y: "<< tuple.y<< ", x: "  << tuple.x;
}
Tile invalid_tile = Invalid;

//just make sure to check for invalid b4 modifying...
Tile& get_tile(std::vector<std::vector<Tile>>& board, int y, int x){
    if(y < 0 || y >= board.size()) return invalid_tile;
    if(x < 0 || x >= board[0].size()) return invalid_tile;
    return board[y][x];
}
Tile& get_tile(std::vector<std::vector<Tile>>& board, IntTuple t){
    return get_tile(board, t.y, t.x);
}




void part1(){
    std::ifstream input(INPUTFILE);
    if(!input.is_open()){
        std::exit(-1);
    }

    std::vector<std::vector<Tile>> map;

    IntTuple guard_pos;
    std::string s;
    while(std::getline(input, s)){
        std::vector<Tile> tiles;
        for(char c : s){
            switch(c){
                case '.':
                    tiles.push_back(Tile::Nothing);
                    break;
                case '#':
                    tiles.push_back(Tile::Wall);
                    break;
                case '^':
                    guard_pos.y = map.size();
                    guard_pos.x = tiles.size();
                    tiles.push_back(Tile::Nothing);
                    break;
                default:
            }
        }
        map.push_back(tiles);
    }
    IntTuple guard_dir = {
        -1, // negative y is going up
        0
    };


    for(;;){
        IntTuple next_pos = guard_pos + guard_dir;
        Tile& next_tile = get_tile(map, next_pos);
        switch(next_tile){
            case Tile::Invalid:
                //todo: leave loop.
                break;
            case Tile::Walked:
            case Tile::Nothing:
                //valid spot to walk
                next_tile = Tile::Walked;
                guard_pos = next_pos;
                continue;
            case Tile::Wall:
                IntTuple new_dir = {
                    guard_dir.x,
                    -guard_dir.y
                };
                guard_dir = new_dir;
                continue;
        }
        break;
    }

    int total = 0;

    for(int y = 0;y<map.size(); y++){
        for(int x = 0;x <map.size(); x++){
            total += map[y][x] == Tile::Walked ? 1 : 0;
        }
    }

    cout << "part 1: " << total << endl;

}

int run_simulation(std::vector<std::vector<Tile>>& map, IntTuple guard_pos, IntTuple guard_dir){
    int steps = 0;
    for(;;){
        IntTuple next_pos = guard_pos + guard_dir;
        Tile& next_tile = get_tile(map, next_pos);
        IntTuple new_dir = {
            guard_dir.x,
            -guard_dir.y
        };
        switch(next_tile){
            case Tile::Invalid:
                //leave loop
                break;
            case Tile::Walked:
            case Tile::Nothing:
                //valid spot to walk
                /*
                we have some potential walls in wall_history we can point our guard towards

                if we put a fake wall at next_tile, guard will turn 90 degrees then theoretically walk to one of the walls in wall_history

                only every 4 walls is valid (bc direction cycles)
                eg: if we have turned 7 times (same as 3 times), we can only possibly encounter the 4th 8th wall etc
                uint idx = wall_history.size() % 4
                
                
                */
                next_tile = Tile::Walked;
                guard_pos = next_pos;
                steps++;
                if(steps > map.size() * map[0].size()){
                    return -1;
                }
                continue;
            case Tile::Wall:
                guard_dir = new_dir;
                continue;
        }
        //if u add code after the switch pls rethink the switch case above!
        return steps;
    }  
}
void part2(){
    std::ifstream input(INPUTFILE);
    if(!input.is_open()){
        std::exit(-1);
    }

    std::vector<std::vector<Tile>> map;

    IntTuple guard_pos;
    IntTuple guard_pos_2;
    std::string s;
    while(std::getline(input, s)){
        std::vector<Tile> tiles;
        for(char c : s){
            switch(c){
                case '.':
                    tiles.push_back(Tile::Nothing);
                    break;
                case '#':
                    tiles.push_back(Tile::Wall);
                    break;
                case '^':
                    guard_pos.y = map.size();
                    guard_pos.x = tiles.size();
                    tiles.push_back(Tile::Nothing);
                    break;
                default:
            }
        }
        map.push_back(tiles);
    }
    IntTuple guard_dir = {
        -1, // negative y is going up
        0
    };

    guard_pos_2 = guard_pos;


    std::vector<WallHistoryItem> wall_history;
    std::vector<WallHistoryItem> walk_history;


    int total_ghost_walls = 0;
    for(;;){
        IntTuple next_pos = guard_pos + guard_dir;
        Tile& next_tile = get_tile(map, next_pos);
        IntTuple new_dir = {
            guard_dir.x,
            -guard_dir.y
        };
        switch(next_tile){
            case Tile::Invalid:
                //leave loop
                break;
            case Tile::Walked:
            case Tile::Nothing:
                //valid spot to walk
                /*
                we have some potential walls in wall_history we can point our guard towards

                if we put a fake wall at next_tile, guard will turn 90 degrees then theoretically walk to one of the walls in wall_history

                only every 4 walls is valid (bc direction cycles)
                eg: if we have turned 7 times (same as 3 times), we can only possibly encounter the 4th 8th wall etc
                uint idx = wall_history.size() % 4
                
                
                */
                next_tile = Tile::Walked;
                guard_pos = next_pos;
                walk_history.push_back({
                    guard_pos,
                    guard_dir
                });
                continue;
            case Tile::Wall:
                wall_history.push_back({
                    next_pos,
                    guard_dir
                });
                guard_dir = new_dir;
                continue;
        }
        //if u add code after the switch pls rethink the switch case above!
        break;
    }
    
    //we do it again!
    guard_dir = { -1, 0};
    guard_pos = guard_pos_2;

    //bruteforced 
    //i spent longer trying to be smart about it than this would actually run like 1k times over
    for(uint i = 0; i < map.size(); i++){
        for(uint j = 0; j < map[0].size(); j++){
            // cout<< i<< " " << j << endl;
            Tile orig = get_tile(map, i,j);
            get_tile(map, i,j) = Tile::Wall;
            int steps = run_simulation(map, guard_pos, guard_dir);
            get_tile(map, i,j) = orig;
            if(steps == -1) total_ghost_walls++;
        }
    }

    cout << "part 2: " << total_ghost_walls << endl;
}
int main(){
    part1();
    part2();
} 
