#ifndef PA2_GAMECONTROLLER_H
#define PA2_GAMECONTROLLER_H

#include "BlockFall.h"

using namespace std;

class GameController {
public:
    bool play(BlockFall &game, const string &commands_file); // Function that implements the gameplay
    void moveRight(int* y_position);
    void moveLeft(int* y_position);
    void moveDown(int* x_position);
    void moveUp(int* x_position);

    vector<vector<int>> writetoGrid(vector<vector<int>>grid,vector<vector<bool>> gameblock,int x_position,int y_position);
    vector<vector<int>> clearGrid(vector<vector<int>>grid,vector<vector<bool>> gameblock,int x_position,int y_position);
    bool collisionCheck(vector<vector<bool>> &block,vector<vector<int>> grid,int x_position,int y_position);
    void print_grid(std::vector<std::vector<int>> &grid);


    vector<vector<int>>gravityController( vector<vector<int>> grid);

    vector<vector<int>> clearRows(vector<vector<int>> grid,vector<int> fullRows);

    void print_block(const vector<std::vector<bool>> &block);

    bool isPowerUponGrid(vector<vector<int>> grid, vector<vector<bool>> gameblock);

    void clearFullGrid(BlockFall &game);

    vector<int> fullRowsNumbers(vector<vector<int>> grid);

    int onePointNumber(BlockFall &game);

    int blockOnePointNumber(vector<vector<bool>> block);
};


#endif //PA2_GAMECONTROLLER_H
