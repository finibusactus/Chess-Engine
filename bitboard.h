#ifndef BOARD_H
#define BOARD_H

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
clealy listed by void func(&parameter) eg.
addAllPawnMoves(std::vector<Move> &moves) */
class Bitboard {
public:
  Bitboard();
  void printBoard();

public:
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

  std::bitset<64> getWhitePieceSquares();
  std::bitset<64> getBlackPieceSquares();
  std::bitset<64> getOccupiedSquares();
  std::bitset<64> getEmptySqures();

  std::bitset<64> whitePawnPushSingleTarget();
  std::bitset<64> whitePawnPushDoubleTarget();
  std::bitset<64> whitePawnPushSingleStart();
  std::bitset<64> whitePawnPushDoubleStart();
  std::bitset<64> whitePawnEastCaptureTarget();
  std::bitset<64> whitePawnWestCaptureTarget();
  std::bitset<64> whitePawnEastCaptureStart();
  std::bitset<64> whitePawnWestCaptureStart();

  std::bitset<64> blackPawnPushSingleTarget();
  std::bitset<64> blackPawnPushDoubleTarget();
  std::bitset<64> blackPawnPushSingleStart();
  std::bitset<64> blackPawnPushDoubleStart();
  std::bitset<64> blackPawnEastCaptureTarget();
  std::bitset<64> blackPawnWestCaptureTarget();
  std::bitset<64> blackPawnEastCaptureStart();
  std::bitset<64> blackPawnWestCaptureStart();

  void addWhitePawnCaptureMoves(std::vector<Move> &moves);
  void addBlackPawnCaptureMoves(std::vector<Move> &moves);
  void addAllWhitePawnMoves(std::vector<Move> &moves);
  void addAllBlackPawnMoves(std::vector<Move> &moves);

  void addAllPawnMoves(std::vector<Move> &moves);
  void addAllKnightMoves(std::vector<Move> &moves);
  void makeMoveAndUpdateClassVaribles(Move move);
};
#endif
