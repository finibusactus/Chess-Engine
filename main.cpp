#include "bitboard.hpp"
#include <iostream>

int main() {
  Bitboard board;
  std::vector<Move> moves;
  board.loadFENString(
      "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - ");
  board.addAllMoves(moves);
  if (board.inCheck(true)) {
    std::cout << "I am in check\n";
  }
  for (Move move : moves) {
    std::cout << move.startIndex << "||" << move.endIndex << '\n';
  }
  board.printBoard();
  std::cout << moves.size() << '\n';
  return 0;
}