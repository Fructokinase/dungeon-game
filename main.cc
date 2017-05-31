#include <iostream>
#include <fstream>
#include <string>
#include "game.h"
#include <cstdlib>
#include "floor.h"
#include <ncurses.h>

using namespace std;

int main(int argc, char* argv[]){

    int seed = static_cast<int>(time(0));
    srand(seed);

    string MAP_FILE_NAME = "";
    bool useDefaultMap = true;
    bool useRandomMap = false;


    //commandl line arguments control
    if(argc > 1) {
        string firstCommand = argv[1];
        if(firstCommand == "randomize") {
            useRandomMap = true;
        } else {
            MAP_FILE_NAME = argv[1];
            useDefaultMap = false;
        }
    } else {
        MAP_FILE_NAME = "example_map.txt";
    }

    //prepares to read the map file
    ifstream map_file (MAP_FILE_NAME);
    string line;
    string map_layout = "";
    string chamber_layout = "";


    //reads the map from the specified file
    if(!useRandomMap){
        if (map_file.is_open()) {
            while ( getline(map_file, line) ) {
                map_layout+=line;
            }
            map_file.close();
        }
    }

    Floor f = Floor{25, 79};

    if(useRandomMap){
        for(int i = 0; i < 5; i++) {
            f.make();
            map_layout+=f.getLayout();
            chamber_layout+=f.getChamber();
        }
    }

    if(!useRandomMap){
        if(useDefaultMap){
         //reads the map from the specified file
            ifstream chamber_file ("chamber.txt");
            if (chamber_file.is_open()) {
                while ( getline(chamber_file, line) ) {
                    chamber_layout+=line;
                }
                chamber_file.close();
            }
        }
    }

    // START GAME
    string command;
    string direction;
    string race;

    while (true){

        cout << "Please enter a race to continue or 'q' to quit" << endl;
        cout << "Races: 'shade', 'drow', 'vampire', 'troll', 'goblin'" << endl;
        cin >> race;
        if(race == "q") return 1;

        Game g{map_layout, chamber_layout, 5};

        if(useDefaultMap){
            g.init(race);
        } else {
            // use when the position of everything is given
            // hence no chamberlayout
            g.init(race, true);
        }

        int game_status = 1;

        cout << g;

        while(cin >> command) {
            if (command == "q"){
                return 1;
            } else if (command == "r") {
                break;
            } else if (command == "f"){
                g.freezeEnemies();
            } else if (command == "a"){
                cin >> direction;
                g.attack(direction);
            } else if (command == "u"){
                cin >> direction;
                g.usePotion(direction);
                game_status = g.nextTurn();
            } else if (command == "no" || command == "so" || command == "we" || command == "ea" ||
                command == "nw" || command == "ne" || command == "se" || command == "sw" ){
                int game_status =  g.movePlayer(command);

                if(game_status == 2) {
                    cout << g;
                    int win_status = g.getScore();
                    cout << "Your score is " << win_status << endl;
                    break;
                }

                game_status = g.nextTurn();
            } else if (command == "move"){
                //this is admin move
                cin >> command;
                int x = 0;
                int y = 0;

                if(command == "v") {
                    cin >> x;
                } else if (command == "h") {
                    cin >> y;
                }

                g.movePlayer(-x, y);
                game_status = g.nextTurn();
            } else if (command  == "floor"){
                int win_status = g.changeFloor(1);

                if(win_status != -1) {
                    cout << "Your score is " << win_status << endl;
                    break;
                }

            } else {
                game_status = g.nextTurn();
            }

            cout << g;

            //when a player is dead
            if (game_status == 0){
                cout << "Game over" << endl;
                break;
            }
        };
    }


};
