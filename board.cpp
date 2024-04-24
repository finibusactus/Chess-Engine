#include "board.h"
#include <iostream>

Bitboard::Bitboard() {
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

void Bitboard::printBoard() {
  for (int i = 63; i >= 0; i--) {
    if (whitePawns[i]) {
      std::cout << "P";
    } else if (whiteRooks[i]) {
      std::cout << "R";
    } else if (whiteKnights[i]) {
      std::cout << "N";
    } else if (whiteBishops[i]) {
      std::cout << "B";
    } else if (whiteQueens[i]) {
      std::cout << "Q";
    } else if (whiteKing[i]) {
      std::cout << "K";
    } else if (blackPawns[i]) {
      std::cout << "p";
    } else if (blackRooks[i]) {
      std::cout << "r";
    } else if (blackKnights[i]) {
      std::cout << "n";
    } else if (blackBishops[i]) {
      std::cout << "b";
    } else if (blackQueens[i]) {
      std::cout << "q";
    } else if (blackKing[i]) {
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