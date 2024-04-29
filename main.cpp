#include "bitboard.h"
#include <iostream>

int main() {
  Bitboard board;
  board.printBoard();
  std::vector<Move> moves;
  std::cout << board.whitePawnEastCaptureStart() << '\n';
  std::cout << board.whitePawnWestCaptureStart() << '\n';
  std::cout << board.whitePawnEastCaptureTarget() << '\n';
  std::cout << board.whitePawnWestCaptureTarget() << '\n';
  board.addAllWhitePawnMoves(moves);
  for (Move move : moves) {
    std::cout << move.startIndex << "||" << move.endIndex << '\n';
  }
  board.printBoard();
  return 0;
}
