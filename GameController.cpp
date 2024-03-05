#include <fstream>
#include "GameController.h"
#include <iostream>

void GameController::moveRight(int* y_position) {
    (*y_position)++;
}
void GameController::moveLeft(int* y_position){
    (*y_position)--;
}
void GameController::moveDown(int* x_position){
    (*x_position)++;
}
void GameController::moveUp(int* x_position){
    (*x_position)--;
}
int GameController::blockOnePointNumber(vector<vector<bool>> block){
    int number = 0;
    for (int i = 0; i < block.size(); ++i) {
        for (int j = 0; j <block[0].size(); ++j) {
            if (block[i][j] == 1){
                number++;
            }
        }
    }
    return number;
}
int GameController::onePointNumber(BlockFall &game){
    int number = 0;
    for (int i = 0; i < game.grid.size(); ++i) {
        for (int j = 0; j < game.grid[0].size(); ++j) {
            if (game.grid[i][j] == 1){
                number++;
            }
        }
    }
    return  number;
}

void GameController::clearFullGrid(BlockFall &game){
    for (int i = 0; i < game.grid.size(); ++i) {
        for (int j = 0; j < game.grid[0].size(); ++j) {
            game.grid[i][j] = 0;
        }
    }
}
bool GameController:: isPowerUponGrid(vector<vector<int>>grid,vector<vector<bool>> gameblock){

    for (int i = 0; i < grid.size()-gameblock.size(); ++i) {
        for (int j = 0; j < grid[0].size()-gameblock[0].size(); ++j) {
            vector<vector<bool>> shape;
            for (int k = 0; k < gameblock.size(); ++k) {
                vector<bool> row;
                for (int l = 0; l < gameblock[0].size(); ++l) {
                    if(grid[i+k][j+l] == 1){
                        row.push_back(true);
                    }else{
                        row.push_back(false);
                    }
                }
                shape.push_back(row);
            }
            if(gameblock == shape){
                return true;
            }else{
                continue;
            }
        }
    }
    return false;
}
vector<vector<int>> GameController::writetoGrid(vector<vector<int>>grid,vector<vector<bool>> gameblock,int x_position,int y_position){
    for (int i = 0; i < gameblock.size(); ++i) {
        for (int j = 0; j < gameblock[0].size(); ++j) {
            if (grid[i+x_position][j+y_position] != 1){
                grid[i+x_position][j+y_position] = gameblock [i][j];
            }
        }
    }
    return grid;
}
vector<vector<int>> GameController::clearGrid(vector<vector<int>>grid,vector<vector<bool>> gameblock,int x_position,int y_position){
    for (int i = 0; i < gameblock.size(); ++i) {
        for (int j = 0; j < gameblock[0].size(); ++j) {
            grid[i+x_position][j+y_position] = 0;
        }
    }
    return grid;
}
bool GameController::collisionCheck(vector<vector<bool>> &block,vector<vector<int>> grid,int x_position,int y_position){

    for (int i = 0; i < block.size(); ++i) {
        for (int j = 0; j < block[0].size(); ++j) {
            if ((i + x_position < 0) || (i + x_position >= grid.size()) || (j + y_position < 0) || (j + y_position >= grid[0].size())) {
                return true;
            }
        }
    }
    for (int i = 0; i < block.size(); ++i) {
        for (int j = 0; j < block[0].size(); ++j) {
            if(block[i][j] == 1 && grid[i+x_position][j+y_position] == 1){
                return true;
            }
        }
    }
    return false;
}


void GameController::print_grid(std::vector<std::vector<int>> &grid) {
    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[0].size(); ++j) {
            std::cout << (grid[i][j] == 1 ?  1 : 0)<<"";
        }
        std::cout<<endl;

    }
}
vector<vector<int>> GameController::gravityController(vector<vector<int>> grid) {
    for (int j = 0; j < grid[0].size(); ++j) {
        int targetRow = grid.size() - 1;
        for (int i = grid.size() - 1; i >= 0; --i) {
            if (grid[i][j] == 1) {
                grid[targetRow][j] = 1;
                if (targetRow != i) {
                    grid[i][j] = 0;
                }
                --targetRow;
            }
        }
    }
    return grid;
}
vector<int> GameController::fullRowsNumbers(vector<vector<int>>grid) {
    vector<int> fullRows;
    for (int i = 0; i < grid.size(); ++i) {
        bool isRowFull = true;
        for (int j = 0; j < grid[0].size(); ++j) {
            if (grid[i][j] == 0) {
                isRowFull = false;
                break;
            }
        }
        if (isRowFull) {
            fullRows.push_back(i);
        }
    }
    return fullRows;
}
vector<vector<int>> GameController::clearRows(vector<vector<int>>grid,vector<int> fullRows){
    for (int i : fullRows) {
        grid.erase(grid.begin() + i);
        grid.insert(grid.begin(), std::vector<int>(grid[0].size(), 0));
    }
    return grid;
}
bool GameController::play(BlockFall& game, const string& commands_file){

    // TODO: Implement the gameplay here while reading the commands from the input file given as the 3rd command-line
    //       argument. The return value represents if the gameplay was successful or not: false if game over,
    //       true otherwise.

    Block* gameBlock = game.active_rotation;
    vector<vector<bool>> power_up_shape = game.power_up;


    std::ifstream inputFile(commands_file);
    if(!inputFile.is_open()){
        return false;
    }
    int x_position = 0;
    int y_position = 0;

    std::string command;
    while(inputFile >> command){

        std::cout<< command << std::endl;
        if (command == "PRINT_GRID"){
            game.grid = writetoGrid(game.grid,gameBlock->shape,x_position,y_position);
            print_grid(game.grid);
            cout<<"-----------------------------------"<<endl;
            game.grid = clearGrid(game.grid,gameBlock->shape,x_position,y_position);
        } else if (command == "ROTATE_RIGHT") {
            if (!collisionCheck(gameBlock->right_rotation->shape, game.grid, x_position, y_position)) {
                int rotatedWidth = gameBlock->right_rotation->shape[0].size();
                if ((y_position + rotatedWidth)<= game.grid[0].size()) {
                    gameBlock = gameBlock->right_rotation;
                }
            }
        } else if (command == "ROTATE_LEFT") {
            if (!collisionCheck(gameBlock->left_rotation->shape, game.grid, x_position, y_position)) {
                int rotatedWidth = gameBlock->left_rotation->shape[0].size();
                if ((y_position + rotatedWidth) <= game.grid[0].size()) {
                    gameBlock = gameBlock->left_rotation;
                }
            }
        }
        else if (command == "MOVE_RIGHT") {
            if(!collisionCheck(gameBlock -> shape,game.grid,x_position,y_position)){
               if(y_position != game.grid[0].size()-gameBlock->shape[0].size()){
                    moveRight(&y_position);
               }
            }else{
                moveLeft(&y_position);
            }

        } else if (command == "MOVE_LEFT") {
            if(!collisionCheck(gameBlock -> shape,game.grid,x_position,y_position)){
                if(y_position != 0){
                    moveLeft(&y_position);
                }
            }else{
                moveRight(&y_position);
            }

        } else if (command == "DROP") {
            while(!collisionCheck(gameBlock->shape,game.grid,x_position,y_position)){
                moveDown(&x_position);
            }
            if(x_position != 0){
                moveUp(&x_position);
            }
            game.grid = writetoGrid(game.grid,gameBlock->shape,x_position,y_position);
            if(game.gravity_mode_on){
                game.grid = gravityController(game.grid);
            }
            game.current_score += x_position* blockOnePointNumber(gameBlock->shape);
            x_position = 0;
            y_position = 0;
            gameBlock = gameBlock -> next_block;
            print_grid(game.grid);

            if(isPowerUponGrid(game.grid,game.power_up)){
                game.current_score = onePointNumber(game)+1000;
                clearFullGrid(game);
            }
            vector<int> fullRows = fullRowsNumbers(game.grid);
            if(fullRows.size() > 0){
                game.grid = clearRows(game.grid,fullRows);
                game.current_score += game.grid[0].size();
            }

            std::cout<< game.current_score << endl;

        } else if (command == "GRAVITY_SWITCH") {
            if(game.gravity_mode_on){
                game.gravity_mode_on = false;
            }else{
                game.gravity_mode_on = true;
                game.grid = gravityController(game.grid);
                if(isPowerUponGrid(game.grid,game.power_up)){
                    game.current_score = onePointNumber(game)+1000;
                    clearFullGrid(game);
                }
                vector<int> fullRows = fullRowsNumbers(game.grid);
                if(fullRows.size() > 0){
                    game.grid = clearRows(game.grid,fullRows);
                    game.current_score += game.grid[0].size();
                }
            }

        } else {
            std::cout<< "Unknown command: " << command << std::endl;
        }

    }
    game.active_rotation = gameBlock;


    inputFile.close();
    return true;
}



