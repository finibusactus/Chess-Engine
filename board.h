#ifndef BOARD_HPP
#define BOARD_HPP

#include <bitset>

struct Move;

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

  std::bitset<64> whitePushSingleTarget();
  std::bitset<64> whitePushDoubleTarget();

  std::bitset<64> blackPushSingleTarget();
  std::bitset<64> blackPushDoubleTarget();

  void makeMove(const Move *move);
};
#endif