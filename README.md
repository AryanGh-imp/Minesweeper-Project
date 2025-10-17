# Minesweeper Project

A modern **console-based implementation** of the classic Minesweeper game, written in **C++**, featuring multiple difficulty levels, user accounts, performance tracking, and a leaderboard system.

![MineSweeper](https://github.com/user-attachments/assets/a2486081-87d4-40a8-9ce0-e64531da36d1)


> **Disclaimer:**
> This project is a **personal educational project** inspired by the classic Minesweeper game.
> It is not affiliated with or endorsed by Microsoft or any other entity.

---

## 🎮 Overview

This project recreates the classic Minesweeper experience right in your terminal — complete with colorful visuals, Unicode characters, and smooth gameplay.  
It includes features such as **account management**, **difficulty modes**, **leaderboards**, and **data persistence** for tracking your performance.

---

## ✨ Features

- 🧠 **Classic Gameplay** — Reveal safe cells and avoid the mines!  
- 🎚️ **Difficulty Levels** — Easy, Medium, Hard, or Custom grids  
- 👤 **User Accounts** — Create and manage player profiles  
- 🏆 **Leaderboard System** — Compare your best times and scores  
- 🎨 **Visual Console UI** — Color-coded text and Unicode graphics  
- 🔒 **First Move Safety** — Your first step is always safe

---

## 💻 Requirements

- Windows OS (uses Windows Console API)  
- C++11 compatible compiler (e.g., MinGW, Visual Studio)  
- Console supporting UTF-8 characters

---

## ▶️ How to Play

1. **Create an account** or log in.  
2. **Select a difficulty level.**  
3. Use the following controls:
   - `WASD` → Move cursor  
   - `Enter` → Reveal a cell  
   - `F` → Flag or unflag a cell  
   - `Esc` → Exit the game  

**Goal:** Clear all safe cells without detonating a mine!

---

## 🧾 Game Rules

- Each revealed number shows how many mines surround that cell.  
- Use logic to flag or clear cells safely.  
- If you open a mine — game over! 💣  
- Win by uncovering all non-mine cells.

---

## 🗂️ Data & Files

Game data and user information are saved in text files:

```

USERS DATA FOLDER/
│
├── UDF.txt                → User credentials
├── easyPlayers.txt        → Easy mode stats
├── mediumPlayers.txt      → Medium mode stats
└── hardPlayers.txt        → Hard mode stats

```

---

## 🧱 Project Structure

```

Minesweeper/
│
├── maingame.cpp
├── GUIDE/
│   ├── MineSweeperGuidePage1.txt
│   ├── MineSweeperGuidePage2.txt
│   └── MineSweeperGuidePage3.txt
├── LOGOS/
│   ├── flag.txt
│   └── gojo.txt
├── USERS DATA FOLDER/
│   ├── UDF.txt
│   ├── easyPlayers.txt
│   ├── mediumPlayers.txt
│   └── hardPlayers.txt
└── CLEAR DATA/
└── clearDataSection.txt

````

---

## ⚙️ Compilation

### 🧩 Using MinGW G++
```bash
g++ maingame.cpp -o maingame.exe -std=c++11
````

### 🧩 Using Visual Studio Command Line

```bash
cl /EHsc maingame.cpp /Fe:maingame.exe
```

---

## 🧑‍💻 Difficulty Levels

| Level  | Grid Size  | Mines   |
| ------ | ---------- | ------- |
| Easy   | 9×9        | 10      |
| Medium | 14×14      | 40      |
| Hard   | 20×20      | 99      |
| Custom | NxN (9–40) | 10–N²−1 |

---

## 🧹 Data Management

* Game automatically creates data files on first run.
* Admin can clear data using `[5] CLEAR DATA` from the menu.
* Admin password: `AryanGh#Minesweeper`

---

## ⚠️ Troubleshooting

* Ensure directories exist (`GUIDE`, `LOGOS`, `USERS DATA FOLDER`, etc.)
* Use UTF-8 enabled console for proper visuals
* Verify compiler supports C++11

---

## 👨‍💻 Developer

Developed by **Aryan Ghasemi**

---

## 📜 License

This project is licensed under the **MIT License** — see [LICENSE](LICENSE.md) for details.
