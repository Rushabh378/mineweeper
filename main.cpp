#include <bits/stdc++.h>
#define ROWS 9
#define COLS 9
#define RANGE 100

using namespace std;

void line() { cout << endl << "~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl; }

class Tiles {
protected:
  char showBoard[ROWS][COLS];
  int realBoard[ROWS][COLS];
  int markedArea[ROWS][COLS] = {0};
  int bombLeft = 0;

  void initialisingRealBoard() {
    srand(time(0));
    for (int i = 0; i < ROWS; i++) {
      for (int j = 0; j < COLS; j++) {
        int n = rand() % RANGE;
        if (n < 80)
          realBoard[i][j] = 0;
        else {
          realBoard[i][j] = 1;
          bombLeft++;
        }
      }
    }
  }
  void initialisingShowBoard() {
    for (int i = 0; i < ROWS; i++) {
      for (int j = 0; j < COLS; j++) {
        showBoard[i][j] = '-';
      }
    }
  }

public:
  Tiles() {
    initialisingRealBoard();
    initialisingShowBoard();
  }
  void displayBoard(string board = "front") {
    if (board == "front")
      cout << endl << "Minesweeper Board";
    else if (board == "marked")
      cout << endl << "marked Board";
    else
      cout << endl << "Cheat Board";
    line();
    cout << "     ";
    for (int i = 1; i <= COLS; i++)
      cout << i << " ";
    cout << endl;
    for (int i = 0; i < ROWS; i++) {
      cout << i + 1;
      cout << "    ";
      for (int j = 0; j < COLS; j++) {
        if (board == "front")
          cout << showBoard[i][j] << " ";
        else if (board == "marked")
          cout << markedArea[i][j] << " ";
        else
          cout << realBoard[i][j] << " ";
      }
      cout << endl;
    }
  }
};
class Minesweeper : public Tiles {
  bool win, lose;

public:
  int bombToFind;
  Minesweeper() {
    win = lose = 0;
    bombToFind = bombLeft;
  }
  // checking input value is in scope.
  bool isAvailable(int row, int col) {
    return (row >= 0) && (row < ROWS) && (col >= 0) && (col < COLS);
  }
  // has mine?
  bool isMine(int row, int col) { return realBoard[row][col]; }
  void sweepAt(int row, int col, bool firstTime) {
    if (firstTime && isMine(row, col))
      realBoard[row][col] = 0;
    // if cell has mine
    if (isMine(row, col)) {
      lose = true;
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
      else if (firstTime && !markedArea[row - 1][col])
        sweepAt(row - 1, col, false);
    }

    // South
    if (isAvailable(row + 1, col)) {
      if (isMine(row + 1, col))
        count++;
      else if (firstTime && !markedArea[row + 1][col])
        sweepAt(row + 1, col, false);
    }

    // East
    if (isAvailable(row, col + 1)) {
      if (isMine(row, col + 1))
        count++;
      else if (firstTime && !markedArea[row][col + 1])
        sweepAt(row, col + 1, false);
    }

    // West
    if (isAvailable(row, col - 1)) {
      if (isMine(row, col - 1))
        count++;
      else if (firstTime && !markedArea[row][col - 1])
        sweepAt(row, col - 1, false);
    }
    // North-East
    if (isAvailable(row - 1, col + 1)) {
      if (isMine(row - 1, col + 1))
        count++;
      else if (firstTime && !markedArea[row - 1][col + 1])
        sweepAt(row - 1, col + 1, false);
    }
    // North-West
    if (isAvailable(row - 1, col - 1)) {
      if (isMine(row - 1, col - 1))
        count++;
      else if (firstTime && !markedArea[row - 1][col - 1])
        sweepAt(row - 1, col - 1, false);
    }
    // South-East
    if (isAvailable(row + 1, col + 1)) {
      if (isMine(row + 1, col + 1))
        count++;
      else if (firstTime && !markedArea[row + 1][col + 1])
        sweepAt(row + 1, col + 1, false);
    }
    // South-West
    if (isAvailable(row + 1, col - 1)) {
      if (isMine(row + 1, col - 1))
        count++;
      else if (firstTime && !markedArea[row + 1][col - 1])
        sweepAt(row + 1, col - 1, false);
    }
    // marking area
    if (count == 0)
      markedArea[row][col] = 1;
    // showing bombs in cell
    showBoard[row][col] = count + '0';
    // clearing area
    if (!firstTime && count == 0)
      sweepAt(row, col, true);
  }
  // flaging unflaging bomb and trigger win condition
  void flagBomb() {
    int row, col;
    cout << "provide row and col to flag:" << endl;
    cin >> row;
    cin >> col;
    // flaging the bomb
    if (showBoard[row - 1][col - 1] == '-') {
      showBoard[row - 1][col - 1] = 'f';
      bombToFind--;
      // if flaged real bomb
      if (realBoard[row - 1][col - 1])
        bombLeft--;
      // unflaging the bomb
    } else if (showBoard[row - 1][col - 1] == 'f') {
      showBoard[row - 1][col - 1] = '-';
      bombToFind++;
      // if unflaged real bomb
      if (realBoard[row - 1][col - 1])
        bombLeft++;
    } else
      cout << endl << "there is no need to flag ucovered area.";
    if (bombLeft == 0)
      win = true;
  }
  // trigger and display all bombs.
  void triggerBombs() {
    for (int i = 0; i < ROWS; i++)
      for (int j = 0; j < COLS; j++)
        if (realBoard[i][j] == 1)
          showBoard[i][j] = '*';
    displayBoard();
  }
  bool isGameOver() {
    if (win || lose)
      return true;
    return false;
  }
  void gameOverScreen() {
    if (!win && !lose)
      return;
    if (win)
      cout << endl << "good job you found all the bombs.\n";
    if (lose)
      cout << endl << "there was a bomb buddy u lost.\n";
    triggerBombs();
  }
};

int main() {
  Minesweeper ms;
  int row, col;
  bool firstTime = true, exit = false;
  while (!exit) {
    ms.displayBoard();
    // uncomment below line if u want devmode or cheat.
    ms.displayBoard("cheat");
    cout << endl;
    cout << "* Enter row and col to sweep." << endl;
    cout << "* Enter 0 to flag or unflag bomb." << endl;
    cout << "* Bomb to find : " << ms.bombToFind << endl;
    cin >> row;
    if (row == 0) {
      ms.flagBomb();
      system("clear");
      continue;
    }
    cin >> col;
    if (!ms.isAvailable(row - 1, col - 1)) {
      cout << endl << "invalid input please enter again.";
      continue;
    }
    ms.sweepAt(row - 1, col - 1, firstTime);
    firstTime = false;
    system("clear");
    if (ms.isGameOver()) {
      ms.gameOverScreen();
      char choice;
      cout << endl << "restart game y/n ?";
      cin >> choice;
      if (choice == 'y' || choice == 'Y') {
        ms = Minesweeper();
        firstTime = true;
        continue;
      } else
        exit = true;
    }
  }
  cout << endl << "Thanks for playing my game.\nRegards Rishabh gohel.";
}