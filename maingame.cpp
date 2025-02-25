#include <iostream>  
#include <cstdlib>
#include <time.h>
#include <windows.h>  
#include <fstream>
#include <conio.h>
#include <stdio.h>  
#include <random>
#include <string>
#include <chrono>

using namespace std;
using namespace chrono;

// Global Items //////////////////////////////////////////////////////////////////////////////

const string ADMINISTRATORPASSWORD = "AryanGh#Minesweeper";

struct User
{
    string username;
    string password;
};

struct Player
{
    bool isWin;
    string username;
    int correctCellsOpened;
    double timeTaken;
};

User userList[100];
int currentUsers = 0;

Player easyPlayers[100];
int easyPlayerNumber = 0;

Player mediumPlayers[100];
int mediumPlayerNumber = 0;

Player hardPlayers[100];
int hardPlayerNumber = 0;


const int MAX_SIZE = 40;          // Max board size
char hiddenBoard[MAX_SIZE][MAX_SIZE];
string displayBoard[MAX_SIZE][MAX_SIZE];
int boardSize = 9;               // Default
int totalMines = 10;             // Default
int cellsToReveal;
int cursorX = 0, cursorY = 0;    // Player's location

string gameMode;
string playerName;
int won = -1;

bool isFirstMove = true;
int firstMoveX = -1, firstMoveY = -1;

time_point<steady_clock> startTime, endTime;

// Functions Prototypes //////////////////////////////////////////////////////////////////////

void MainMenu();
void setColor(int textColor, int bgColor);
void sleepyPrint(string str);
void guide ();
void createAnAccount();
void saveUsersData();
void easyPlayersData();
void mediumPlayersData();
void hardPlayersData();
void clearData();
void initializeBoard();
void printBoard();
void placeMines(int numMines, int safeX, int safeY);
void setDifficulty();
void gameLoop();
void checkWin();
void toggleFlag(int x, int y);
void revealCell(int x, int y);
void loadData();
void checkAccount();
void deleteData();
void displayLeaderboardMenu();
void sortPlayersByWinStatusAndPerformance(string gameModeChoice);
void displayRankedLeaderboard(string gameModeChoice);
void setCursorPosition(int x, int y);
int countSurroundedMines(int x, int y);
void flagtxt();

// main //////////////////////////////////////////////////////////////////////////////////////

int main()
{
    SetConsoleOutputCP(CP_UTF8);

    // Hide the console cursor
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = false; // Set cursor to hidden mode
    SetConsoleCursorInfo(hConsole, &cursorInfo);

    while(true){
    easyPlayerNumber = 0;
    mediumPlayerNumber = 0;
    hardPlayerNumber = 0;
        bool isFirstMove = true;
        int firstMoveX = -1, firstMoveY = -1;
        won = -1;
        loadData();
        MainMenu();
        setDifficulty();
        initializeBoard();
        placeMines(totalMines, cursorX, cursorY);
        startTime = steady_clock::now(); // Start time tracking
        gameLoop();
    }
    return 0;
}

// Functions /////////////////////////////////////////////////////////////////////////////////

void setColor(int textColor, int bgColor) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (textColor + (bgColor * 16)));
}

void sleepyPrint(string str){
	for(int i=0 ; i < str.length() ; i++){
		Sleep(50);
		cout << str[i];
	}
}

void loadData(){
    ifstream udfFile("USERS DATA FOLDER/UDF.txt");
    if (udfFile.is_open()){
        User intializeUsers;
        while (udfFile >> intializeUsers.username && udfFile >> intializeUsers.password){
            userList[currentUsers] = intializeUsers;
            currentUsers++;
        }
    }

    ifstream efile("USERS DATA FOLDER/easyPlayers.txt");
    if (efile.is_open()){
        Player intializeEasy;
        while (efile >> intializeEasy.isWin && efile >> intializeEasy.username && efile >>
        intializeEasy.correctCellsOpened && efile >> intializeEasy.timeTaken){
            easyPlayers[easyPlayerNumber] = intializeEasy;
            easyPlayerNumber++;
        }
    }

    ifstream hfile("USERS DATA FOLDER/hardPlayers.txt");
    if (hfile.is_open()){
        Player intializeHard;
        while (hfile >> intializeHard.isWin && hfile >> intializeHard.username && hfile >>
        intializeHard.correctCellsOpened && hfile >> intializeHard.timeTaken){
            hardPlayers[hardPlayerNumber] = intializeHard;
            hardPlayerNumber++;
        }
    }

    ifstream mfile("USERS DATA FOLDER/mediumPlayers.txt");
    if (mfile.is_open()){
        Player intializeMedium;
        while (mfile >> intializeMedium.isWin && mfile >> intializeMedium.username && mfile >>
        intializeMedium.correctCellsOpened && mfile >> intializeMedium.timeTaken){
            mediumPlayers[mediumPlayerNumber] = intializeMedium;
            mediumPlayerNumber++;
        }
    }
}


void initializeBoard() {
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            hiddenBoard[i][j] = ' ';    // Empty blocks
            displayBoard[i][j] = "?"; // Coverd blocks
        }
    }
}

void printBoard() {
    system("cls");
    setColor(14, 0);
    cout << "Remaining cells to reveal: ";
    setColor(11,0);
    cout << cellsToReveal << "\n\n";
    setColor(7, 0);

    // Print top of the frame
    cout << "  ╔";
    for (int i = 0; i < boardSize * 3 + 1; i++) cout << "═";
    cout << "╗\n";

    // Print main (display) box
    for (int i = 0; i < boardSize; i++) {
        cout << "  ║ "; // Print left of the frame
        for (int j = 0; j < boardSize; j++) {
            if (i == cursorY && j == cursorX) {
                cout << "[" << displayBoard[i][j] << "]";
            } else {
                cout << displayBoard[i][j] << "  ";
            }
        }
        cout << "║\n"; // Print right of the frame
    }

    // Print bottom of the frame
    cout << "  ╚";
    for (int i = 0; i < boardSize * 3 + 1; i++) cout << "═";
    cout << "╝\n\n";

}

void placeMines(int numMines, int safeX, int safeY) {
    srand(static_cast<unsigned int>(time(nullptr)));
    for (int i = 0; i < numMines; i++) {
        int x = rand() % boardSize;
        int y = rand() % boardSize;
        if (hiddenBoard[y][x] != '*' && !(x == safeX && y == safeY)) {
            hiddenBoard[y][x] = '*';
        } else {
            i--; // Try again
        }
    }
}

void toggleFlag(int x, int y) {
    if (displayBoard[y][x] == "?") {
        displayBoard[y][x] = "\033[38;5;198mF\033[m"; // Flagging
    } else if (displayBoard[y][x] == "\033[38;5;198mF\033[m") {
        displayBoard[y][x] = "?"; // Remove flag
    }
}

int countSurroundedMines(int x, int y) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int nx = x + j, ny = y + i;
            if (nx >= 0 && nx < boardSize && ny >= 0 && ny < boardSize &&
            hiddenBoard[ny][nx] == '*') {
                count++;
            }
        }
    }

    return count;
}

void checkWin() {
    if (cellsToReveal == 0) {
        won = 1;
        printBoard();
        endTime = steady_clock::now(); // Stop the time
        duration<double> timePlayed = endTime - startTime;
        
        cout << endl
             << "\033[31mC\033[32mo\033[33mn\033[34mg\033[35mr\033[36ma\033[37mt\033[31mu\033[32ml\033[33ma\033[34mt\033[35mi\033[36mo\033[36mn\033[36ms\033[0m"
             << "\033[31m!\033[0m "
             << "\033[31mY\033[32mo\033[33mu\033[34m \033[35mh\033[36ma\033[37mv\033[31me\033[0m "
             << "\033[32mw\033[33mo\033[34mn\033[35me\033[36md\033[0m "
             << endl;

        cout << "Time Played: " << timePlayed.count() << " seconds.\n";
        
        if(gameMode == "EASY")
        {
            bool find = false;
            
            for(int i = 0; i < currentUsers; i++)
            {
                if(userList[i].username == playerName)
                {
                    for(int j = 0; j < easyPlayerNumber; j++)
                    {
                        if(easyPlayers[j].username == playerName && timePlayed.count() < easyPlayers[j].timeTaken)
                        {
                        find = true;
                        easyPlayers[j].username = playerName;
                        easyPlayers[j].isWin = true;
                        easyPlayers[j].timeTaken = timePlayed.count();
                        easyPlayers[j].correctCellsOpened = 71;
                        easyPlayersData();
                        return;
                        }
                        else if (easyPlayers[j].username == playerName && timePlayed.count() > easyPlayers[j].timeTaken)
                        {
                            find = true;
                            return;
                        }
                    }
                    if(!find)
                    {
                        easyPlayers[i].username = playerName;
                        easyPlayers[i].isWin = true;
                        easyPlayers[i].timeTaken = timePlayed.count();
                        easyPlayers[i].correctCellsOpened = 71;
                        easyPlayerNumber++;
                        easyPlayersData();
                    }
                }
            }
        }

        if(gameMode == "MEDIUM")
        {
            bool find = false;
            
            for(int i = 0; i < currentUsers; i++)
            {
                if(userList[i].username == playerName)
                {
                    for(int j = 0; j < mediumPlayerNumber; j++)
                    {
                        if(mediumPlayers[j].username == playerName && timePlayed.count() < mediumPlayers[j].timeTaken)
                        {
                        find = true;
                        mediumPlayers[j].username = playerName;
                        mediumPlayers[j].isWin = true;
                        mediumPlayers[j].timeTaken = timePlayed.count();
                        mediumPlayers[j].correctCellsOpened = 71;
                        mediumPlayersData();
                        return;
                        }
                        else if (mediumPlayers[j].username == playerName && timePlayed.count() > mediumPlayers[j].timeTaken)
                        {
                            find = true;
                            return;
                        }
                    }
                    if(!find)
                    {
                        mediumPlayers[i].username = playerName;
                        mediumPlayers[i].isWin = true;
                        mediumPlayers[i].timeTaken = timePlayed.count();
                        mediumPlayers[i].correctCellsOpened = 71;
                        mediumPlayerNumber++;
                        mediumPlayersData();
                    }
                }
            }
        }

        if(gameMode == "HARD")
        {
            bool find = false;
            
            for(int i = 0; i < currentUsers; i++)
            {
                if(userList[i].username == playerName)
                {
                    for(int j = 0; j < hardPlayerNumber; j++)
                    {
                        if(hardPlayers[j].username == playerName && timePlayed.count() < hardPlayers[j].timeTaken)
                        {
                        find = true;
                        hardPlayers[j].username = playerName;
                        hardPlayers[j].isWin = true;
                        hardPlayers[j].timeTaken = timePlayed.count();
                        hardPlayers[j].correctCellsOpened = 71;
                        hardPlayersData();
                        return;
                        }
                        else if (hardPlayers[j].username == playerName && timePlayed.count() > hardPlayers[j].timeTaken)
                        {
                            find = true;
                            return;
                        }
                    }
                    if(!find)
                    {
                        hardPlayers[i].username = playerName;
                        hardPlayers[i].isWin = true;
                        hardPlayers[i].timeTaken = timePlayed.count();
                        hardPlayers[i].correctCellsOpened = 71;
                        hardPlayerNumber++;
                        hardPlayersData();
                    }
                }
            }
        }
    }
}

void saveUsersData(){
    ofstream usersDataFile("USERS DATA FOLDER/UDF.txt" , ios::trunc);
    if (usersDataFile.is_open()){
        for(int i = 0; i < currentUsers; i++){
            usersDataFile << userList[i].username << " " <<  userList[i].password << "\n";
        }
    }
    usersDataFile.close();
}

void easyPlayersData(){
    ofstream easyPlayersData("USERS DATA FOLDER/easyPlayers.txt" , ios::trunc);
    if (easyPlayersData.is_open()){
        for(int i = 0; i < easyPlayerNumber; i++){
            easyPlayersData << easyPlayers[i].isWin << " " <<  easyPlayers[i].username << " "
            << easyPlayers[i].correctCellsOpened << " " << easyPlayers[i].timeTaken << "\n";
        }
    }
    easyPlayersData.close();
}

void mediumPlayersData(){
    ofstream mediumPlayersData("USERS DATA FOLDER/mediumPlayers.txt" , ios::trunc);
    if (mediumPlayersData.is_open()){
        for(int i = 0; i < mediumPlayerNumber; i++){
            mediumPlayersData << mediumPlayers[i].isWin << " " <<  mediumPlayers[i].username << " "
            << mediumPlayers[i].correctCellsOpened << " " << mediumPlayers[i].timeTaken << "\n";
        }
    }
    mediumPlayersData.close();
}

void hardPlayersData(){
    ofstream hardPlayersData("USERS DATA FOLDER/hardPlayers.txt" , ios::trunc);
    if (hardPlayersData.is_open()){
        for(int i = 0; i < hardPlayerNumber; i++){
            hardPlayersData << hardPlayers[i].isWin << " " <<  hardPlayers[i].username << " "
            << hardPlayers[i].correctCellsOpened << " " << hardPlayers[i].timeTaken << "\n";
        }
    }
    hardPlayersData.close();
}



void setDifficulty() {
    system("cls");

    setColor(11, 0);
    cout << "SELECT ";
    Sleep(500);

    setColor(6, 0);
    cout << "DIFFICULTY ";
    Sleep(500);

    setColor(4, 0);
    cout << "LEVEL:\n\n";
    Sleep(500);


    cout << "[1] ";
    setColor(11, 0);
    cout << "EASY ";
    setColor(7, 0);
    cout << "(9x9 , 10 mines)\n\n";
    Sleep(1000);

    setColor(4, 0);
    cout << "[2] ";
    setColor(6, 0);
    cout << "MEDIUM ";
    setColor(7, 0);
    cout << "(14x14 , 40 mines)\n\n";
    Sleep(1000);

    setColor(4, 0);
    cout << "[3] ";
    cout << "HARD ";
    setColor(7, 0);
    cout << "(20x20 , 99 mines)\n\n";
    Sleep(1000);

    setColor(4, 0);
    cout << "[4] ";
    setColor(7, 0);
    cout << "CUSTOM (your choice)\n\n\n";
    Sleep(1000);
    sleepyPrint("PLEASE SELECT YOUR OPTION (1-4)  \n\n");

    char choice;
    int inputNxN;
    int inputM;
    while(true){
        choice = getch();
        if(choice == '1' || choice == '2' || choice == '3' || choice == '4')
        {
            switch (choice) {
                case '1': boardSize = 9; totalMines = 10; gameMode = "EASY"; break;
                case '2': boardSize = 14; totalMines = 40; gameMode = "MEDIUM"; break;
                case '3': boardSize = 20; totalMines = 99; gameMode = "HARD"; break;
                case '4':
                    while (true){
                    cout << "Enter board size: ";
                    setColor(6, 0);
                    cout << "(nxn): ";
                    setColor(7, 0);
                    cin >> inputNxN;
                    if (inputNxN > 8 && inputNxN <= 40 ) break;
                    else{
                        setColor(4, 0);
                        cout << "INVALID INPUT!\nPLEASE CHOOSE A NUMBER FROM 9 TO 40\n\n";
                        setColor(7, 0);
                        }
                    }
                    boardSize = inputNxN;


                    while (true){
                    cout << "Enter number of mines ";
                    setColor(6, 0);
                    cout << "(m): ";
                    setColor(7, 0);
                    cin >> inputM;

                    if (inputM > 9 && inputM < boardSize * boardSize ) {break;}
                    else{
                        setColor(4, 0);
                        cout << "INVALID INPUT!\nPLEASE CHOOSE A NUMBER FROM 10 TO "
                        << boardSize * boardSize - 1 << "\n\n";
                        setColor(7, 0);
                        }
                    }
                    totalMines = inputM;
            }
            cellsToReveal = boardSize * boardSize - totalMines;
            break;
        }
    }
}

void revealCell(int x, int y) {

        if (isFirstMove)
        {
            for(int i = 0; i < boardSize; i++)
            {
                for(int j = 0; j < boardSize; j++)
                {
                    hiddenBoard[i][j] = ' ';
                }
            }

            firstMoveX = x;
            firstMoveY = y;
            placeMines(totalMines, firstMoveX, firstMoveY);
            isFirstMove = false;
        }

    if (x < 0 || x >= boardSize || y < 0 || y >= boardSize ||
    (displayBoard[y][x] != "?" && displayBoard[y][x] != "\033[38;5;198mF\033[m")) return;

    int mines = countSurroundedMines(x, y);
    if (hiddenBoard[y][x] == '*') {
        for(int i = 0; i < boardSize; i++){
            for(int j = 0; j < boardSize; j++){
                if(hiddenBoard[i][j] == '*'){displayBoard[i][j] = "\033[31m#\33[0m";} // Show all minee
            }
        }
        system("cls");
        printBoard();
        endTime = steady_clock::now(); // Stop the time
        setColor(4, 0);
        cout << "\n\nYOU HIT A MINE! GAME OVER!\n\n";
        setColor(14, 0);
        duration<double> timePlayed = endTime - startTime;
        cout << "Time Played: ";
        setColor(2, 0);
        cout << timePlayed.count();
        setColor(7, 0);
        cout << " seconds.\n";
        
        if(gameMode == "EASY")
        {
            bool find = false;
            
            for(int i = 0; i < currentUsers; i++)
            {
                if(userList[i].username == playerName)
                {
                    for(int j = 0; j < easyPlayerNumber; j++)
                    {
                        if(easyPlayers[j].username == playerName && timePlayed.count() < easyPlayers[j].timeTaken)
                        {
                        bool find = true;
                        easyPlayers[j].username = playerName;
                        easyPlayers[j].isWin = false;
                        easyPlayers[j].timeTaken = timePlayed.count();
                        easyPlayers[j].correctCellsOpened = boardSize * boardSize - cellsToReveal;
                        easyPlayersData();
                        }
                        else if (easyPlayers[j].username == playerName && timePlayed.count() > easyPlayers[j].timeTaken)
                        {
                            bool find = true;
                        }
                    }
                    if(!find)
                    {
                        easyPlayers[i].username = playerName;
                        easyPlayers[i].isWin = false;
                        easyPlayers[i].timeTaken = timePlayed.count();
                        easyPlayers[i].correctCellsOpened = boardSize * boardSize - cellsToReveal;
                        easyPlayerNumber++;
                        easyPlayersData();
                    }
                }
            }
        }

        if(gameMode == "MEDIUM")
        {
            bool find = false;
            
            for(int i = 0; i < currentUsers; i++)
            {
                if(userList[i].username == playerName)
                {
                    for(int j = 0; j < mediumPlayerNumber; j++)
                    {
                        if(mediumPlayers[j].username == playerName && timePlayed.count() < mediumPlayers[j].timeTaken)
                        {
                        bool find = true;
                        mediumPlayers[j].username = playerName;
                        mediumPlayers[j].isWin = false;
                        mediumPlayers[j].timeTaken = timePlayed.count();
                        mediumPlayers[j].correctCellsOpened = boardSize * boardSize - cellsToReveal;
                        mediumPlayersData();
                        }
                        else if (mediumPlayers[j].username == playerName && timePlayed.count() > mediumPlayers[j].timeTaken)
                        {
                            bool find = true;
                        }
                    }
                    if(!find)
                    {
                        mediumPlayers[i].username = playerName;
                        mediumPlayers[i].isWin = false;
                        mediumPlayers[i].timeTaken = timePlayed.count();
                        mediumPlayers[i].correctCellsOpened = boardSize * boardSize - cellsToReveal;
                        mediumPlayerNumber++;
                        mediumPlayersData();
                    }
                }
            }
        }

        if(gameMode == "HARD")
        {
            bool find = false;
            
            for(int i = 0; i < currentUsers; i++)
            {
                if(userList[i].username == playerName)
                {
                    for(int j = 0; j < hardPlayerNumber; j++)
                    {
                        if(hardPlayers[j].username == playerName && timePlayed.count() < hardPlayers[j].timeTaken)
                        {
                        bool find = true;
                        hardPlayers[j].username = playerName;
                        hardPlayers[j].isWin = false;
                        hardPlayers[j].timeTaken = timePlayed.count();
                        hardPlayers[j].correctCellsOpened = boardSize * boardSize - cellsToReveal;
                        hardPlayersData();
                        }
                        else if (hardPlayers[j].username == playerName && timePlayed.count() > hardPlayers[j].timeTaken)
                        {
                            bool find = true;
                        }
                    }
                    if(!find)
                    {
                        hardPlayers[i].username = playerName;
                        hardPlayers[i].isWin = false;
                        hardPlayers[i].timeTaken = timePlayed.count();
                        hardPlayers[i].correctCellsOpened = boardSize * boardSize - cellsToReveal;
                        hardPlayerNumber++;
                        hardPlayersData();
                    }
                }
            }
        }
        won = 0;
    }

    else if (mines > 0) {
        switch (mines)
        {
        case 1:
            displayBoard[y][x] = "\033[38;5;81m1\033[0m";
            break;
        
        case 2:
            displayBoard[y][x] = "\033[38;5;2m2\033[0m";
            break;
        case 3:
            displayBoard[y][x] = "\033[38;5;5m3\033[0m";
            break;
        case 4:
            displayBoard[y][x] = "\033[38;5;3m4\033[0m";
            break;
        case 5:
            displayBoard[y][x] = "\033[38;5;1m5\033[0m";
            break;
        case 6:
            displayBoard[y][x] = "\033[38;5;12m6\033[0m";
            break;
        case 7:
            displayBoard[y][x] = "\033[38;5;9m7\033[0m";
            break;
        }
        cellsToReveal--;
    } else {
        displayBoard[y][x] = ' ';
        cellsToReveal--;
        // Reveal surrounded cells
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                revealCell(x + j, y + i);
            }
        }
    }
}

void guide (){
    ifstream file1("GUIDE/MineSweeperGuidePage1.txt");
    string line1;

    if (file1.is_open()) {
        while (getline(file1, line1)) {
            cout << line1 << endl;
        }
        file1.close();
    }
    cout << "\nPress \033[31mEnter\033[0m to go to the next page...";
    
    while (true)
    {
        char inputChar3 = getch();
        if(inputChar3 == 13 || inputChar3 == 10)
        {
            break;
        }
    }

    system("cls");

    ifstream file2("GUIDE/MineSweeperGuidePage2.txt");
    string line2;

    if (file2.is_open()) {
        while (getline(file2, line2)) {
            cout << line2 << endl;
        }
        file2.close();
    }

    cout << "\nPress \033[31mEnter\033[0m to go to the next page...";
    
    while (true)
    {
        char inputChar3 = getch();
        if(inputChar3 == 13 || inputChar3 == 10)
        {
            break;
        }
    }


    system("cls");

    ifstream file3("GUIDE/MineSweeperGuidePage3.txt");
    string line3;

    if (file3.is_open()) {
        while (getline(file3, line3)) {
            cout << line3 << endl;
        }
        file3.close();
    }

    cout << "\nPress \033[31mESC\033[0m to return to the main menu...";
    
    while (true) {
        char inputChar3 = getch();
        if (inputChar3 == 27) {
            break;
        }
    }
}

void createAnAccount() {
    system("cls");

    setColor(5, 0);
    sleepyPrint("👤 Create a New Account 👤\n\n");

    setColor(7, 0);
    string inputUserName, inputPassword;


    cout << "Enter your username: ";
    setColor(11,0);
    cin >> inputUserName;
    setColor(7,0);

    // Check if the username is already taken
    for (int i = 0; i < currentUsers; i++) {
        if (userList[i].username == inputUserName) {
            cout << "This username is already taken! Please choose another one.\n";
            Sleep(1500);
            createAnAccount();  // Return and let the user try again with a new username
            return;
        }
    }

    while (true) {
        cout << "Enter your password (at least 8 characters): ";
        setColor(4,0);
        cin >> inputPassword;
        setColor(7,0);

        // Check if the password is at least 8 characters long
        if (inputPassword.length() >= 8) {
            break;
        } else {
            cout << "The password must be at least 8 characters long. Please enter it again.\n";
        }
    }

    // Save the new user account information
    userList[currentUsers].username = inputUserName;
    userList[currentUsers].password = inputPassword;

    currentUsers++;

    saveUsersData();

    setColor(14, 0);
    cout << "\nYour account has been successfully created!\n\n";
    setColor(7, 0);


    cout << "Press \033[31mESC\033[0m to return to the main menu...";
    while (true)
    {
        char inputChar2 = getch();
        if(inputChar2 == 27)
        {
            break;
        }
    }
}

void gameLoop() {
    while (true) {
        printBoard();
        cout << "\nPress \033[31mESC\033[0m to return to exit the game...";
        char input = getch();
        switch (input) {
            case 'w': if (cursorY > 0) cursorY--; break;
            case 's': if (cursorY < boardSize - 1) cursorY++; break;
            case 'a': if (cursorX > 0) cursorX--; break;
            case 'd': if (cursorX < boardSize - 1) cursorX++; break;
            case 'f': toggleFlag(cursorX, cursorY); break;
            case 13: revealCell(cursorX, cursorY); checkWin(); break; //Enter
            case 10: revealCell(cursorX, cursorY); checkWin(); break; //Enter
            case 27:setColor(4, 0); cout << "\nExiting game...\n";Sleep(3000);exit(0); // Esc and exit            
            default: break;
        }
        if(won == 1 || won == 0)
        {
            cout << "\nPress \033[31mESC\033[0m to return to the main menu...";   
            while (true) {
                char inputChar3 = getch();
                if (inputChar3 == 27) {
                    break;
                }
            }
            return;
        }        
    }
}


void MainMenu()
{
    system("cls");

    setColor(12 , 0);
    sleepyPrint("💣 MINE SWEEPER 💣");
    cout << "\n\n" ;
    setColor(7 , 0);
    sleepyPrint("DEVELOPED BY ");
    setColor(11,0);
    sleepyPrint("ARYAN GHASEMI");
    cout<< "\n\n";
    setColor(7 , 0);
    sleepyPrint("============================================");
    Sleep(800);
    cout << "\n\n";
    setColor(12 , 0);
    cout << "[1]";
    setColor(7 , 0);   
    cout << " NEW GAME\n\n";

    setColor(12 , 0);
    cout << "[2]";
    setColor(7 , 0);   
    cout << " CREATE AN ACCOUNT\n\n";

    setColor(12 , 0);
    cout << "[3]";
    setColor(7 , 0);   
    cout << " GUIDE\n\n";

    setColor(12 , 0);
    cout << "[4]";
    setColor(7 , 0);   
    cout << " LEADER BOARD\n\n";

    setColor(12 , 0);
    cout << "[5]";
    setColor(7 , 0);   
    cout << " CLEAR DATA\n\n";

    setColor(12 , 0);
    cout << "[6]";
    setColor(7 , 0);   
    cout << " EXIT\n\n";

    Sleep(500);

    sleepyPrint("PLEASE SELECT YOUR OPTION (1-6)  ");
    flagtxt();


    switch(char inputChar1 = getch()){
	 	case '1':{
            checkAccount();
		}break;


	 	case '2':{
	 	    createAnAccount();
            MainMenu();	
		}break;

		case '3':{
            system("cls");
			guide();
            MainMenu();
		}break;

		case '4':{
            displayLeaderboardMenu();
            MainMenu();  
		}break;

        case '5':{

			system("cls");
			clearData();
            exit(0);
		}break;
		
        case '6':
        {
        system("cls");
        setColor(11,0);
        sleepyPrint("Hope you enjoy!\n");
        sleepyPrint("SAYONARA!!!\n");
        Sleep(1000);

        setColor(15,0);

        ifstream file("LOGOS/gojo.txt");
        string line;

        if (file.is_open())
        {
            while (getline(file, line))
            {
                cout << line << endl;
            }
            file.close();
        }

        Sleep(4000);

        exit(0);
        }
        break;
		
		default:
			system("cls");
            setColor(12,0);
			sleepyPrint("Invalid input!\nPlease choose a number from 1 to 6\n\n");
            setColor(7,0);
            Sleep(1000);
            cout << "Press \033[31mESC\033[0m to return to the main menu...";
            while (true)
            {
                char inputChar2 = getch();
                if(inputChar2 == 27)
                {
                    break;
                }
            }
            MainMenu();
			

	}
}

void clearData(){

    setColor(4, 0);
    cout << "CLEAR DATA SECTION :\n";
    setColor(14, 0);

    ifstream CDSfile("CLEAR DATA/clearDataSection.txt");
    string CDSline;

    if (CDSfile.is_open()){
        while(getline(CDSfile , CDSline)){
            cout << CDSline << endl;
        }
        CDSfile.close();
    }
    cout << "\n" << endl;
    string inputPass;
    while (true){
        setColor(4, 0);
        sleepyPrint("ENTER ADMINISTRATOR PASSWORD : ");
        setColor(4, 15);
        cin >> inputPass;
        setColor(7, 0);
        if(inputPass == "AryanGh#Minesweeper"){deleteData();break;}
        else{
            setColor(14, 0);
            cout << "\n\nINVALID PASSWORD - TRY AGAIN\n\n";
        }
    }
    system("cls");
    setColor(4, 0);
    Sleep(1000);
    sleepyPrint("DELETING");
    Sleep(1000);
    cout << ".";
    Sleep(1000);
    cout << ".";
    Sleep(1000);
    cout << ".";
    setColor(2, 0);
    cout << "\n\n";
    sleepyPrint("DONE!");
    cout << "\n\n";
    sleepyPrint("DATA HAS BEEN SUCCESSFULLY DELETED");
    cout << "\n\n";
    sleepyPrint("APPLICATION WILL BE CLOSED");
    Sleep(3000);
}

void checkAccount() {
    system("cls");
    setColor(6, 0);
    sleepyPrint("🔑 LOG IN TO YOUR ACCOUNT 🔑\n\n");
    setColor(7, 0);
    cout << "USERNAME : ";
    setColor(11, 0);
    string inputUsername;
    cin >> inputUsername;
    cout << "\n";
    setColor(7, 0);
    cout << "PASSWORD : ";
    setColor(11, 0);
    string inputPassword;
    cin >> inputPassword;
    cout << "\n";

    bool accountFound = false;

    if (currentUsers == 0) {
        setColor(4, 0);
        sleepyPrint("No accounts found! Please create an account first.\n\n");
        setColor(7, 0);
        cout << "\nPress \033[31mESC\033[0m to return to the main menu...";
        while (true) {
            char inputChar = getch();
            if (inputChar == 27) {
                MainMenu();
                return;
            }
        }
    }

    for (int i = 0; i < currentUsers; i++) {
        if (userList[i].username == inputUsername && userList[i].password == inputPassword) {
            playerName = userList[i].username;
            setColor(2, 0);
            sleepyPrint("✅ YOU HAVE SUCCESSFULLY LOGGED IN TO YOUR ACCOUNT!\n");
            Sleep(1000);
            setColor(7, 0);
            accountFound = true;
            return;
        }
    }

    if (!accountFound) {
        setColor(4, 0);
        sleepyPrint("❌ INVALID USERNAME OR PASSWORD!\n");
        setColor(7, 0);
        cout << "\nPress \033[31mESC\033[0m to return to the main menu...\n";
        cout << "Press \033[31mR\033[0m to try again...\n";
        while (true) {
            char inputChar = getch();
            if (inputChar == 27) {
                MainMenu();
                return;
            } else if (inputChar == 'R' || inputChar == 'r') {
                checkAccount();
                return;
            }
        }
    }
}


void sortPlayersByWinStatusAndPerformance(string gameModeChoice) {

    Player sort[100];
    int sortPlayerNumber = 0;

    if(gameModeChoice == "EASY")
    {
        for(int i = 0; i < easyPlayerNumber; i++)
        {
            sort[i] = easyPlayers[i];
        }
        sortPlayerNumber = easyPlayerNumber;
    }

    else if(gameModeChoice == "MEDIUM")
    {
            for(int i = 0; i < mediumPlayerNumber; i++)
        {
            sort[i] = mediumPlayers[i];
        }
        sortPlayerNumber = mediumPlayerNumber;
    }

    else if(gameModeChoice == "HARD")
    {
            for(int i = 0; i < hardPlayerNumber; i++)
        {
            sort[i] = hardPlayers[i];
        }
        sortPlayerNumber = hardPlayerNumber;
    }

    for (int i = 0; i < sortPlayerNumber - 1; i++) {
        for (int j = 0; j < sortPlayerNumber - i - 1; j++) {
            bool swap = false;

            if (sort[j].isWin && !sort[j + 1].isWin) {
                swap = false;
            } else if (!sort[j].isWin && sort[j + 1].isWin) {
                swap = true;
            } else if (sort[j].isWin && sort[j + 1].isWin) {
                if (sort[j].timeTaken > sort[j + 1].timeTaken) {
                    swap = true;
                }
            } else if (!sort[j].isWin && !sort[j + 1].isWin) {
                if (sort[j].correctCellsOpened < sort[j + 1].correctCellsOpened) {
                    swap = true;
                } else if (sort[j].correctCellsOpened == sort[j + 1].correctCellsOpened &&
                           sort[j].timeTaken > sort[j + 1].timeTaken) {
                    swap = true;
                }
            }

            if (swap) {
                Player temp = sort[j];
                sort[j] = sort[j + 1];
                sort[j + 1] = temp;
            }
        }
    }

        if(gameModeChoice == "EASY")
    {
        for(int i = 0; i < easyPlayerNumber; i++)
        {
            easyPlayers[i] = sort[i];
        }
    }

    else if(gameModeChoice == "MEDIUM")
    {
            for(int i = 0; i < mediumPlayerNumber; i++)
        {
            mediumPlayers[i] = sort[i];
        }        
    }

    else if(gameModeChoice == "HARD")
    {
            for(int i = 0; i < hardPlayerNumber; i++)
        {
            hardPlayers[i] = sort[i];
        }        
    }
}


void displayLeaderboardMenu() {
        system("cls");
        setColor(6, 0);
        sleepyPrint("🏆 LEADERBOARD MENU 🏆\n");
        setColor(7, 0);

        Sleep(500);

        cout << "\n\n";
        setColor(12 , 0);
        cout << "[1]";
        setColor(7 , 0);   
        cout << " EASY LEADERBOARD\n\n";

        setColor(12 , 0);
        cout << "[2]";
        setColor(7 , 0);   
        cout << " MEDIUM LEADERBORD\n\n";

        setColor(12 , 0);
        cout << "[3]";
        setColor(7 , 0);   
        cout << " HARD LEADERBORD\n\n";

        Sleep(500);

        sleepyPrint("Please select your option (1-3)  ");


        while (true)
        {
            char levelChoice = getch();
            switch (levelChoice) {
                case '1': sortPlayersByWinStatusAndPerformance("EASY");displayRankedLeaderboard("EASY"); return;
                case '2': sortPlayersByWinStatusAndPerformance("MEDIUM");displayRankedLeaderboard("MEDIUM"); return;
                case '3': sortPlayersByWinStatusAndPerformance("HARD");displayRankedLeaderboard("HARD"); return;
            }
        }    
}

void displayRankedLeaderboard(string gameModeChoice) {
    Player listedPlayer[100];
    int listedPlayerNubers = 0;

    if(gameModeChoice == "EASY")
    {
        for(int i = 0; i < easyPlayerNumber; i++)
        {
            listedPlayer[i] = easyPlayers[i];
            listedPlayerNubers++;
        } 
    }

        if(gameModeChoice == "MEDIUM")
    {
        for(int i = 0; i < mediumPlayerNumber; i++)
        {
            listedPlayer[i] = mediumPlayers[i];
            listedPlayerNubers++;
        } 
    }
        if(gameModeChoice == "HARD")
    {
        for(int i = 0; i < hardPlayerNumber; i++)
        {
            listedPlayer[i] = hardPlayers[i];
            listedPlayerNubers++;
        } 
    }


    system("cls");
    setColor(11, 0);
    cout << "🏆 LEADERBOARD 🏆\n\n";
    setColor(7, 0);

    cout << "Rank\tUsername\tStatus\t\tScore/Time\n";
    cout << "------------------------------------------------------------------\n";

    for (int i = 0; i < listedPlayerNubers; i++) {
        cout << (i + 1) << "\t" 
             << listedPlayer[i].username << "\t\t";

        if (listedPlayer[i].isWin) {
            cout << "Winner\t\t" << listedPlayer[i].timeTaken << "s\n";
        } else {
            cout << "Loser\t\t" << listedPlayer[i].correctCellsOpened 
                 << " cells (" << listedPlayer[i].timeTaken << "s)\n";
        }
    }

    cout << "\nPress \033[31mESC\033[0m to return to the main menu...";
    while (true) {
        char inputChar6 = getch();
        if (inputChar6 == 27){break;}
    }
}


void deleteData (){
    ofstream targetFile("USERS DATA FOLDER/UDF.txt" , ios::trunc);
    targetFile.close();
}


void setCursorPosition(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void flagtxt() {
    ifstream file("LOGOS/flag.txt");
    string line;

    int i = 0;

    setColor(12, 0);

    if (file.is_open()) {
        while (getline(file, line))
        {
            setCursorPosition(65, i);
            cout << line << endl;
            Sleep(80);
            i++;
        }
        file.close();
    }
    setColor(7, 0);
}

