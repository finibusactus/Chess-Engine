#include "board.h"
#include <bitset>
#include <iostream>

enum PieceNames {
  WHITE_PAWN,
  WHITE_ROOK,
  WHITE_KNIGHT,
  WHITE_BISHOP,
  WHITE_QUEEN,
  WHITE_KING,
  BLACK_PAWN,
  BLACK_ROOK,
  BLACK_KNIGHT,
  BLACK_BISHOP,
  BLACK_QUEEN,
  BLACK_KING
};

/* clang-format off */ 
// prevents clang-format from expandint this enum into 64 lines!
enum Squares {
  A8, A7, A6, A5, A4, A3, A2, A1, 
  B8, B7, B6, B5, B4, B3, B2, B1, 
  C8, C7, C6, C5, C4, C3, C2, C1, 
  D8, D7, D6, D5, D4, D3, D2, D1, 
  E8, E7, E6, E5, E4, E3, E2, E1, 
  F8, F7, F6, F5, F4, F3, F2, F1, 
  G8, G7, G6, G5, G4, G3, G2, G1,
  H8, H7, H6, H5, H4, H3, H2, H1
};
/* clang-format on */

struct {
  PieceNames pieceName;
  Squares originalSquare;
  Squares destSqure;
  PieceNames promotedPieceName;
} move;
Bitboard::Bitboard() {
  whiteToMove = true;

  whitePawns = 0x000000000000FF00;
  whiteRooks = 0x0000000000000081;
  whiteKnights = 0x0000000000000042;
  whiteBishops = 0x0000000000000024;
  whiteQueens = 0x0000000000000008;
  whiteKing = 0x0000000000000010;

  blackPawns = 0x00FF000000000000;
  blackRooks = 0x8100000000000000;
  blackKnights = 0x4200000000000000;
  blackBishops = 0x2400000000000000;
  blackQueens = 0x0800000000000000;
  blackKing = 0x1000000000000000;
};

std::bitset<64> moveNorth(const std::bitset<64> board) { return board << 8; }
std::bitset<64> moveSouth(const std::bitset<64> board) { return board >> 8; }

std::bitset<64> Bitboard::getOccupiedSquares() {
  return whitePawns | whiteRooks | whiteKnights | whiteBishops | whiteQueens |
         whiteKing | blackPawns | blackRooks | blackKnights | blackBishops |
         blackQueens | blackKing;
}
std::bitset<64> Bitboard::getEmptySqures() { return ~getOccupiedSquares(); }

std::bitset<64> Bitboard::whitePushSingleTarget() {
  return moveNorth(whitePawns) & getEmptySqures();
}
std::bitset<64> Bitboard::whitePushDoubleTarget() {
  const std::bitset<64> fourthRank = 0x00000000FF000000;
  const std::bitset<64> singlePushes = whitePushSingleTarget();
  return moveNorth(singlePushes) & getEmptySqures() & fourthRank;
}

std::bitset<64> Bitboard::blackPushSingleTarget() {
  return moveSouth(blackPawns) & getEmptySqures();
}
std::bitset<64> Bitboard::blackPushDoubleTarget() {
  const std::bitset<64> fifthRank = 0x000000FF00000000;
  const std::bitset<64> singlePushes = blackPushSingleTarget();
  return moveSouth(singlePushes) & getEmptySqures() & fifthRank;
}

void Bitboard::printBoard() {
  for (int i = 63; i >= 0; i--) {
    // We have to flip the bit to deal with endiness so it now goes, 56, 57,
    // 58, 59, 60, 61 62, 63, 48, 49, 50, 51, 52, 53, 54, 55, 40, 41, 42, ...
    int flipped = i ^ 7;
    if (whitePawns[flipped]) {
      std::cout << "P";
    } else if (whiteRooks[flipped]) {
      std::cout << "R";
    } else if (whiteKnights[flipped]) {
      std::cout << "N";
    } else if (whiteBishops[flipped]) {
      std::cout << "B";
    } else if (whiteQueens[flipped]) {
      std::cout << "Q";
    } else if (whiteKing[flipped]) {
      std::cout << "K";
    } else if (blackPawns[flipped]) {
      std::cout << "p";
    } else if (blackRooks[flipped]) {
      std::cout << "r";
    } else if (blackKnights[flipped]) {
      std::cout << "n";
    } else if (blackBishops[flipped]) {
      std::cout << "b";
    } else if (blackQueens[flipped]) {
      std::cout << "q";
    } else if (blackKing[flipped]) {
      std::cout << "k";
    } else {
      std::cout << " ";
    }
    if (i % 8 == 0) {
      std::cout << "\n";
    }
  }
  std::cout << std::endl;
  whitePawns = whitePushSingleTarget();
}