#include <iostream>
#include <fstream>
#include <string>
#include "logic.h"
#include <sstream>

using std::cout, std::endl, std::ifstream, std::string;

/**
 * TODO: Student implement this function
 * Load representation of the dungeon level from file into the 2D map.
 * Calls createMap to allocate the 2D array.
 * @param   fileName    File name of dungeon level.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object by reference to set starting position.
 * @return  pointer to 2D dynamic array representation of dungeon map with player's location., or nullptr if loading fails for any reason
 * @updates  maxRow, maxCol, player
 */
char** loadLevel(const string& fileName, int& maxRow, int& maxCol, Player& player) {
    std::ifstream inFS;
    inFS.open(fileName);
    if (!inFS.is_open()){
        return nullptr;
    }

    char** map;
    int row;
    int col;

    std::string linestring;
    std::istringstream inSS;
    getline(inFS, linestring);
    inSS.str(linestring);
    inSS >> row;
    if (inSS.fail()){
        return nullptr;
    }
    inSS >> col;
    if (inSS.fail()){
        return nullptr;
    }
    

    if (row < 1 || col < 1){
        return nullptr;
    }
    if (row >= INT32_MAX/col){
        return nullptr;
    }

    maxRow = row;
    maxCol = col;
    inSS.clear();


    getline(inFS, linestring);
    inSS.str(linestring);
    int playerRow;
    int playerCol;
    inSS >> playerRow;
    if (inSS.fail()){
        return nullptr;
    }
    inSS >> playerCol;
    if (inSS.fail()){
        return nullptr;
    }

    if (playerRow < 0 || playerCol < 0 || playerRow >= maxRow || playerCol >= maxCol){
        return nullptr;
    }

    player.row = playerRow;
    player.col = playerCol;
   

    map = createMap(maxRow,maxCol);
    inSS.clear();
    getline(inFS, linestring);
    inSS.str(linestring);
    int r = 0;
    int c = 0;
    bool noExit = true;
    char tile;
    while (!inFS.fail()){
        while(inSS.get(tile)){
            if (!isspace(tile)){
                map[r][c] = tile;
                if (tile != TILE_AMULET && tile != TILE_DOOR && tile != TILE_EXIT && tile != TILE_MONSTER && tile != TILE_OPEN && tile != TILE_PILLAR && tile != TILE_TREASURE){
                    deleteMap(map,maxRow);
                    return nullptr;
                }
                if (tile == TILE_EXIT || tile == TILE_DOOR){
                    noExit = false;
                }
                c++;
                if (c == maxCol){
                    c = 0;
                    r++;
                }
                if (r == maxRow){
                    
                    if(inSS.get(tile)){
                        if(!isspace(tile)){
                            deleteMap(map,maxRow);
                            inFS.close();
                            return nullptr;
                        }
                    }
                    inFS.close();
                    break;
                }
            }
        }
        
        inSS.clear();
        getline(inFS, linestring);
        inSS.str(linestring);
    }
    
    
    if (row != maxRow){
        deleteMap(map,maxRow);
        return nullptr;
    }

    if (noExit){
        deleteMap(map, maxRow);
        return nullptr;
    }

    map[player.row][player.col] = 'o';
    inFS.close();
    return map;
}

/**
 * TODO: Student implement this function
 * Translate the character direction input by the user into row or column change.
 * That is, updates the nextRow or nextCol according to the player's movement direction.
 * @param   input       Character input by the user which translates to a direction.
 * @param   nextRow     Player's next row on the dungeon map (up/down).
 * @param   nextCol     Player's next column on dungeon map (left/right).
 * @updates  nextRow, nextCol
 */
void getDirection(char input, int& nextRow, int& nextCol) {
    if (input == MOVE_UP){
        nextRow--;
    }
    else if (input == MOVE_DOWN){
        nextRow++;
    }
    else if (input == MOVE_LEFT){
        nextCol--;
    }
    else if (input == MOVE_RIGHT){
        nextCol++;
    }
}

/**
 * TODO: [suggested] Student implement this function
 * Allocate the 2D map array.
 * Initialize each cell to TILE_OPEN.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @return  2D map array for the dungeon level, holds char type.
 */
char** createMap(int maxRow, int maxCol) {
    char** map = new char *[maxRow];
    for (int i = 0; i < maxRow; ++i){
        map[i] = new char[maxCol];
    }

    for (int i = 0; i < maxRow; ++i){
        for (int j = 0; j < maxCol; ++j){
            map[i][j] = TILE_OPEN;
        }
    }
    return map;
}

/**
 * TODO: Student implement this function
 * Deallocates the 2D map array.
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @return None
 * @update map, maxRow
 */
void deleteMap(char**& map, int& maxRow) {
    if (map != nullptr){
        for(int i = 0; i < maxRow; ++i) {
            delete[] map[i];   
        }
        //Free the array of pointers
        delete[] map;
        map = nullptr;
        maxRow = 0;
    }
}

/**
 * TODO: Student implement this function
 * Resize the 2D map by doubling both dimensions.
 * Copy the current map contents to the right, diagonal down, and below.
 * Do not duplicate the player, and remember to avoid memory leaks!
 * You can use the STATUS constants defined in logic.h to help!
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height), to be doubled.
 * @param   maxCol      Number of columns in the dungeon table (aka width), to be doubled.
 * @return  pointer to a dynamically-allocated 2D array (map) that has twice as many columns and rows in size.
 * @update maxRow, maxCol
 */
char** resizeMap(char** map, int& maxRow, int& maxCol) {
    int newRow = maxRow * 2;
    int newCol = maxCol * 2;
    char** newMap = createMap(newRow, newCol);

    // top left quadrant
    for (int i = 0; i < maxRow; ++i){
        for (int j = 0; j < maxCol; ++j){
            newMap[i][j] = map[i][j];
        }
    }

    // bottom left quadrant
    for (int i = maxRow; i < maxRow*2; ++i){
        for (int j = 0; j < maxCol; ++j){
            newMap[i][j] = map[i-maxRow][j];
            if (map[i-maxRow][j] == 'o'){
                newMap[i][j] = '-';
            }
        }
    }

    // top right quadrant
    for (int i = 0; i < maxRow; ++i){
        for (int j = maxCol; j < maxCol*2; ++j){
            newMap[i][j] = map[i][j-maxCol];
            if (map[i][j-maxCol] == 'o'){
                newMap[i][j] = '-';
            }
        }
    }

    // bottom right quadrant
    for (int i = maxRow; i < maxRow*2; ++i){
        for (int j = maxCol; j < maxCol*2; ++j){
            newMap[i][j] = map[i-maxRow][j-maxCol];
            if (map[i-maxRow][j-maxCol] == 'o'){
                newMap[i][j] = '-';
            }
        }
    }

    deleteMap(map, maxRow);
    maxRow = newRow;
    maxCol = newCol;
    

    return newMap;
}

/**
 * TODO: Student implement this function
 * Checks if the player can move in the specified direction and performs the move if so.
 * Cannot move out of bounds or onto TILE_PILLAR or TILE_MONSTER.
 * Cannot move onto TILE_EXIT without at least one treasure. 
 * If TILE_TREASURE, increment treasure by 1.
 * Remember to update the map tile that the player moves onto and return the appropriate status.
 * You can use the STATUS constants defined in logic.h to help!
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object to by reference to see current location.
 * @param   nextRow     Player's next row on the dungeon map (up/down).
 * @param   nextCol     Player's next column on dungeon map (left/right).
 * @return  Player's movement status after updating player's position.
 * @update map contents, player
 */
int doPlayerMove(char** map, int maxRow, int maxCol, Player& player, int nextRow, int nextCol) {
    
    if (nextRow < 0 || nextRow >= maxRow || nextCol < 0 || nextCol >= maxCol){
        return STATUS_STAY;
    }
    char position = map[nextRow][nextCol];
    if (position == TILE_PILLAR || position == TILE_MONSTER){
        return STATUS_STAY;
    }
    else if(position == TILE_OPEN){
        map[player.row][player.col] = '-';
        player.row = nextRow;
        player.col = nextCol;
        map[player.row][player.col] = 'o';
        return STATUS_MOVE;
    }
    else if (position == TILE_TREASURE){
        map[player.row][player.col] = '-';
        player.row = nextRow;
        player.col = nextCol;
        player.treasure++;
        map[player.row][player.col] = 'o';
        return STATUS_TREASURE;
    }
    else if (position == TILE_DOOR){
        map[player.row][player.col] = '-';
        player.row = nextRow;
        player.col = nextCol;
        map[nextRow][nextCol] = 'o';
        return STATUS_LEAVE;
    }
    else if (position == TILE_EXIT){
        if (player.treasure >= 1){
            map[player.row][player.col] = '-';
            player.row = nextRow;
            player.col = nextCol;
            map[nextRow][nextCol] = 'o';
            return STATUS_ESCAPE;
        }
        else{
            return STATUS_STAY;
        }
    }
    else if (position == TILE_AMULET){
        map[player.row][player.col] = '-';
        player.row = nextRow;
        player.col = nextCol;
        map[player.row][player.col] = 'o';
        return STATUS_AMULET;
    }
    
    return 0;
}

/**
 * TODO: Student implement this function
 * Update monster locations:
 * We check up, down, left, right from the current player position.
 * If we see an obstacle, there is no line of sight in that direction, and the monster does not move.
 * If we see a monster before an obstacle, the monster moves one tile toward the player.
 * We should update the map as the monster moves.
 * At the end, we check if a monster has moved onto the player's tile.
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object by reference for current location.
 * @return  Boolean value indicating player status: true if monster reaches the player, false if not.
 * @update map contents
 */
bool doMonsterAttack(char** map, int maxRow, int maxCol, const Player& player) {
    int monsterX;
    int monsterY;
    int playerX = player.row;
    int playerY = player.col;
    bool monsterStatus = false;
    
        // look up
    for (int i = playerX-1; i >= 0; --i){
        if (map[i][playerY] == '+'){
            break;
        }
        if (map[i][playerY] == 'M'){
            map[i][playerY] = '-';
            map[i+1][playerY] = 'M';
            monsterX = i+1;
            monsterY = playerY;
            if ((monsterX == playerX) && (monsterY == playerY)){
                monsterStatus = true;
            }
        }
    }
    

    // look down
    for (int i = playerX+1; i < maxRow; ++i){

        if (map[i][playerY] == '+'){
            break;
        }
        if (map[i][playerY] == 'M'){
            map[i][playerY] = '-';
            map[i-1][playerY] = 'M';
            monsterX = i-1;
            monsterY = playerY;
            if ((monsterX == playerX) && (monsterY == playerY)){
                monsterStatus = true;
            }
        }
    }
    

    // look left
    for (int i = playerY-1; i >= 0; --i){
    
        if (map[playerX][i] == '+'){
            break;
        }
        if (map[playerX][i] == 'M'){
            map[playerX][i] = '-';
            map[playerX][i+1] = 'M';
            monsterX = playerX;
            monsterY = i+1;
            if ((monsterX == playerX) && (monsterY == playerY)){
                monsterStatus = true;
            }
        }
    }

    // look right
    for (int i = playerY+1; i < maxCol; ++i){
       
        if (map[playerX][i] == '+'){
            break;
        }
        if (map[playerX][i] == 'M'){
            map[playerX][i] = '-';
            map[playerX][i-1] = 'M';
            monsterX = playerX;
            monsterY = i-1;
            if ((monsterX == playerX) && (monsterY == playerY)){
                monsterStatus = true;
            }
        }
    }
    
    return monsterStatus;
}
