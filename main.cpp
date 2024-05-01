#include "bitboard.hpp"
#include <iostream>

int main() {
  Bitboard board;
  std::vector<Move> moves;
  board.loadFENString("r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/"
                      "R4RK1 w - - 0 10 ");
  board.addAllMoves(moves);
  std::cout << moves.size();
  // board.printBoard();
  return 0;
}
