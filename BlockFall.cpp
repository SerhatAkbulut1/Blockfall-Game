#include <fstream>
#include <sstream>
#include <iostream>
#include "BlockFall.h"


BlockFall::BlockFall(string grid_file_name, string blocks_file_name, bool gravity_mode_on, const string &leaderboard_file_name, const string &player_name) : gravity_mode_on(
        gravity_mode_on), leaderboard_file_name(leaderboard_file_name), player_name(player_name) {
    initialize_grid(grid_file_name);
    read_blocks(blocks_file_name);
    leaderboard.read_from_file(leaderboard_file_name);
}

vector<vector<bool>>BlockFall::right_rotation(const vector<vector<bool>> &matrix) {
    int row = matrix.size();
    int col = matrix[0].size();

    vector<vector<bool>> temp (col,vector<bool>(row,0));
    for(int i = 0 ; i < row ; ++i ){
        for(int j = 0 ; j < col ; ++j ){
            temp[j][row - 1 - i] = matrix[i][j];
        }
    }
    return temp;
}

void BlockFall::print_grid(const std::vector<std::vector<int>> &grid) {
    for (const auto &row : grid) {
        for (int value : row) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }
}
void BlockFall ::print_block(const std::vector<std::vector<bool>> &block) {
    for (const auto &row : block) {
        for (int value : row) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }
}

void BlockFall::read_blocks(const string &input_file) {
    // TODO: Read the blocks from the input file and initialize "initial_block" and "active_rotation" member variables
    std::string file_path = "sampleIO/1_big_grid_gravity_switch/blocks.dat";
    std::ifstream file(input_file);

    if (!file.is_open()) {
        return ;
    }

    vector<vector<vector<bool>>> Shapes;
    vector<vector<bool>> shape;
    string line;
    bool inBlock = false;
    int number = 0;

    while (getline(file, line)) {

        istringstream iss(line);
        int value;
        vector<bool> row;

        if(line == ""){
            continue;
        }

        if (line[0] == '[') {
            inBlock = true;
        }

        if (inBlock) {

            if (line[line.size() - 1] == ']') {
                inBlock = false;
            }

            for (int i = 0; i < line.size() ; ++i) {
                value =static_cast<int>(line.at(i));
                if(value == 49){
                    row.push_back(true);
                }
                else if (value ==48){
                    row.push_back(false);
                }
                else{}
            }

        }
        shape.push_back(row);

        if(!inBlock){
            Shapes.push_back(shape);
            shape.erase(shape.begin(),shape.end());
            number++;
        }

    }

    // TODO: Initialize the "power_up" member variable as the last shape from the input file (do not add it to the linked list!)
    power_up = Shapes[Shapes.size()-1];
    Shapes.erase(Shapes.end());

    // TODO: For every shape, generate its rotations and properly implement the multilevel linked list structure
    //       that represents the game blocks, as explained in the PA instructions.



    for(int i = Shapes.size()-1; i >= 0; i--){
        vector<vector<vector<bool>>> rotatedBLocks;
        shape = Shapes[i];
        rotatedBLocks.push_back(shape);

        for(int x = 0 ; x < 3 ; ++x){
            shape = right_rotation(shape);
            rotatedBLocks.push_back(shape);
        }

        if(rotatedBLocks[0] == rotatedBLocks [1]){
            rotatedBLocks.erase(rotatedBLocks.begin() + 1, rotatedBLocks.end());
        }else if(rotatedBLocks[0] == rotatedBLocks [2]){
            rotatedBLocks.erase(rotatedBLocks.begin() + 2, rotatedBLocks.end());
        }

        Block * start = nullptr;
        for(int j  = 0; j < rotatedBLocks.size(); ++j){
            if(start == nullptr){
                Block* newBlock = new Block;
                newBlock-> shape = Shapes[i];
                newBlock ->right_rotation = newBlock;
                newBlock ->left_rotation = newBlock;
                start = newBlock;
                if(i == Shapes.size() -1){
                    newBlock->next_block = nullptr;
                }else{
                    newBlock -> next_block = initial_block;
                }
                initial_block = newBlock;
                active_rotation = initial_block;
            }else{
                Block* newBlock = new Block;
                newBlock -> shape = rotatedBLocks[j];
                Block* last = initial_block -> left_rotation;
                newBlock -> right_rotation = initial_block;
                newBlock -> left_rotation = last;
                last -> right_rotation = newBlock;
                start -> left_rotation = newBlock;
                if(i == Shapes.size() -1){
                    newBlock->next_block = nullptr;
                }else{
                    newBlock -> next_block = initial_block;
                }
            }
        }
    }
    file.close();

}

void BlockFall::initialize_grid(const string &input_file) {
    std::ifstream file(input_file);
    if(!file.is_open()){
        return;
    }

    // TODO: Initialize "rows" and "cols" member variables
    int rows = 0;
    int cols = 0;

    // TODO: Initialize "grid" member variable using the command-line argument 1 in main
   // vector<vector<int> > grid;

    std::string line;
    while(getline(file,line)){
        istringstream iss(line);
        int Value ;
        vector<int> row;

        while(iss >> Value){
            row.push_back(Value);   
            cols++;
        }
        if (!row.empty()) {
            grid.push_back(row);
            rows++;
        }
    }
    file.close();

}

BlockFall::~BlockFall() {

}

