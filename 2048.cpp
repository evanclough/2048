#include <iostream>
#include <array>
#include <stdio.h> 
#include <stdlib.h> 
#include<time.h> 
#include <vector>
#include <math.h> 
#include <set>
#include <map>
#include <algorithm>
using namespace std;


class Square {
    public:
        Square(int x, int y, int value) : x(x), y(y), value(value) {}      
        int x;
        int y;
        int value = 1;
        bool square_behind = false;
        bool square_ahead = false;
        bool square_behind_and_ahead = false;

};
vector<Square> squares = { Square(0, 0, 1) };

bool playing = true;
void show() {

    int grid[4][4];

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < squares.size(); k++) {
                if (squares[k].x == j && squares[k].y == i) {
                    grid[i][j] = squares[k].value;
                    break;
                }
                else {
                    grid[i][j] = 0;
                }
            }    
            if (grid[i][j] != 0) {
                if (j != 3) {
                    cout << "   " << pow(2, grid[i][j]) << "   ";
                }
                else {
                    cout << "   " << pow(2, grid[i][j]) << "   " << endl << endl << endl;
                }
            }
            else {
                if (j != 3) {
                    cout << "   -   ";
                }
                else {
                    cout << "   -   " << endl << endl << endl;
                }
            }
        }
    }
}


int score = 0;

void play(char move){
    bool movement = false;
    map<int, set<pair<int, int>>> x_keys;
    map<int, set<pair<int, int>>> y_keys;
    for (auto i : squares) {
        x_keys[i.x].insert({ i.y, i.value });
        y_keys[i.y].insert({ i.x, i.value });
    }
    for (auto i = squares.begin(); i != squares.end(); i++) {
        int didmovex = i->x;
        int didmovey = i->y;
        if (move == 'a') {
            
            pair<int, int> p = { i->x, i->value };
            auto it = y_keys[i->y].find(p);
            i->x = distance(y_keys[i->y].begin(), it);
        }
        else if (move == 'd') {
            pair<int, int> p = { i->x, i->value };
            auto it = y_keys[i->y].find(p);
            i->x = 4 - distance(it, y_keys[i->y].end());
        }
        else if (move == 'w') {
            pair<int, int> p = { i->y, i->value };
            auto it = x_keys[i->x].find(p);
            i->y = distance(x_keys[i->x].begin(), it);
        }
        else if (move == 's') {
            pair<int, int> p = { i->y, i->value };
            auto it = x_keys[i->x].find(p);
            i->y = 4 - distance(it, x_keys[i->x].end());
        }
        if (didmovex != i->x) movement = true;
        if (didmovey != i->y) movement = true;
    }
        x_keys.clear();
        y_keys.clear();
        for (auto i : squares) {
            x_keys[i.x].insert({ i.y, i.value });
            y_keys[i.y].insert({ i.x, i.value });
        }
        
        for (auto i = squares.begin(); i != squares.end(); i++) {
            i->square_behind = false;
            i->square_ahead = false;
            i->square_behind_and_ahead = false;
            if (move == 'a') {           
                if (y_keys[i->y].find({ i->x - 1, i->value }) != y_keys[i->y].end())
                    i->square_behind = true;
                if (y_keys[i->y].find({ i->x + 1, i->value }) != y_keys[i->y].end())
                    i->square_ahead = true;
                if (i->square_behind && i->square_ahead) {
                    i->square_behind_and_ahead = true;
                }
                if (i->square_ahead && !i->square_behind_and_ahead) {
                    i->value++;
                    score += i->value;
                }
                if (i->square_behind && !i->square_behind_and_ahead) {
                    i->value = 0;
                }
             
            }else if (move == 'd') {
                if (y_keys[i->y].find({ i->x - 1, i->value }) != y_keys[i->y].end())
                    i->square_behind = true;
                if (y_keys[i->y].find({ i->x + 1, i->value }) != y_keys[i->y].end())
                    i->square_ahead = true;
                if (i->square_behind && i->square_ahead) {
                    i->square_behind_and_ahead = true;
                }
                if (i->square_behind && !i->square_behind_and_ahead) {
                    i->value++;
                    score += i->value;
                }
                if (i->square_ahead && !i->square_behind_and_ahead) {
                    i->value = 0;
                }
            }else if (move == 'w') {
                if (x_keys[i->x].find({ i->y - 1, i->value }) != x_keys[i->x].end())
                    i->square_behind = true;
                if (x_keys[i->x].find({ i->y + 1, i->value }) != x_keys[i->x].end())
                    i->square_ahead = true;
                if (i->square_behind && i->square_ahead) {
                    i->square_behind_and_ahead = true;
                }
                if (i->square_ahead && !i->square_behind_and_ahead) {
                    score += i->value;
                    i->value++;
                    
                }
                if (i->square_behind && !i->square_behind_and_ahead) {
                    i->value = 0;
                }
            }else if (move == 's') {
                if (x_keys[i->x].find({ i->y - 1, i->value }) != x_keys[i->x].end())
                    i->square_behind = true;
                if (x_keys[i->x].find({ i->y + 1, i->value }) != x_keys[i->x].end())
                    i->square_ahead = true;
                if (i->square_behind && i->square_ahead) {
                    i->square_behind_and_ahead = true;
                }
                if (i->square_behind && !i->square_behind_and_ahead) {
                    score += i->value;
                    i->value++;

                }
                if (i->square_ahead && !i->square_behind_and_ahead) {
                    i->value = 0;
                }
            }   
        }
        for (int i = 0; i < squares.size(); i++) {
            if (squares[i].value == 0) {
                squares.erase(squares.begin() + i);
                movement = true;
            }
        }
        x_keys.clear();
        y_keys.clear();
        for (auto i : squares) {
            x_keys[i.x].insert({ i.y, i.value });
            y_keys[i.y].insert({ i.x, i.value });
        }
        for (auto i = squares.begin(); i != squares.end(); i++) {
            int didmovex = i->x;
            int didmovey = i->y;
            if (move == 'a') {

                pair<int, int> p = { i->x, i->value };
                auto it = y_keys[i->y].find(p);
                i->x = distance(y_keys[i->y].begin(), it);
            }
            else if (move == 'd') {
                pair<int, int> p = { i->x, i->value };
                auto it = y_keys[i->y].find(p);
                i->x = 4 - distance(it, y_keys[i->y].end());
            }
            else if (move == 'w') {
                pair<int, int> p = { i->y, i->value };
                auto it = x_keys[i->x].find(p);
                i->y = distance(x_keys[i->x].begin(), it);
            }
            else if (move == 's') {
                pair<int, int> p = { i->y, i->value };
                auto it = x_keys[i->x].find(p);
                i->y = 4 - distance(it, x_keys[i->x].end());
            }
            if (didmovex != i->x) movement = true;
            if (didmovey != i->y) movement = true;
        }
        x_keys.clear();
        y_keys.clear();
        for (auto i : squares) {
            x_keys[i.x].insert({ i.y, i.value });
            y_keys[i.y].insert({ i.x, i.value });
        }
       
        int grid[4][4];
        vector<int> empty_x;
        vector<int> empty_y;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                for (int k = 0; k < squares.size(); k++) {
                    if (squares[k].x == j && squares[k].y == i) {
                        grid[i][j] = squares[k].value;
                        break;
                    }
                    else {
                        grid[i][j] = 0;
                    }
                }
            }
        }
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (grid[i][j] == 0) {
                    empty_x.push_back(i);
                    empty_y.push_back(j);
                    
                }
            }
        }
        if (!movement && squares.size() == 16) {
            
            squares.clear();
            cout << "You lost" << endl;
            cout << "Score: " << score << endl;
            score = 0;
        }
        srand(time(NULL));

        
        if (movement) {
            int randindex = rand() % empty_x.size();
            squares.push_back(Square(empty_y[randindex], empty_x[randindex], (rand() % 2) + 1));
            
        }
        
        
    }

   

int main() {
    cout << "2048" << endl;
    cout << "Use the WASD keys to move." << endl;
    cout << "Press Z to quit" << endl;
    show();
    char move;
    do {
        cin >> move;
        play(move);
        show();
        
    } while (move != 'z' && playing);
}
