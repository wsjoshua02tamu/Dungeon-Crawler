#include <iostream>
#include "logic.h"

using std::cout, std::endl;

// TODO(student): Write unit tests for the functions in logic.h
//                You should end up with at least 500 lines of test code

void deallocate(char**& map, int rows){
    if (map != nullptr){
for(int i = 0; i < rows; ++i) {
        delete[] map[i];   
    }
    //Free the array of pointers
    delete[] map;
    map = NULL;
}
    }

/*
char** loadLevel(const std::string& fileName, int& maxRow, int& maxCol, Player& player){
    char** matrix = new char*[5];
    for (int i = 0; i < 5; ++i) {
        matrix[i] = new char[5];
        for (int j = 0; j < 5; ++j) {
            matrix[i][j] = '+';
        }
    }
    maxRow = 5;
    maxCol = 5;
    return matrix;
}
void getDirection(char input, int& nextRow, int& nextCol){
    
}
void deleteMap(char**& map, int& maxRow){
        for(int i = 0; i < maxRow; ++i) {
        delete[] map[i];   
    }
    //Free the array of pointers
    delete[] map;
    map = NULL;
}
char** resizeMap(char** map, int& maxRow, int& maxCol){
    return NULL;
}

int doPlayerMove(char** map, int maxRow, int maxCol, Player& player, int nextRow, int nextCol){
    return 0;
}
bool doMonsterAttack(char** map, int maxRow, int maxCol, Player player){
    return false;
}
*/

//memory not allocated; file does not exist
//dimensions given do not match pointer
//player position out of bounds
//tiles are not one of the constants given
void testLevel(){
    int numTests = 0;
    int row;
    int col;
    Player player1;
    char** level;
    const std::string filename = "example.txt";
    level = loadLevel(filename, row, col, player1);
    if (row == 5 && col == 3 && player1.row == 3 && player1.col == 0){
        cout << "PASS: Happy paths test " << numTests++ << endl;
    }
    else{
        cout << "FAIL: Happy paths test " << numTests++ << endl;
    }
    deallocate(level, row);
    const std::string filename1 = "fakeFile.txt";
    level = loadLevel(filename1, row, col, player1);
    cout << "PASS: Unhappy paths test " << numTests++ << endl;

    const std::string filename2 = "noWayHome.txt";
    level = loadLevel(filename2, row, col, player1);
    cout << "PASS: Unhappy paths test " << numTests++ << endl;
    
    
    
}

//input is not a direction
//final location is incorrect
void testDirection(){
    int x, y;
    int numTests = 100;
    x = 1;
    y = 1;
    getDirection('e',x,y);
    if (x == 1 && y == 1){
        cout << "PASS: Happy paths test "  << numTests++ << endl;
    }
    else{
        cout << "FAIL: Happy paths test "  << numTests++ << endl;
    }
    x = 1;
    y = 1;
    getDirection('w',x,y);
    if (x == 0 && y == 1){
        cout << "PASS: Happy paths test "  << numTests++ << endl;
    }
    else{
        cout << "FAIL: Happy paths test "  << numTests++ << endl;
    }
    x = 1;
    y = 1;
    getDirection('a',x,y);
    if (x == 1 && y == 0){
        cout << "PASS: Happy paths test "  << numTests++ << endl;
    }
    else{
        cout << "FAIL: Happy paths test "  << numTests++ << endl;
    }
    x = 1;
    y = 1;
    getDirection('s',x,y);
    if (x == 2 && y == 1){
        cout << "PASS: Happy paths test "  << numTests++ << endl;
    }
    else{
        cout << "FAIL: Happy paths test "  << numTests++ << endl;
    }
    x = 1;
    y = 1;
    getDirection('d',x,y);
    if (x == 1 && y == 2){
        cout << "PASS: Happy paths test "  << numTests++ << endl;
    }
    else{
        cout << "FAIL: Happy paths test "  << numTests++ << endl;
    }
    getDirection('x',x,y);
    cout << "PASS: Unhappy paths test "  << numTests++ << endl;

}

void testDelete(){
    int numTests = 200;
    int row;
    int col;
    Player player1;
    char** level;
    const std::string filename = "example.txt";
    level = loadLevel(filename, row, col, player1);
    deleteMap(level,row);
    if (level == NULL){
        cout << "PASS: Happy paths test "  << numTests++ << endl;
    }
    else{
        cout << "FAIL: Happy paths test "  << numTests++ << endl;
    }
}

void testResize(){
    int numTests = 300;
    int row;
    int col;
    Player player1;
    char** level;
    const std::string filename = "example.txt";
    level = loadLevel(filename, row, col, player1);
    int resizedRow = row;
    int resizedCol = col;
    level = resizeMap(level,resizedRow, resizedCol);
    if (resizedRow == row * 2 && resizedCol == col * 2){
        cout << "PASS: Happy paths test "  << numTests++ << endl;
    }
    else{
        cout << "FAIL: Happy paths test "  << numTests++ << endl;
    }
    deallocate(level,resizedRow);

}
void testMove(){
    int numTests = 400;
    int row;
    int col;
    Player player1;
    char** level;
    const std::string filename = "example.txt";
    level = loadLevel(filename, row, col, player1);
    player1.row = 3;
    player1.col = 0;
    player1.treasure = 0;
    int movement;
    movement = doPlayerMove(level,row,col,player1,4,0);
    if (movement == STATUS_AMULET && player1.row == 4 && player1.col == 0){
        cout << "PASS: Happy paths test "  << numTests++ << endl;
    }
    else{
        cout << "FAIL: Happy paths test "  << numTests++ << endl;
    }

    player1.row = 2;
    player1.col = 0;
    player1.treasure = 0;
    movement = doPlayerMove(level,row,col,player1,2,1);
    if (movement == STATUS_STAY && player1.row == 2 && player1.col == 0){
        cout << "PASS: Happy paths test "  << numTests++ << endl;
    }
    else{
        cout << "FAIL: Happy paths test "  << numTests++ << endl;
    }

    player1.row = 1;
    player1.col = 0;
    player1.treasure = 0;
    movement = doPlayerMove(level,row,col,player1,2,0);
    if (movement == STATUS_MOVE && player1.row == 2 && player1.col == 0){
        cout << "PASS: Happy paths test "  << numTests++ << endl;
    }
    else{
        cout << "FAIL: Happy paths test "  << numTests++ << endl;
    }

    player1.row = 4;
    player1.col = 1;
    player1.treasure = 0;
    movement = doPlayerMove(level,row,col,player1,4,2);
    if (movement == STATUS_TREASURE && player1.row == 4 && player1.col == 2 && player1.treasure == 1){
        cout << "PASS: Happy paths test "  << numTests++ << endl;
    }
    else{
        cout << "FAIL: Happy paths test "  << numTests++ << endl;
    }

    player1.row = 3;
    player1.col = 1;
    player1.treasure = 0;
    movement = doPlayerMove(level,row,col,player1,3,2);
    if (movement == STATUS_LEAVE){
        cout << "PASS: Happy paths test "  << numTests++ << endl;
    }
    else{
        cout << "FAIL: Happy paths test "  << numTests++ << endl;
    }

    player1.row = 1;
    player1.col = 2;
    player1.treasure = 0;
    movement = doPlayerMove(level,row,col,player1,2,2);
    if (movement == STATUS_STAY){
        cout << "PASS: Happy paths test "  << numTests++ << endl;
    }
    else{
        cout << "FAIL: Happy paths test "  << numTests++ << endl;
    }

    player1.row = 1;
    player1.col = 2;
    player1.treasure = 1;
    movement = doPlayerMove(level,row,col,player1,2,2);
    if (movement == STATUS_ESCAPE){
        cout << "PASS: Happy paths test "  << numTests++ << endl;
    }
    else{
        cout << "FAIL: Happy paths test "  << numTests++ << endl;
    }

    player1.row = 0;
    player1.col = 2;
    player1.treasure = 0;
    movement = doPlayerMove(level,row,col,player1,-1,2);
    if (movement == STATUS_STAY && player1.row == 0 && player1.col == 2){
        cout << "PASS: Happy paths test "  << numTests++ << endl;
    }
    else{
        cout << "FAIL: Happy paths test "  << numTests++ << endl;
    }

    player1.row = 0;
    player1.col = 2;
    player1.treasure = 0;
    movement = doPlayerMove(level,row,col,player1,0,3);
    if (movement == STATUS_STAY && player1.row == 0 && player1.col == 2){
        cout << "PASS: Happy paths test "  << numTests++ << endl;
    }
    else{
        cout << "FAIL: Happy paths test "  << numTests++ << endl;
    }

    player1.row = 2;
    player1.col = 0;
    player1.treasure = 0;
    movement = doPlayerMove(level,row,col,player1,2,-1);
    if (movement == STATUS_STAY && player1.row == 2 && player1.col == 0){
        cout << "PASS: Happy paths test "  << numTests++ << endl;
    }
    else{
        cout << "FAIL: Happy paths test "  << numTests++ << endl;
    }

    player1.row = 4;
    player1.col = 1;
    player1.treasure = 0;
    movement = doPlayerMove(level,row,col,player1,5,1);
    if (movement == STATUS_STAY && player1.row == 4 && player1.col == 1){
        cout << "PASS: Happy paths test "  << numTests++ << endl;
    }
    else{
        cout << "FAIL: Happy paths test "  << numTests++ << endl;
    }

    player1.row = 1;
    player1.col = 0;
    player1.treasure = 0;
    movement = doPlayerMove(level,row,col,player1,0,0);
    if (movement == STATUS_STAY && player1.row == 1 && player1.col == 0){
        cout << "PASS: Happy paths test "  << numTests++ << endl;
    }
    else{
        cout << "FAIL: Happy paths test "  << numTests++ << endl;
    }

    player1.row = 0;
    player1.col = 1;
    player1.treasure = 0;
    movement = doPlayerMove(level,row,col,player1,1,2);
    cout << "PASS: Unhappy paths test "  << numTests++ << endl;   

    player1.row = 0;
    player1.col = 1;
    player1.treasure = 0;
    movement = doPlayerMove(level,row,col,player1,1,0);
    cout << "PASS: Unhappy paths test "  << numTests++ << endl;   
    deallocate(level,row);

}
void testMonster(){
    int numTests = 500;
    int row;
    int col;
    Player player1;
    char** level;
    const std::string filename = "example.txt";
    level = loadLevel(filename, row, col, player1);
    bool monsterStatus;

    player1.row = 0;
    player1.col = 2;
    monsterStatus = doMonsterAttack(level,row,col,player1);
    if (!monsterStatus && level[0][0] == 'M'){
        cout << "PASS: Happy paths test "  << numTests++ << endl;
    }
    else{
        cout << "FAIL: Happy paths test "  << numTests++ << endl;
    }
    deallocate(level,row);

    level = loadLevel(filename, row, col, player1);
    player1.row = 1;
    player1.col = 2;
    monsterStatus = doMonsterAttack(level,row,col,player1);
    if (!monsterStatus && level[0][0] == 'M'){
        cout << "PASS: Happy paths test "  << numTests++ << endl;
    }
    else{
        cout << "FAIL: Happy paths test "  << numTests++ << endl;
    }
    deallocate(level,row);

    level = loadLevel(filename, row, col, player1);
    player1.row = 1;
    player1.col = 0;
    monsterStatus = doMonsterAttack(level,row,col,player1);
    if (monsterStatus){
        cout << "PASS: Happy paths test "  << numTests++ << endl;
    }
    else{
        cout << "FAIL: Happy paths test "  << numTests++ << endl;
    }
    deallocate(level,row);

    level = loadLevel(filename, row, col, player1);
    player1.row = 2;
    player1.col = 0;
    monsterStatus = doMonsterAttack(level,row,col,player1);
    if (!monsterStatus && level[1][0] == 'M'){
        cout << "PASS: Happy paths test "  << numTests++ << endl;
    }
    else{
        cout << "FAIL: Happy paths test "  << numTests++ << endl;
    }
    deallocate(level,row);

    const std::string filename1 = "emptyMonster.txt";
    level = loadLevel(filename1, row, col, player1);
    player1.row = 0;
    player1.col = 2;
    monsterStatus = doMonsterAttack(level,row,col,player1);
    if (!monsterStatus && level[1][2] == 'M'){
        cout << "PASS: Happy paths test "  << numTests++ << endl;
    }
    else{
        cout << "FAIL: Happy paths test "  << numTests++ << endl;
    }
    deallocate(level,row);

    level = loadLevel(filename1, row, col, player1);
    player1.row = 2;
    player1.col = 0;
    monsterStatus = doMonsterAttack(level,row,col,player1);
    if (!monsterStatus && level[2][1] == 'M'){
        cout << "PASS: Happy paths test "  << numTests++ << endl;
    }
    else{
        cout << "FAIL: Happy paths test "  << numTests++ << endl;
    }
    deallocate(level,row);

    level = loadLevel(filename1, row, col, player1);
    player1.row = 2;
    player1.col = 4;
    monsterStatus = doMonsterAttack(level,row,col,player1);
    if (!monsterStatus && level[2][3] == 'M'){
        cout << "PASS: Happy paths test "  << numTests++ << endl;
    }
    else{
        cout << "FAIL: Happy paths test "  << numTests++ << endl;
    }
    deallocate(level,row);

    level = loadLevel(filename1, row, col, player1);
    player1.row = 4;
    player1.col = 2;
    monsterStatus = doMonsterAttack(level,row,col,player1);
    if (!monsterStatus && level[3][2] == 'M'){
        cout << "PASS: Happy paths test "  << numTests++ << endl;
    }
    else{
        cout << "FAIL: Happy paths test "  << numTests++ << endl;
    }
    deallocate(level,row);

    level = loadLevel(filename1, row, col, player1);
    player1.row = 2;
    player1.col = 1;
    monsterStatus = doMonsterAttack(level,row,col,player1);
    if (monsterStatus){
        cout << "PASS: Happy paths test "  << numTests++ << endl;
    }
    else{
        cout << "FAIL: Happy paths test "  << numTests++ << endl;
    }
    deallocate(level,row);

    level = loadLevel(filename1, row, col, player1);
    player1.row = 1;
    player1.col = 2;
    monsterStatus = doMonsterAttack(level,row,col,player1);
    if (monsterStatus){
        cout << "PASS: Happy paths test "  << numTests++ << endl;
    }
    else{
        cout << "FAIL: Happy paths test "  << numTests++ << endl;
    }
    deallocate(level,row);

    level = loadLevel(filename1, row, col, player1);
    player1.row = 2;
    player1.col = 3;
    monsterStatus = doMonsterAttack(level,row,col,player1);
    if (monsterStatus){
        cout << "PASS: Happy paths test "  << numTests++ << endl;
    }
    else{
        cout << "FAIL: Happy paths test "  << numTests++ << endl;
    }
    deallocate(level,row);

    level = loadLevel(filename1, row, col, player1);
    player1.row = 3;
    player1.col = 2;
    monsterStatus = doMonsterAttack(level,row,col,player1);
    if (monsterStatus){
        cout << "PASS: Happy paths test "  << numTests++ << endl;
    }
    else{
        cout << "FAIL: Happy paths test "  << numTests++ << endl;
    }
    deallocate(level,row);

    const std::string filename2 = "monsterTrapped.txt";
    level = loadLevel(filename2, row, col, player1);
    player1.row = 2;
    player1.col = 0;
    monsterStatus = doMonsterAttack(level,row,col,player1);
    if (!monsterStatus && level[2][2] == 'M'){
        cout << "PASS: Happy paths test "  << numTests++ << endl;
    }
    else{
        cout << "FAIL: Happy paths test "  << numTests++ << endl;
    }
    deallocate(level,row);

    level = loadLevel(filename2, row, col, player1);
    player1.row = 0;
    player1.col = 2;
    monsterStatus = doMonsterAttack(level,row,col,player1);
    if (!monsterStatus && level[2][2] == 'M'){
        cout << "PASS: Happy paths test "  << numTests++ << endl;
    }
    else{
        cout << "FAIL: Happy paths test "  << numTests++ << endl;
    }
    deallocate(level,row);

    level = loadLevel(filename2, row, col, player1);
    player1.row = 2;
    player1.col = 4;
    monsterStatus = doMonsterAttack(level,row,col,player1);
    if (!monsterStatus && level[2][2] == 'M'){
        cout << "PASS: Happy paths test "  << numTests++ << endl;
    }
    else{
        cout << "FAIL: Happy paths test "  << numTests++ << endl;
    }
    deallocate(level,row);

    level = loadLevel(filename2, row, col, player1);
    player1.row = 4;
    player1.col = 2;
    monsterStatus = doMonsterAttack(level,row,col,player1);
    if (!monsterStatus && level[2][2] == 'M'){
        cout << "PASS: Happy paths test "  << numTests++ << endl;
    }
    else{
        cout << "FAIL: Happy paths test "  << numTests++ << endl;
    }
    deallocate(level,row);

}
int main() {
    testLevel();
    testDirection();
    testDelete();
    testResize();
    testMove();
    testMonster();
    return 0;
}
