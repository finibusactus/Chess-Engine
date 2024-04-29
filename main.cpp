#include "bitboard.h"
#include <iostream>

int main() {
  Bitboard board;
  board.printBoard();
  std::vector<Move> moves;
  board.loadFENString(
      "rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq c6 0 2");
  std::cout << '\n';
  board.printBoard();
  return 0;
}
