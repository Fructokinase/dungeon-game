#include "floor.h"
#include <cstdlib>
#include "Rect.h"

using namespace std;

Floor::Floor(int r, int c):ROW_NUM(r), COL_NUM(c) {};
Floor::~Floor(){};

string Floor::getLayout(){
    string result = "";

    for(int i = 0; i < ROW_NUM; i++){
        string tmp(layout[i].begin(), layout[i].end());
        result.append(tmp);
    }

    return result;
}

string Floor::getChamber(){
    string result = "";

    for(int i = 0; i < ROW_NUM; i++){
        string tmp(chamber[i].begin(), chamber[i].end());
        result.append(tmp);
    }

    return result;
}

void Floor::make(){
    layout.clear();
    chamber.clear();
    Floor::generateBasicLayout();
    Floor::generateChambers();
}

void Floor::generateBasicLayout(){

    // generate the east and west border
    for(int i = 0; i < ROW_NUM; i++) {

        vector<char> tmp;
        vector<char> chamberTmp;
        for(int j = 0; j < COL_NUM; j++) {
            if(j == 0 || j == COL_NUM - 1) {
                tmp.emplace_back('|');
                chamberTmp.emplace_back('|');
            } else {
                tmp.emplace_back(' ');
                chamberTmp.emplace_back(' ');
            }
        }
        layout.emplace_back(tmp);
        chamber.emplace_back(chamberTmp);
    }

    // generate the north and south border
    for(int j = 1; j < COL_NUM - 1; j++) {
        layout[0][j] = '-';
        chamber[0][j] = '-';
        layout[ROW_NUM - 1][j] = '-';
        chamber[ROW_NUM - 1][j] = '-';
    }
}

void Floor::digCell(int bridgeSeedX, int bridgeSeedY){

    int randRow;
    int randCol;

    bool found = false;

    while(!found){

        randRow = rand()%16;
        randCol = rand()%65;

        bool all_space = true;
        for(int i = 0; i < 6; i++) {
            for(int j = 0; j < 8; j++){
                if(layout[randRow + i][randCol + j] != ' ') all_space = false;
            }
        }

        if(all_space) {
            found = true;
        }
    }

    for(int i = 0; i < 6; i++) {
        for(int j = 0; j < 8; j++){
            if(i == 0 || i == 5) {
                layout[randRow + i][randCol + j] = '-';
            } else if(j == 0 || j == 7){
                layout[randRow + i][randCol + j] = '|';
            } else {
                layout[randRow + i][randCol + j] = '.';
                chamber[randRow + i][randCol + j] = '4';
            }
        }
    }

    int doorRow = rand()%3 + 1;
    if(bridgeSeedY > randCol + 8){
        layout[randRow + doorRow][randCol + 7] = '+';

        for(int i = randCol + 8; i <= bridgeSeedY ;i++){
            layout[randRow + doorRow][i] = '#';
        }
    } else {
        layout[randRow + doorRow][randCol] = '+';
    }

    for(int i = bridgeSeedY; i < randCol ;i++){
        layout[randRow + doorRow][i] = '#';
    }

    for(int j = bridgeSeedX; j <= randRow + doorRow; j ++) {
        layout[j][bridgeSeedY] = '#';
    }

}

Rect Floor::makeChamber(int startX, int startY, int endX, int endY){

    // first cordinate cannot be a part of the wall
    int x1 = startX;
    int y1 = startY;

    int x2 = x1 + 4 + rand()%(endX - x1 - 4);
    int y2 = y1 + 4 + rand()%(endY - y1 - 4);

    for(int i = x1; i < x2; i++) {
        for(int j = y1; j < y2; j++) {

            if(i == x1 || i == x2 - 1) {
                layout[i][j] = '-';
            } else if(j == y1 || j == y2 - 1) {
                layout[i][j] = '|';
            } else {
                layout[i][j] = '.';
            }

            
        }
    }

    return Rect{x1, y1, x2, y2};

}

void Floor::digBridge(int r, int c) {
        layout[r][c] = '#';
}

void Floor::labelChamber(Rect r, char label){
    for(int i = r.x1 + 1; i < r.x2 - 1; i++){
        for(int j = r.y1 + 1; j < r.y2 - 1; j++){
            chamber[i][j] = label;
        }
    }
}

void Floor::generateChambers(){

    int last_start_x;

    chambers.emplace_back(makeChamber(rand()%4 + 1, rand()%4 + 1, 15, 40));
    chambers.emplace_back(makeChamber(chambers[0].x2 + 1, 2, 23, 40));
    chambers.emplace_back(makeChamber(1, 41, 15, 77));

    if(chambers[0].y2 > chambers[1].y2) {
        last_start_x = chambers[0].y2 + 2;
    } else {
        last_start_x = chambers[1].y2 + 2;
    }
    chambers.emplace_back(makeChamber(chambers[2].x2 + 1, last_start_x , 23, 77));


    //label chamber numbers
    Floor::labelChamber(chambers[0], '0');
    Floor::labelChamber(chambers[1], '1');
    Floor::labelChamber(chambers[2], '2');
    Floor::labelChamber(chambers[3], '3');

    int bridgeSeedY;
    int bridgeSeedX;

   do{
        bridgeSeedX = rand()%10 + 5;
        bridgeSeedY = rand()%25 + 20;

    } while(layout[bridgeSeedX][bridgeSeedY] != ' ');

    // connect chambers 0
    int doorRow1 = chambers[0].x1 + rand()%(chambers[0].x2 - chambers[0].x1);
    layout[doorRow1][chambers[0].y2 - 1] = '+'; 
    layout[doorRow1][chambers[0].y2] = '#'; 

    for(int i = chambers[0].y2; i <= bridgeSeedY; i++) {
        layout[doorRow1][i] = '#';
    }

    for(int j = doorRow1; j <= bridgeSeedX; j++) {
        layout[j][bridgeSeedY] = '#';
    }

    for(int i = doorRow1; i <= bridgeSeedX ;i++){
        layout[i][chambers[0].y2] = '#';
    }

    int doorRow2 = chambers[1].x1 + rand()%(chambers[1].x2 - chambers[1].x1);
    layout[doorRow2][chambers[1].y2 - 1] = '+';
    layout[doorRow2][chambers[1].y2] = '#';

    for(int i = bridgeSeedX; i <= doorRow2 ;i++){
        layout[i][bridgeSeedY] = '#';
    }

    for(int j = chambers[1].y2; j < bridgeSeedY; j++){
        layout[doorRow2][j] = '#';
    }

    int doorRow3 = chambers[2].x1 + rand()%(chambers[2].x2 - chambers[2].x1);
    layout[doorRow3][chambers[2].y1 ] = '+'; 
    layout[doorRow3][chambers[2].y1 - 1] = '#'; 

    for(int i = bridgeSeedX; i >= doorRow3; i--) {
        layout[i][bridgeSeedY] = '#';
    }

    for(int j = bridgeSeedY; j < chambers[2].y1; j++){
        layout[doorRow3][j] = '#';
    }

    int doorRow4 = chambers[3].x1 + rand()%(chambers[3].x2 - chambers[3].x1);

    if(chambers[3].y2 > 35){
        layout[doorRow4][chambers[3].y1] = '+';  
        layout[doorRow4][chambers[3].y1 - 1] = '#';

        for(int i = bridgeSeedX; i <=  doorRow4; i++) {
            layout[i][chambers[3].y1 - 1] = '#';
        }
    } else {
        layout[doorRow4][chambers[3].y2] = '+';  
        layout[doorRow4][chambers[3].y2 + 1] = '#';
    }

    for(int i = bridgeSeedX; i<= doorRow4 ;i++){
        layout[i][bridgeSeedY] = '#';
    }

    for(int j = bridgeSeedY; j<= chambers[3].y1;j++){
        layout[doorRow4][j] = '#';
    }

    digBridge(bridgeSeedX, bridgeSeedY);

    digCell(bridgeSeedX, bridgeSeedY);


}

ostream &operator<<(ostream &out, const Floor &f) {


    // for the game board
    for (int i = 0; i < f.ROW_NUM; i++) {
        for (int j = 0; j < f.COL_NUM; j ++) {
            out  << f.layout[i][j];
        }
        out << endl;
    }

    // for (int i = 0; i < f.ROW_NUM; i++) {
    //     for (int j = 0; j < f.COL_NUM; j ++) {
    //         out  << f.chamber[i][j];
    //     }
    //     out << endl;
    // }

    return out;
}

