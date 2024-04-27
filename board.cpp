#include "board.h"
#include <bitset>
#include <iostream>

int setZeroAndReturnIndexOfLSB(std::bitset<64> &bitboard) {
  for (int i = 0; i < 64; i++) {
    if (bitboard[i]) {
      bitboard[i] = 1;
      return i;
    }
  }
  return -1;
}

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

std::bitset<64> Bitboard::whitePawnPushSingleTarget() {
  return moveNorth(whitePawns) & getEmptySqures();
}
std::bitset<64> Bitboard::whitePawnPushDoubleTarget() {
  const std::bitset<64> fourthRank = 0x00000000FF000000;
  const std::bitset<64> singlePushes = whitePawnPushSingleTarget();
  return moveNorth(singlePushes) & getEmptySqures() & fourthRank;
}
std::bitset<64> Bitboard::whitePawnPushSingleStart() {
  return moveSouth(whitePawnPushSingleTarget());
}
std::bitset<64> Bitboard::whitePawnPushDoubleStart() {
  return moveSouth(whitePawnPushDoubleTarget());
}

std::bitset<64> Bitboard::blackPawnPushSingleTarget() {
  return moveSouth(blackPawns) & getEmptySqures();
}
std::bitset<64> Bitboard::blackPawnPushDoubleTarget() {
  const std::bitset<64> fifthRank = 0x000000FF00000000;
  const std::bitset<64> singlePushes = blackPawnPushSingleTarget();
  return moveSouth(singlePushes) & getEmptySqures() & fifthRank;
}
std::bitset<64> Bitboard::blackPawnPushSingleStart() {
  return moveNorth(blackPawnPushSingleTarget());
}
std::bitset<64> Bitboard::blackPawnPushDoubleStart() {
  return moveNorth(blackPawnPushDoubleTarget());
}

void Bitboard::generatePawnMoves() {
  std::bitset<64> whitePawnStart = whitePawnPushDoubleStart();
  std::bitset<64> whitePawnTarget = whitePawnPushDoubleTarget();
  setZeroAndReturnIndexOfLSB(whitePawnStart);
  setZeroAndReturnIndexOfLSB(whitePawnStart);
}

void Bitboard::makeMove(Move move) {
  int startIndex = move.startIndex;
  int endIndex = move.endIndex;
  auto makeMoveForSpecificBitboard = [&](std::bitset<64> &bitboard) {
    bitboard[startIndex] = 0;
    bitboard[endIndex] = 1;
  };
  if (whitePawns[startIndex]) {
    makeMoveForSpecificBitboard(whitePawns);
  } else if (whiteRooks[startIndex]) {
    makeMoveForSpecificBitboard(whiteRooks);
  } else if (whiteKnights[startIndex]) {
    makeMoveForSpecificBitboard(whiteKnights);
  } else if (whiteBishops[startIndex]) {
    makeMoveForSpecificBitboard(whiteBishops);
  } else if (whiteQueens[startIndex]) {
    makeMoveForSpecificBitboard(whiteQueens);
  } else if (whiteKing[startIndex]) {
    makeMoveForSpecificBitboard(whiteKing);
  } else if (blackPawns[startIndex]) {
    makeMoveForSpecificBitboard(blackPawns);
  } else if (blackRooks[startIndex]) {
    makeMoveForSpecificBitboard(blackRooks);
  } else if (blackKnights[startIndex]) {
    makeMoveForSpecificBitboard(blackKnights);
  } else if (blackBishops[startIndex]) {
    makeMoveForSpecificBitboard(blackBishops);
  } else if (blackQueens[startIndex]) {
    makeMoveForSpecificBitboard(blackQueens);
  } else if (blackKing[startIndex]) {
    makeMoveForSpecificBitboard(blackKing);
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
}