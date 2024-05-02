#include "bitboard.hpp"
#include <iostream>

int main() {
  Bitboard board;
  std::vector<Move> moves;
  board.loadFENString(
      "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - ");
  board.addAllMoves(moves);
  std::cout << moves.size();
  board.printBoard();
  return 0;
}
