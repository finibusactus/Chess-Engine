#include "board.h"

int main() {
  Bitboard board;
  board.printBoard();
  board.makeMove(6, 21);
  board.printBoard();
  return 0;
}