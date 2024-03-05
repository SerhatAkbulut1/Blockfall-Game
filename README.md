# BlockFall Game

## Overview:
BlockFall is a console-based tile-matching video game that challenges players with strategic gameplay and dynamic memory management. Developed as a programming assignment for Hacettepe Computer Engineering's BBM203 Software Practicum I course in Fall 2023, BlockFall draws inspiration from classic block-matching games like Tetris while introducing unique mechanics and complexities. Developed by students from HUBBM and HUAIN, prestigious computer engineering programs, BlockFall aims to provide both captivating entertainment and educational value in C++ programming.

## Getting Started:
### Prerequisites:
- C++ compiler
- Input files: grid.dat, blocks.dat, commands.dat
- Command line arguments: grid file, blocks file, commands file, gravity mode, leaderboard file, player name
### Initialization:
BlockFall initializes by parsing input data from provided files and setting up the game grid, blocks, and commands. Effective dynamic memory allocation is crucial for managing game elements.

## Key Features:
BlockFall offers several essential gameplay functionalities:
- **Reading and Processing Commands:** Real-time interpretation of commands to facilitate gameplay conditions.
- **Block Movements and Collision Detection:** Handling block movements, rotations, and collisions with the game grid.
- **Clearance and Scoring:** Mechanisms for clearing rows, detecting power-ups, and awarding points.
- **Leaderboard Management:** Tracking high scores, maintaining a leaderboard with top player achievements.

## Implementation Guidelines:
To implement BlockFall effectively, the following classes are utilized:
- **Block Class:** Represents individual blocks in the game, featuring operators for shape comparison.
- **BlockFall Class:** Manages main game logic and structure, including dynamic memory management and initialization.
- **GameController Class:** Implements gameplay mechanics by interpreting commands from input files.
- **LeaderboardEntry Class:** Represents a single entry in the game's leaderboard, featuring score, timestamp, and player name.
- **Leaderboard Class:** Manages the game's leaderboard, including insertion, reading, writing, and printing operations.
