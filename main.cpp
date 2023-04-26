#include <bits/stdc++.h>
#include <vector>
#define ROWS 9
#define COLS 9
#define RANGE 100

using namespace std;

void line() { cout << endl << "~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl; }
class Minesweeper {
  int realBoard[ROWS][COLS];
  char showBoard[ROWS][COLS];
  int win, lose, movesLeft;
  void intializRealBoard() {
    srand(time(0));
    for (int i = 0; i < ROWS; i++) {
      for (int j = 0; j < COLS; j++) {
        int n = rand() % RANGE;
        if (n < 85) {
          realBoard[i][j] = 0;
          movesLeft++;
        } else
          realBoard[i][j] = 1;
      }
    }
  }
  void intializShowBoard() {
    for (int i = 0; i < ROWS; i++) {
      for (int j = 0; j < COLS; j++) {
        showBoard[i][j] = '-';
      }
    }
  }

public:
  Minesweeper() {
    win = lose = movesLeft = 0;
    intializRealBoard();
    intializShowBoard();
  }
  //~Minesweeper();
  void displayShowBoard() {
    cout << endl << "Minesweeper Board";
    line();
    cout << "     ";
    for (int i = 1; i <= COLS; i++)
      cout << i << " ";
    cout << endl;
    for (int i = 0; i < ROWS; i++) {
      cout << i + 1;
      cout << "    ";
      for (int j = 0; j < COLS; j++) {
        cout << showBoard[i][j] << " ";
      }
      cout << endl;
    }
  }
  void displayRealBoard() {
    line();
    for (int i = 0; i < ROWS; i++) {
      cout << i + 1;
      cout << "    ";
      for (int j = 0; j < COLS; j++) {
        cout << realBoard[i][j] << " ";
      }
      cout << endl;
    }
  }
  bool isAvailable(int row, int col) {
    return (row > 0) && (row < ROWS) && (col > 0) && (col < COLS);
  }
  bool isMine(int row, int col) { return realBoard[row][col]; }
  void sweepAt(int row, int col, bool firstTime) {
    // if cell has mine
    if (firstTime && isMine(row, col))
      realBoard[row][col] = 0;

    if (isMine(row, col)) {
      lose = 1;
      return;
    }
    int count = 0;
    /*
        Count all the mines in the 8 adjacent
        cells

            N.W   N   N.E
              \   |   /
               \  |  /
            W----Cell----E
                 / | \
               /   |  \
            S.W    S   S.E

        Cell-->Current Cell (row, col)
        N -->  North        (row-1, col)
        S -->  South        (row+1, col)
        E -->  East         (row, col+1)
        W -->  West         (row, col-1)
        N.E--> North-East   (row-1, col+1)
        N.W--> North-West   (row-1, col-1)
        S.E--> South-East   (row+1, col+1)
        S.W--> South-West   (row+1, col-1)
    */

    // North
    if (isAvailable(row - 1, col)) {
      if (isMine(row - 1, col))
        count++;
      else if (firstTime)
        sweepAt(row - 1, col, false);
    }

    // South
    if (isAvailable(row + 1, col)) {
      if (isMine(row + 1, col))
        count++;
      else if (firstTime)
        sweepAt(row + 1, col, false);
    }

    // East
    if (isAvailable(row, col + 1)) {
      if (isMine(row, col + 1))
        count++;
      else if (firstTime)
        sweepAt(row, col + 1, false);
    }

    // West
    if (isAvailable(row, col - 1)) {
      if (isMine(row, col - 1))
        count++;
      else if (firstTime)
        sweepAt(row, col - 1, false);
    }
    // North-East
    if (isAvailable(row - 1, col + 1)) {
      if (isMine(row - 1, col + 1))
        count++;
      else if (firstTime)
        sweepAt(row - 1, col + 1, false);
    }
    // North-West
    if (isAvailable(row - 1, col - 1)) {
      if (isMine(row - 1, col - 1))
        count++;
      else if (firstTime)
        sweepAt(row - 1, col - 1, false);
    }
    // South-East
    if (isAvailable(row + 1, col + 1)) {
      if (isMine(row + 1, col + 1))
        count++;
      else if (firstTime)
        sweepAt(row + 1, col + 1, false);
    }
    // South-West
    if (isAvailable(row + 1, col - 1)) {
      if (isMine(row + 1, col - 1))
        count++;
      else if (firstTime)
        sweepAt(row + 1, col - 1, false);
    }
    // showing in squre bombs
    showBoard[row][col] = count + '0';
    movesLeft--;
  }
  void flagBombs() {
    for (int i = 0; i < ROWS; i++) {
      for (int j = 0; j < COLS; j++) {
        if (realBoard[i][j] == 1)
          showBoard[i][j] = '*';
        //cout<<"i";
      }
    }
    displayShowBoard();
  }
  int movesToDo() { return movesLeft; }
  bool playerWin() { return (movesToDo() == 0); }
  bool playerLose() { return lose; }
};

int main() {
  Minesweeper ms;
  int row, col;
  bool firstTime = true;
  while (!ms.playerLose() && !ms.playerWin()) {
    ms.displayShowBoard();
    // uncomment below line if u want devmode or cheat.
     ms.displayRealBoard();
    cout << endl << " moves Left : " << ms.movesToDo();
    cout << endl << "enter row and col :" << endl;
    cin >> row;
    cin >> col;
    if (row > ROWS || col > COLS) {
      cout << endl << "invalid input please enter again.";
      continue;
    }
    ms.sweepAt(row - 1, col - 1, firstTime);
    firstTime = false;
    system("clear");
  }
  if (ms.playerLose())
    cout << endl << "there was a bomb u died.";
  ms.flagBombs();
}