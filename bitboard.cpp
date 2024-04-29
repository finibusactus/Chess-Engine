#include "bitboard.h"
#include <array>
#include <bitset>
#include <cctype>
#include <iostream>
#include <tuple>
#include <vector>

int setZeroAndReturnIndexOfLSB(std::bitset<64> &bitboard) {
  for (int i = 0; i < 64; i++) {
    if (bitboard[i]) {
      bitboard[i] = 0;
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

std::bitset<64> notAFile = ~0x0101010101010101;
std::bitset<64> notHFile = ~0x8080808080808080;
std::bitset<64> moveNorth(const std::bitset<64> board) { return board << 8; }
std::bitset<64> moveSouth(const std::bitset<64> board) { return board >> 8; }
std::bitset<64> moveEast(std::bitset<64> board) {
  return (board & notHFile) << 1;
}
std::bitset<64> moveWest(std::bitset<64> board) {
  return (board & notAFile) >> 1;
}
std::bitset<64> moveSouthEast(std::bitset<64> board) {
  return moveEast(moveSouth(board));
}
std::bitset<64> moveSouthWest(std::bitset<64> board) {
  return moveWest(moveSouth(board));
}
std::bitset<64> moveNorthEast(std::bitset<64> board) {
  return moveEast(moveNorth(board));
}
std::bitset<64> moveNorthWest(std::bitset<64> board) {
  return moveWest(moveNorth(board));
}
std::bitset<64> moveAnyDirection(std::bitset<64> board, int xTranslation,
                                 int yTranslation) {
  while (xTranslation) {
    if (xTranslation > 0) {
      xTranslation--;
      board = moveWest(board);
    } else {
      xTranslation++;
      board = moveEast(board);
    };
  }
  while (yTranslation) {
    if (yTranslation > 0) {
      yTranslation--;
      board = moveSouth(board);
    } else {
      yTranslation++;
      board = moveNorth(board);
    }
  }
  return board;
}
std::bitset<64> Bitboard::getWhitePieceSquares() {
  return whitePawns | whiteRooks | whiteKnights | whiteBishops | whiteQueens |
         whiteKing;
}
std::bitset<64> Bitboard::getBlackPieceSquares() {
  return blackPawns | blackRooks | blackKnights | blackBishops | blackQueens |
         blackKing;
}
std::bitset<64> Bitboard::getOccupiedSquares() {
  return getWhitePieceSquares() | getBlackPieceSquares();
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
  return moveSouth(moveSouth(whitePawnPushDoubleTarget()));
}
std::bitset<64> Bitboard::whitePawnEastCaptureTarget() {
  return moveNorthEast(whitePawns) & getBlackPieceSquares();
}
std::bitset<64> Bitboard::whitePawnWestCaptureTarget() {
  return moveNorthWest(whitePawns) & getBlackPieceSquares();
}
std::bitset<64> Bitboard::whitePawnEastCaptureStart() {
  return moveSouthWest(whitePawnEastCaptureTarget());
}
std::bitset<64> Bitboard::whitePawnWestCaptureStart() {
  return moveSouthEast(whitePawnWestCaptureTarget());
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
  return moveNorth(moveNorth(blackPawnPushDoubleTarget()));
}
std::bitset<64> Bitboard::blackPawnEastCaptureTarget() {
  return moveSouthEast(blackPawns) & getWhitePieceSquares();
}
std::bitset<64> Bitboard::blackPawnWestCaptureTarget() {
  return moveSouthWest(blackPawns) & getWhitePieceSquares();
}
std::bitset<64> Bitboard::blackPawnEastCaptureStart() {
  return moveSouthWest(blackPawnEastCaptureTarget());
}
std::bitset<64> Bitboard::blackPawnWestCaptureStart() {
  return moveSouthEast(blackPawnWestCaptureTarget());
}

// Handles 1-1 eg. Pawn Push relationships and 1-many eg. knight attacks.
void addValidMovesToMoves(std::vector<Move> &moves,
                          std::bitset<64> startBitboard,
                          std::bitset<64> endBitboard) {
  while (true) {
    int tmp = setZeroAndReturnIndexOfLSB(startBitboard);
    int startIndex = (tmp == -1 ? startIndex : tmp);
    int endIndex = setZeroAndReturnIndexOfLSB(endBitboard);
    if (tmp == -1 && endIndex == -1) {
      break;
    } else {
      moves.push_back(Move(startIndex, endIndex));
    }
  }
};

void Bitboard::addWhitePawnCaptureMoves(std::vector<Move> &moves) {
  addValidMovesToMoves(moves, whitePawnEastCaptureStart(),
                       whitePawnEastCaptureTarget());
  addValidMovesToMoves(moves, whitePawnWestCaptureStart(),
                       whitePawnWestCaptureTarget());
}
void Bitboard::addBlackPawnCaptureMoves(std::vector<Move> &moves) {
  addValidMovesToMoves(moves, blackPawnEastCaptureStart(),
                       blackPawnEastCaptureTarget());
  addValidMovesToMoves(moves, blackPawnWestCaptureStart(),
                       blackPawnWestCaptureTarget());
}

void Bitboard::addAllWhitePawnMoves(std::vector<Move> &moves) {
  addValidMovesToMoves(moves, whitePawnPushSingleStart(),
                       whitePawnPushSingleTarget());
  addValidMovesToMoves(moves, whitePawnPushDoubleStart(),
                       whitePawnPushDoubleTarget());
  addValidMovesToMoves(moves, whitePawnEastCaptureStart(),
                       whitePawnEastCaptureTarget());
  addValidMovesToMoves(moves, whitePawnWestCaptureStart(),
                       whitePawnWestCaptureTarget());
}
void Bitboard::addAllBlackPawnMoves(std::vector<Move> &moves) {
  addValidMovesToMoves(moves, blackPawnPushSingleStart(),
                       blackPawnPushSingleTarget());
  addValidMovesToMoves(moves, blackPawnPushDoubleStart(),
                       blackPawnPushDoubleTarget());
  addValidMovesToMoves(moves, blackPawnEastCaptureStart(),
                       blackPawnEastCaptureTarget());
  addValidMovesToMoves(moves, blackPawnWestCaptureStart(),
                       blackPawnWestCaptureTarget());
}

void Bitboard::addAllPawnMoves(std::vector<Move> &moves) {
  if (whiteToMove) {
    addAllWhitePawnMoves(moves);
  } else {
    addAllBlackPawnMoves(moves);
  }
}

void Bitboard::addAllKnightMoves(std::vector<Move> &moves) {
  const std::array<std::tuple<int, int>, 8> possibleKnightMoves = {
      std::make_tuple<int, int>(-1, 2),  std::make_tuple<int, int>(1, 2),
      std::make_tuple<int, int>(2, 1),   std::make_tuple<int, int>(2, -1),
      std::make_tuple<int, int>(1, -2),  std::make_tuple<int, int>(-1, -2),
      std::make_tuple<int, int>(-2, -1), std::make_tuple<int, int>(-2, 1)};
  std::bitset<64> knightsBitboard = whiteKnights;
  if (!whiteToMove) {
    knightsBitboard = blackKnights;
  }
  for (std::tuple<int, int> translation : possibleKnightMoves) {
    std::bitset<64> targetBitboard = moveAnyDirection(
        knightsBitboard, std::get<0>(translation), std::get<1>(translation));
    std::cout << targetBitboard << "||" << knightsBitboard << 1 << '\n';
    std::cout << std::get<0>(translation) << std::get<1>(translation) << '\n';
    if (whiteToMove) {
      targetBitboard &= ~getWhitePieceSquares();
    } else {
      targetBitboard &= ~getBlackPieceSquares();
    }
    addValidMovesToMoves(moves,
                         moveAnyDirection(targetBitboard,
                                          -std::get<0>(translation),
                                          -std::get<1>(translation)),
                         targetBitboard);
    std::cout << targetBitboard << "||" << knightsBitboard << 2 << '\n';
  }
}

void Bitboard::addAllBishopAndQueenDiagonalMoves(std::vector<Move> &moves) {
  std::bitset<64> startBitboard = whiteBishops | whiteQueens;
  if (!whiteToMove) {
    startBitboard = blackBishops | blackQueens;
  }
  std::bitset<64> targetBitboard = startBitboard;
  for (int i = 0; i < 8; i++) {
    targetBitboard = moveNorthWest(targetBitboard);
    if (whiteToMove) {
      targetBitboard &= ~getWhitePieceSquares();
    } else {
      targetBitboard &= ~getBlackPieceSquares();
    }
    addValidMovesToMoves(moves, moveSouthEast(targetBitboard), targetBitboard);
  }
}

void Bitboard::makeMoveAndUpdateClassVaribles(Move move) {
  whiteToMove = !whiteToMove;
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
}

void Bitboard::loadFENString(std::string FENString) {
  clearAllData();
  int currentIndex = 63;
  int flippedInternalIndex = currentIndex ^ 7;
  for (char ch : FENString) {
    while (currentIndex >= 0) {
      if (ch == '/') {
        currentIndex++;
        break;
      } else if (ch == ' ') {
        break;
      }
      if (isdigit(ch) && ch != ' ') {
        std::cout << "I am a digit" << currentIndex;
        currentIndex -= ch;
      } else {
        std::cout << ch << "||" << flippedInternalIndex;
        switch (ch) {
        case 'r':
          blackRooks[flippedInternalIndex] = 1;
          break;
        case 'n':
          blackKnights[flippedInternalIndex] = 1;
          break;
        case 'b':
          blackBishops[flippedInternalIndex] = 1;
          break;
        case 'q':
          blackQueens[flippedInternalIndex] = 1;
          break;
        case 'k':
          blackKing[flippedInternalIndex] = 1;
          break;
        case 'R':
          whiteRooks[flippedInternalIndex] = 1;
          break;
        case 'N':
          whiteKnights[flippedInternalIndex] = 1;
          break;
        case 'B':
          whiteBishops[flippedInternalIndex] = 1;
          break;
        case 'Q':
          whiteQueens[flippedInternalIndex] = 1;
          break;
        case 'K':
          whiteKing[flippedInternalIndex] = 1;
        }
        currentIndex--;
      }
      flippedInternalIndex = currentIndex ^ 7;
      break;
    }
    if (currentIndex > 0) {
      continue;
    }
    whiteToMove = ch == 'w';
    switch (ch) { break; }
  }
}
void Bitboard::clearAllData() {
  whiteToMove = true;

  whitePawns.reset();
  whiteRooks.reset();
  whiteKnights.reset();
  whiteBishops.reset();
  whiteQueens.reset();
  whiteKing.reset();

  blackPawns.reset();
  blackRooks.reset();
  blackKnights.reset();
  blackBishops.reset();
  blackQueens.reset();
  blackKing.reset();
}