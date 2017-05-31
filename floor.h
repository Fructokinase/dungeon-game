#include <iostream>
#include <vector>
#include "Rect.h"

using namespace std;

class Floor{

    vector<vector<char>> layout;
    vector<vector<char>> chamber;

    int ROW_NUM;
    int COL_NUM;

    vector<Rect> chambers;

public:

    Floor(int, int);
    ~Floor();

    void make();

    string getLayout();
    string getChamber();

    void generateBasicLayout();

    void digCell(int, int);

    void digBridge(int, int);

    Rect makeChamber(int, int, int, int);

    void generateChambers();

    void labelChamber(Rect, char);

    friend std::ostream &operator<<(std::ostream &out, const Floor &f);
};
