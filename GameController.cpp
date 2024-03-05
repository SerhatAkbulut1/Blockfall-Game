#include <fstream>
#include <iostream>
#include "GameController.h"

void GameController::moveRight(int& y_position) {
    y_position++;
}

void GameController::moveLeft(int& y_position) {
    y_position--;
}

void GameController::moveDown(int& x_position) {
    x_position++;
}

void GameController::moveUp(int& x_position) {
    x_position--;
}

int GameController::countBlockPoints(const std::vector<std::vector<bool>>& block) {
    int points = 0;
    for (const auto& row : block) {
        for (bool cell : row) {
            if (cell) {
                points++;
            }
        }
    }
    return points;
}

int GameController::countGridPoints(const std::vector<std::vector<int>>& grid) {
    int points = 0;
    for (const auto& row : grid) {
        for (int cell : row) {
            if (cell == 1) {
                points++;
            }
        }
    }
    return points;
}

void GameController::clearGrid(std::vector<std::vector<int>>& grid) {
    for (auto& row : grid) {
        for (int& cell : row) {
            cell = 0;
        }
    }
}

bool GameController::checkPowerUp(const std::vector<std::vector<int>>& grid, const std::vector<std::vector<bool>>& power_up) {
    for (int i = 0; i <= grid.size() - power_up.size(); ++i) {
        for (int j = 0; j <= grid[0].size() - power_up[0].size(); ++j) {
            bool match = true;
            for (int x = 0; x < power_up.size(); ++x) {
                for (int y = 0; y < power_up[0].size(); ++y) {
                    if (power_up[x][y] && grid[i + x][j + y] != 1) {
                        match = false;
                        break;
                    }
                }
                if (!match) {
                    break;
                }
            }
            if (match) {
                return true;
            }
        }
    }
    return false;
}

std::vector<std::vector<int>> GameController::applyBlockToGrid(std::vector<std::vector<int>> grid, const std::vector<std::vector<bool>>& block, int x_position, int y_position) {
    for (int i = 0; i < block.size(); ++i) {
        for (int j = 0; j < block[0].size(); ++j) {
            if (block[i][j]) {
                grid[x_position + i][y_position + j] = 1;
            }
        }
    }
    return grid;
}

std::vector<std::vector<int>> GameController::removeBlockFromGrid(std::vector<std::vector<int>> grid, const std::vector<std::vector<bool>>& block, int x_position, int y_position) {
    for (int i = 0; i < block.size(); ++i) {
        for (int j = 0; j < block[0].size(); ++j) {
            if (block[i][j]) {
                grid[x_position + i][y_position + j] = 0;
            }
        }
    }
    return grid;
}

bool GameController::checkCollision(const std::vector<std::vector<bool>>& block, const std::vector<std::vector<int>>& grid, int x_position, int y_position) {
    for (int i = 0; i < block.size(); ++i) {
        for (int j = 0; j < block[0].size(); ++j) {
            if (block[i][j]) {
                int new_x = x_position + i;
                int new_y = y_position + j;
                if (new_x < 0 || new_x >= grid.size() || new_y < 0 || new_y >= grid[0].size() || grid[new_x][new_y] == 1) {
                    return true;
                }
            }
        }
    }
    return false;
}

void GameController::printGrid(const std::vector<std::vector<int>>& grid) {
    for (const auto& row : grid) {
        for (int cell : row) {
            std::cout << (cell == 1 ? 'X' : '.') << ' ';
        }
        std::cout << std::endl;
    }
}

std::vector<std::vector<int>> GameController::applyGravity(std::vector<std::vector<int>> grid) {
    for (int j = 0; j < grid[0].size(); ++j) {
        int write_index = grid.size() - 1;
        for (int i = grid.size() - 1; i >= 0; --i) {
            if (grid[i][j] == 1) {
                grid[write_index--][j] = 1;
            }
        }
        for (int i = write_index; i >= 0; --i) {
            grid[i][j] = 0;
        }
    }
    return grid;
}

std::vector<int> GameController::findFullRows(const std::vector<std::vector<int>>& grid) {
    std::vector<int> full_rows;
    for (int i = 0; i < grid.size(); ++i) {
        bool full = true;
        for (int j = 0; j < grid[0].size(); ++j) {
            if (grid[i][j] != 1) {
                full = false;
                break;
            }
        }
        if (full) {
            full_rows.push_back(i);
        }
    }
    return full_rows;
}

std::vector<std::vector<int>> GameController::clearRows(std::vector<std::vector<int>>& grid, const std::vector<int>& full_rows) {
    for (int row_index : full_rows) {
        grid.erase(grid.begin() + row_index);
        grid.insert(grid.begin(), std::vector<int>(grid[0].size(), 0));
    }
    return grid;
}

bool GameController::play(BlockFall& game, const std::string& commands_file) {
    std::ifstream input_file(commands_file);
    if (!input_file.is_open()) {
        return false;
    }

    int x_position = 0;
    int y_position = 0;

    std::string command;
    while (input_file >> command) {
        if (command == "PRINT_GRID") {
            printGrid(game.grid);
        } else if (command == "ROTATE_RIGHT") {
            if (!checkCollision(game.active_rotation->right_rotation->shape, game.grid, x_position, y_position)) {
                game.active_rotation = game.active_rotation->right_rotation;
            }
        } else if (command == "ROTATE_LEFT") {
            if (!checkCollision(game.active_rotation->left_rotation->shape, game.grid, x_position, y_position)) {
                game.active_rotation = game.active_rotation->left_rotation;
            }
        } else if (command == "MOVE_RIGHT") {
            if (!checkCollision(game.active_rotation->shape, game.grid, x_position, y_position + 1)) {
                moveRight(y_position);
            }
        } else if (command == "MOVE_LEFT") {
            if (!checkCollision(game.active_rotation->shape, game.grid, x_position, y_position - 1)) {
                moveLeft(y_position);
            }
        } else if (command == "DROP") {
            while (!checkCollision(game.active_rotation->shape, game.grid, x_position + 1, y_position)) {
                moveDown(x_position);
            }
            game.grid = applyBlockToGrid(game.grid, game.active_rotation->shape, x_position, y_position);
            if (game.gravity_mode_on) {
                game.grid = applyGravity(game.grid);
            }
            game.current_score += x_position * countBlockPoints(game.active_rotation->shape);

            if (checkPowerUp(game.grid, game.power_up)) {
                game.current_score += 1000;
                clearGrid(game.grid);
            }
            std::vector<int> full_rows = findFullRows(game.grid);
            if (!full_rows.empty()) {
                game.grid = clearRows(game.grid, full_rows);
                game.current_score += full_rows.size() * game.grid[0].size(); // Each cleared row gives points equal to the width of the grid
            }

            std::cout << "Current Score: " << game.current_score << std::endl;
        } else if (command == "GRAVITY_SWITCH") {
            game.gravity_mode_on = !game.gravity_mode_on;
            if (game.gravity_mode_on) {
                game.grid = applyGravity(game.grid);
                if (checkPowerUp(game.grid, game.power_up)) {
                    game.current_score += 1000;
                    clearGrid(game.grid);
                }
                std::vector<int> full_rows = findFullRows(game.grid);
                if (!full_rows.empty()) {
                    game.grid = clearRows(game.grid, full_rows);
                    game.current_score += full_rows.size() * game.grid[0].size(); // Each cleared row gives points equal to the width of the grid
                }
            }
        } else {
            std::cout << "Unknown command: " << command << std::endl;
        }
    }

    input_file.close();
    return true;
}
