# Minesweeper Project

A console-based implementation of the classic Minesweeper game written in C++.

  

## Overview

This project is a fully-featured console implementation of the classic Minesweeper game with user account management, multiple difficulty levels, performance tracking, and a leaderboard system. The game employs a console-based user interface with colored text and Unicode characters to create an intuitive and visually appealing experience.

  

## Features

- **Classic Gameplay**: Reveal cells, flag potential mines, and clear the board without hitting any mines.

- **Multiple Difficulty Levels**:

  - Easy (9x9 board with 10 mines)

  - Medium (14x14 board with 40 mines)

  - Hard (20x20 board with 99 mines)

- **User Account System**: Create accounts and track your performance across games.

- **Leaderboard System**: Compare your performance with other players.

- **Visual Interface**: Colored text and Unicode characters for an enhanced console experience.

- **First-Move Safety**: Your first move is always guaranteed to be safe.

  

## Requirements

- Windows operating system (uses Windows Console API)

- C++ compiler with C++11 support

- Console that supports UTF-8 characters

  

## How to Play

1. Create an account or log in with existing credentials.

2. Select a difficulty level.

3. Use the following controls:

   - **WASD**: Move cursor

   - **F**: Toggle flag on a cell

   - **Enter**: Reveal a cell

   - **Esc**: Exit the game

  

## Game Rules

- Reveal all cells that don't contain mines to win.

- Numbers indicate how many mines are adjacent to that cell.

- Use flags to mark cells you suspect contain mines.

- If you reveal a cell with a mine, you lose.

  

## Game Interface

The game displays a grid of cells with a border made of Unicode box-drawing characters. Each cell can be in one of the following states:

- **?**: Unrevealed cell

- **F**: Flagged cell (colored)

- **(space)**: Revealed empty cell

- **1-7**: Number of adjacent mines (colored)

- **#**: Revealed mine (when game over)

  

## Data Storage

The game stores user accounts and game statistics in text files:

- User accounts: `USERS DATA FOLDER/UDF.txt`

- Easy mode statistics: `USERS DATA FOLDER/easyPlayers.txt`

- Medium mode statistics: `USERS DATA FOLDER/mediumPlayers.txt`

- Hard mode statistics: `USERS DATA FOLDER/hardPlayers.txt`

  

## Implementation Details

The game is implemented in a single C++ source file (`maingame.cpp`) with approximately 1,350 lines of code. It uses:

- Standard C++ libraries

- Windows API for console manipulation

- File I/O for data persistence

- Console input handling

- Timing functions for performance tracking

  

## Project Structure

The project follows a monolithic architecture with all functionality contained in a single source file. The main components include:

- **Game Architecture**: Overall structure and flow control

- **Game Logic**: Core mechanics (board initialization, mine placement, cell revelation)

- **User Interface**: Visual presentation and input handling

- **User Authentication**: Account management

- **Data Management**: Persistence of game data

- **Leaderboard System**: Performance tracking and display

  
# Minesweeper Project System and Setup Guide


## 1. System Requirements

The Minesweeper game is designed to run on Windows systems with the following requirements:

  

- **Windows Operating System**

- **C++ Compiler** (e.g., MinGW, Visual C++)

- **50MB Free Disk Space**

- **Basic Keyboard** for gameplay controls

  

## 2. Directory Structure

Before running the game, ensure the following directory structure is set up to store game data, guide information, logos, and user data:

  

**Root Directory**:

- `maingame.cpp`

- `maingame.exe`

- **GUIDE/**: Contains game guide pages

  - `MineSweeperGuidePage1.txt`

  - `MineSweeperGuidePage2.txt`

  - `MineSweeperGuidePage3.txt`

- **LOGOS/**: Contains ASCII art files

  - `flag.txt`

  - `gojo.txt`

- **USERS DATA FOLDER/**: Stores user account data and game statistics

  - `UDF.txt`

  - `easyPlayers.txt`

  - `mediumPlayers.txt`

  - `hardPlayers.txt`

- **CLEAR DATA/**: Contains data reset information

  - `clearDataSection.txt`

  

**Sources**: maingame.cpp:728-735, 750-757, 774-781, 979-989, 1332-1340; .gitignore:1-7

  

## 3. Compilation Instructions

The game consists of a single C++ source file (`maingame.cpp`) that needs to be compiled to create an executable.

  

### 3.1 Using MinGW G++

```bash

g++ maingame.cpp -o maingame.exe -std=c++11

```

  

### 3.2 Using Visual Studio Command Line

```bash

cl /EHsc maingame.cpp /Fe:maingame.exe

```

  

### Required Libraries

- `iostream`

- `cstdlib`

- `time.h`

- `windows.h`

- `fstream`

- `conio.h`

- `stdio.h`

- `random`

- `string`

- `chrono`

  

## 4. Data Files Setup

The game requires specific text files to function properly. Create the following:

  

### 4.1 Guide Files (in `GUIDE/` directory)

- `MineSweeperGuidePage1.txt`: First page of the game guide

- `MineSweeperGuidePage2.txt`: Second page of the game guide

- `MineSweeperGuidePage3.txt`: Third page of the game guide

  

### 4.2 Logo Files (in `LOGOS/` directory)

- `flag.txt`: ASCII art for the flag displayed in the main menu

- `gojo.txt`: ASCII art displayed during exit

  

### 4.3 Data Files (in `CLEAR DATA/` directory)

- `clearDataSection.txt`: Text displayed in the data clear section


  

## 5. First-Time Execution

When running the game for the first time, the program automatically creates the necessary data files:

  

- `USERS DATA FOLDER/UDF.txt`: Stores user login credentials

- `USERS DATA FOLDER/easyPlayers.txt`: Stores statistics for easy mode

- `USERS DATA FOLDER/mediumPlayers.txt`: Stores statistics for medium mode

- `USERS DATA FOLDER/hardPlayers.txt`: Stores statistics for hard mode

  

### Execution Flow

1. Launch application (`maingame.exe`)

2. Check if `UDF.txt` exists

   - **If not found**:

     - Create `UDF.txt`

     - Create `easyPlayers.txt`

     - Create `mediumPlayers.txt`

     - Create `hardPlayers.txt`

   - **If files exist**:

     - Load user data

     - Load player statistics

3. Display main menu


  

## 6. User Account Setup

To play the game, create a user account as follows:

  

1. Run `maingame.exe`

2. Select `[2] CREATE AN ACCOUNT` from the main menu

3. Enter a unique username

4. Create a password (minimum 8 characters)

5. Account created, return to main menu

6. Select `[1] NEW GAME`

7. Login with credentials

8. Select difficulty

9. Begin game


  

## 7. Game Configuration

The game offers several difficulty levels:

  

|    Difficulty    |    Board Size    |    Number of Mines    |

====================================

|    Easy   |    9x9   |   10   |

|    Medium   |    14x14   |    40   |

|    Hard   |    20x20   |    99   |

|    Custom    |    NxN (9-40)    |    M (10 to N²-1)    |

  

The difficulty setting affects:

- The size of the game board

- The number of mines placed

- The challenge level

- The leaderboard category for your score

  

  

## 8. Data Management

The game automatically saves user data and game statistics to the following files:

- User accounts: `USERS DATA FOLDER/UDF.txt`

- Game statistics:

  - `USERS DATA FOLDER/easyPlayers.txt`

  - `USERS DATA FOLDER/mediumPlayers.txt`

  - `USERS DATA FOLDER/hardPlayers.txt`

  

### Clear Data (Administrator Function)

1. Select `[5] CLEAR DATA` from the main menu

2. Enter the administrator password: `AryanGh#Minesweeper`

  

### Data Persistence Mechanism

- **User Actions** and **Game Events** trigger data storage functions:

  - `saveUsersData()`

  - `easyPlayersData()`

  - `mediumPlayersData()`

  - `hardPlayersData()`

- Data is loaded using `loadData()`

  

  

## 9. Troubleshooting

Common issues and solutions:

- **Missing directories**: Ensure all required directories exist to avoid crashes on startup.

- **Permission errors**: Verify the game has write permissions to the directories.

- **Compilation errors**: Confirm the correct C++ compiler version is installed.

- **Display issues**: Ensure the console supports UTF-8 and special console features.

- **Reset game data**: Use the Clear Data function with the administrator password.

  
## Developer

This project was developed by Aryan Ghasemi.

  

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.