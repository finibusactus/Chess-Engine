#include "bitboard.hpp"
#include <iostream>

int main() {
  Bitboard board;
  board.makeMoveAndUpdateClassVaribles(Move(8, 24));
  board.printBoard();
  // std::cout << board.enPassantIndex;
  return 0;
}
