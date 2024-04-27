#ifndef BOARD_HPP
#define BOARD_HPP

#include <array>
#include <bitset>
#include <vector>

struct Move {
  int startIndex;
  int endIndex;
  Move(int startIndex, int endIndex) {
    this->startIndex = startIndex;
    this->endIndex = endIndex;
  }
};

class Bitboard {
public:
  Bitboard();
  void printBoard();

private:
  bool whiteToMove;

  std::bitset<64> whitePawns;
  std::bitset<64> whiteRooks;
  std::bitset<64> whiteKnights;
  std::bitset<64> whiteBishops;
  std::bitset<64> whiteQueens;
  std::bitset<64> whiteKing;

  std::bitset<64> blackPawns;
  std::bitset<64> blackRooks;
  std::bitset<64> blackKnights;
  std::bitset<64> blackBishops;
  std::bitset<64> blackQueens;
  std::bitset<64> blackKing;

  std::bitset<64> getOccupiedSquares();
  std::bitset<64> getEmptySqures();

  std::bitset<64> whitePawnPushSingleTarget();
  std::bitset<64> whitePawnPushDoubleTarget();
  std::bitset<64> whitePawnPushSingleStart();
  std::bitset<64> whitePawnPushDoubleStart();

  std::bitset<64> blackPawnPushSingleTarget();
  std::bitset<64> blackPawnPushDoubleTarget();
  std::bitset<64> blackPawnPushSingleStart();
  std::bitset<64> blackPawnPushDoubleStart();

  std::vector<Move> moves;
  void generatePawnMoves();

  void makeMove(Move move);
};
#endif