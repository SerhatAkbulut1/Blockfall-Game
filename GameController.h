#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <vector>
#include <string>
#include "BlockFall.h"

class GameController {
public:
    void moveRight(int& y_position);
    void moveLeft(int& y_position);
    void moveDown(int& x_position);
    void moveUp(int& x_position);
    int countBlockPoints(const std::vector<std::vector<bool>>& block);
    int countGridPoints(const std::vector<std::vector<int>>& grid);
    void clearGrid(std::vector<std::vector<int>>& grid);
    bool checkPowerUp(const std::vector<std::vector<int>>& grid, const std::vector<std::vector<bool>>& power_up);
    std::vector<std::vector<int>> applyBlockToGrid(std::vector<std::vector<int>> grid, const std::vector<std::vector<bool>>& block, int x_position, int y_position);
    std::vector<std::vector<int>> removeBlockFromGrid(std::vector<std::vector<int>> grid, const std::vector<std::vector<bool>>& block, int x_position, int y_position);
    bool checkCollision(const std::vector<std::vector<bool>>& block, const std::vector<std::vector<int>>& grid, int x_position, int y_position);
    void printGrid(const std::vector<std::vector<int>>& grid);
    std::vector<std::vector<int>> applyGravity(std::vector<std::vector<int>> grid);
    std::vector<int> findFullRows(const std::vector<std::vector<int>>& grid);
    std::vector<std::vector<int>> clearRows(std::vector<std::vector<int>>& grid, const std::vector<int>& full_rows);
    bool play(BlockFall& game, const std::string& commands_file);
};

#endif // GAMECONTROLLER_H
