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

/*
No functions in this class carry side effects EXCEPT those clearly listed eg.
makeMoveAndUpdateClassVariables(Move move);

Some implementation functions will modify parameters but these should also be
clealy listed by void func(&parameter), these functions tend to be more local in
scope, otherwise a more declarative name is needed*/
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

  std::vector<Move> returnAllWhitePawnMoves();
  std::vector<Move> returnAllBlackPawnMoves();
  // Not implemented, it currently returns all moves; regardless of validity.
  std::vector<Move> returnAllValidPawnMoves();

  void makeMoveAndUpdateClassVaribles(Move move);
};
#endif
