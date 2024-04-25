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
  A8=56, B8=57, C8=58, D8=59, E8=60, F8=61, G8=62, H8=63,
  A7=48, B7=49, C7=50, D7=51, E7=52, F7=53, G7=54, H7=55,
  A6=40, B6=41, C6=42, D6=43, E6=44, F6=45, G6=46, H6=47,
  A5=32, B5=33, C5=34, D5=35, E5=36, F5=37, G5=38, H5=39,
  A4=24, B4=25, C4=26, D4=27, E4=28, F4=29, G4=30, H4=31,
  A3=16, B3=17, C3=18, D3=19, E3=20, F3=21, G3=22, H3=23,
  A2=8,  B2=9,  C2=10, D2=11, E2=12, F2=13, G2=14, H2=15,
  A1=0,  b1=1,  C1=2,  D1=3,  E1=4,  F1=5,  g1=6,  H1=7 
};
/* clang-format on */

struct Move {
  PieceNames pieceName;
  Squares originalSquare;
  Squares destSquare;
  PieceNames promotedPieceName;
};

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

void Bitboard::makeMove(const Move *move) {
  std::cout << move->originalSquare << move->destSquare;
  std::cout << (move->originalSquare ^ move->destSquare);
  switch (move->pieceName) {
  case WHITE_PAWN:
    whitePawns ^= move->originalSquare ^ move->destSquare;
  case WHITE_ROOK:
    whiteRooks ^= move->originalSquare ^ move->destSquare;
  case WHITE_KNIGHT:
    whiteKnights ^= move->originalSquare ^ move->destSquare;
  case WHITE_BISHOP:
    whiteBishops ^= move->originalSquare ^ move->destSquare;
  case WHITE_QUEEN:
    whiteQueens ^= move->originalSquare ^ move->destSquare;
  case WHITE_KING:
    whiteKing ^= move->originalSquare ^ move->destSquare;
  case BLACK_PAWN:
    blackPawns ^= move->originalSquare ^ move->destSquare;
  case BLACK_ROOK:
    blackRooks ^= move->originalSquare ^ move->destSquare;
  case BLACK_KNIGHT:
    blackKnights ^= move->originalSquare ^ move->destSquare;
  case BLACK_BISHOP:
    blackBishops ^= move->originalSquare ^ move->destSquare;
  case BLACK_QUEEN:
    blackQueens ^= move->originalSquare ^ move->destSquare;
  case BLACK_KING:
    blackKing ^= move->originalSquare ^ move->destSquare;
    break;
  default:
    std::cout << "none";
  }
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
  Move move;
  move.pieceName = WHITE_PAWN;
  move.originalSquare = A2;
  move.destSquare = A4;
  makeMove(&move);
}