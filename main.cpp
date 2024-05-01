#include "bitboard.hpp"
#include <iostream>

int main() {
  Bitboard board;
  std::vector<Move> moves;
  board.loadFENString(
      "rn3bnr/ppp1pk2/2b1p1pp/8/8/6PN/PPPPPPqP/RNBQ1RK1 w - - 8 9");
  board.addAllMoves(moves);
  if (board.inCheck(false)) {
    std::cout << "Board is currently in check" << '\n';
  }
  std::cout << moves.size();
  // board.printBoard();
  return 0;
}
