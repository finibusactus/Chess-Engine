#include "bitboard.hpp"
#include <array>
#include <bitset>
#include <cassert>
#include <functional>
#include <iostream>
#include <map>
#include <tuple>
#include <vector>

int returnIndexOfLSB(const std::bitset<64> bitboard) {
  for (int i = 0; i < 64; i++) {
    if (bitboard[i]) {
      return i;
    }
  }
  return -1;
}

int setZeroAndReturnIndexOfLSB(std::bitset<64> &bitboard) {
  int i = returnIndexOfLSB(bitboard);
  switch (i) {
  case -1:
    return -1;
  default:
    bitboard[i] = 0;
    return i;
  }
}

Bitboard::Bitboard() { restoreStartingChessPosition(); };

std::bitset<64> moveNorth(const std::bitset<64> board) { return board << 8; }
std::bitset<64> moveSouth(const std::bitset<64> board) { return board >> 8; }
std::bitset<64> moveEast(std::bitset<64> board) {
  std::bitset<64> notHFile = ~0x8080808080808080;
  return (board & notHFile) << 1;
}
std::bitset<64> moveWest(std::bitset<64> board) {
  std::bitset<64> notAFile = ~0x0101010101010101;
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
  return moveNorthWest(blackPawnEastCaptureTarget());
}
std::bitset<64> Bitboard::blackPawnWestCaptureStart() {
  return moveNorthEast(blackPawnWestCaptureTarget());
}

PieceNames Bitboard::nameOfPieceThatLiesOnSquare(int squareIndex) {
  if (whitePawns[squareIndex]) {
    return WHITE_PAWN;
  } else if (whiteRooks[squareIndex]) {
    return WHITE_ROOK;
  } else if (whiteKnights[squareIndex]) {
    return WHITE_KNIGHT;
  } else if (whiteBishops[squareIndex]) {
    return WHITE_BISHOP;
  } else if (whiteQueens[squareIndex]) {
    return WHITE_QUEEN;
  } else if (whiteKing[squareIndex]) {
    return WHITE_KING;
  } else if (blackPawns[squareIndex]) {
    return BLACK_PAWN;
  } else if (blackRooks[squareIndex]) {
    return BLACK_ROOK;
  } else if (blackKnights[squareIndex]) {
    return BLACK_KNIGHT;
  } else if (blackBishops[squareIndex]) {
    return BLACK_BISHOP;
  } else if (blackQueens[squareIndex]) {
    return BLACK_QUEEN;
  } else if (blackKing[squareIndex]) {
    return BLACK_KING;
  } else {
    return NONE;
  }
}
bool Bitboard ::isMoveDoublePawnPush(Move move) {
  if (whiteToMove) {
    if (not whitePawns[move.startIndex]) {
      return false;
    } else if (move.startIndex >= 8 && move.startIndex <= 15 &&
               move.endIndex >= 24 && move.endIndex <= 31) {
      return true;
    }
    return false;
  }
  if (not blackPawns[move.startIndex]) {
    return false;
  } else if (move.startIndex >= 48 && move.startIndex <= 55 &&
             move.endIndex >= 32 && move.endIndex <= 39) {
    return true;
  }
  return false;
}

bool Bitboard::isMoveEnPassant(Move move) {
  if (enPassantIndex == -1) {
    return false;
  }
  if (whiteToMove) {
    if (!whitePawns[move.startIndex]) {
      return false;
    } else if (enPassantIndex != move.endIndex) {
      return false;
    } else if ((move.endIndex - 7 == move.startIndex) |
               (move.endIndex - 9 == move.startIndex)) {
      return true;
    }
    return false;
  }
  if (!blackPawns[move.startIndex]) {
    return false;
  } else if (enPassantIndex != move.endIndex) {
    return false;
  } else if ((move.endIndex + 7 == move.startIndex) |
             (move.endIndex + 9 == move.startIndex)) {
    return true;
  }
  return false;
}
bool Bitboard::isMovePawnPromotion(Move move) {
  if (whiteToMove) {
    return whitePawns[move.startIndex] &&
           (move.startIndex >= 48 && move.startIndex <= 55);
  } else {
    return blackPawns[move.startIndex] &&
           (move.startIndex >= 8 && move.startIndex <= 15);
  }
}

bool isKingInCheckFromSlidingPieces(
    std::function<std::bitset<64>(std::bitset<64>)> func,
    std::bitset<64> kingBitboard, std::bitset<64> enemyPieces,
    std::bitset<64> ownPieces) {
  std::bitset<64> tmp = kingBitboard;
  for (int j = 0; j < 8; j++) {
    tmp = func(tmp);
    int LSBIndex = returnIndexOfLSB(tmp);
    if (LSBIndex == -1) {
      continue;
    }
    if (enemyPieces[LSBIndex]) {
      return true;
    } else if (ownPieces[LSBIndex]) {
      return false;
    }
  }
  return false;
}
bool Bitboard::inCheck(bool whiteSide) {
  if (whiteSide) {
    std::bitset<64> blackPawnAttackerSquares =
        (moveNorthEast(whiteKing) | moveNorthWest(whiteKing)) & blackPawns;
    if (returnIndexOfLSB(blackPawnAttackerSquares) != -1) {
      return true;
    }
    const std::array<std::tuple<int, int>, 8> possibleKnightMoves = {
        std::make_tuple<int, int>(-1, 2),  std::make_tuple<int, int>(1, 2),
        std::make_tuple<int, int>(2, 1),   std::make_tuple<int, int>(2, -1),
        std::make_tuple<int, int>(1, -2),  std::make_tuple<int, int>(-1, -2),
        std::make_tuple<int, int>(-2, -1), std::make_tuple<int, int>(-2, 1)};
    for (std::tuple<int, int> offset : possibleKnightMoves) {
      std::bitset<64> possibleStartSquare =
          moveAnyDirection(whiteKing, std::get<0>(offset), std::get<1>(offset));
      if (returnIndexOfLSB(possibleStartSquare & blackKnights) != -1) {
        return true;
      }
      if (isKingInCheckFromSlidingPieces(moveNorth, whiteKing,
                                         blackRooks | blackQueens,
                                         getEmptySqures())) {
        return true;
      }
      if (isKingInCheckFromSlidingPieces(moveEast, whiteKing,
                                         blackRooks | blackQueens,
                                         getEmptySqures())) {
        return true;
      }
      if (isKingInCheckFromSlidingPieces(moveSouth, whiteKing,
                                         blackRooks | blackQueens,
                                         getEmptySqures())) {
        return true;
      }
      if (isKingInCheckFromSlidingPieces(moveWest, whiteKing,
                                         blackRooks | blackQueens,
                                         getEmptySqures())) {
        return true;
      }
      if (isKingInCheckFromSlidingPieces(moveNorthEast, whiteKing,
                                         blackBishops | blackQueens,
                                         getEmptySqures())) {
        return true;
      }
      if (isKingInCheckFromSlidingPieces(moveNorthWest, whiteKing,
                                         blackBishops | blackQueens,
                                         getEmptySqures())) {
        return true;
      }
      if (isKingInCheckFromSlidingPieces(moveSouthEast, whiteKing,
                                         blackBishops | blackQueens,
                                         getEmptySqures())) {
        return true;
      }
      if (isKingInCheckFromSlidingPieces(moveSouthWest, whiteKing,
                                         blackBishops | blackQueens,
                                         getEmptySqures())) {
        return true;
      }
      if (returnIndexOfLSB(moveNorth(whiteKing) & blackKing) != -1) {
        return true;
      } else if (returnIndexOfLSB(moveEast(whiteKing) & blackKing) != -1) {
        return true;
      } else if (returnIndexOfLSB(moveSouth(whiteKing) & blackKing) != -1) {
        return true;
      } else if (returnIndexOfLSB(moveWest(whiteKing) & blackKing) != -1) {
        return true;
      } else if (returnIndexOfLSB(moveNorthEast(whiteKing) & blackKing) != -1) {
        return true;
      } else if (returnIndexOfLSB(moveNorthWest(whiteKing) & blackKing) != -1) {
        return true;
      } else if (returnIndexOfLSB(moveSouthEast(whiteKing) & blackKing) != -1) {
        return true;
      } else if (returnIndexOfLSB(moveSouthWest(whiteKing) & blackKing) != -1) {
        return true;
      }
    }
  } else {
    std::bitset<64> whitePawnAttackerSquares =
        (moveSouthEast(whiteKing) | moveSouthWest(whiteKing)) & blackPawns;
    if (returnIndexOfLSB(whitePawnAttackerSquares) != -1) {
      return true;
    }
    const std::array<std::tuple<int, int>, 8> possibleKnightMoves = {
        std::make_tuple<int, int>(-1, 2),  std::make_tuple<int, int>(1, 2),
        std::make_tuple<int, int>(2, 1),   std::make_tuple<int, int>(2, -1),
        std::make_tuple<int, int>(1, -2),  std::make_tuple<int, int>(-1, -2),
        std::make_tuple<int, int>(-2, -1), std::make_tuple<int, int>(-2, 1)};
    for (std::tuple<int, int> offset : possibleKnightMoves) {
      std::bitset<64> possibleStartSquare =
          moveAnyDirection(blackKing, std::get<0>(offset), std::get<1>(offset));
      if (returnIndexOfLSB(possibleStartSquare & whiteKnights) != -1) {
        return true;
      }
      if (isKingInCheckFromSlidingPieces(moveNorth, blackKing,
                                         whiteRooks | whiteQueens,
                                         getEmptySqures())) {
        return true;
      }
      if (isKingInCheckFromSlidingPieces(moveEast, blackKing,
                                         whiteRooks | whiteQueens,
                                         getEmptySqures())) {
        return true;
      }
      if (isKingInCheckFromSlidingPieces(moveSouth, blackKing,
                                         whiteRooks | whiteQueens,
                                         getEmptySqures())) {
        return true;
      }
      if (isKingInCheckFromSlidingPieces(moveWest, blackKing,
                                         whiteRooks | whiteQueens,
                                         getEmptySqures())) {
        return true;
      }
      if (isKingInCheckFromSlidingPieces(moveNorthEast, blackKing,
                                         whiteBishops | whiteQueens,
                                         getEmptySqures())) {
        return true;
      }
      if (isKingInCheckFromSlidingPieces(moveNorthWest, blackKing,
                                         whiteBishops | whiteQueens,
                                         getEmptySqures())) {
        return true;
      }
      if (isKingInCheckFromSlidingPieces(moveSouthEast, blackKing,
                                         whiteBishops | whiteQueens,
                                         getEmptySqures())) {
        return true;
      }
      if (isKingInCheckFromSlidingPieces(moveSouthWest, blackKing,
                                         whiteBishops | whiteQueens,
                                         getEmptySqures())) {
        return true;
      }
      if (returnIndexOfLSB(moveNorth(blackKing) & whiteKing) != -1) {
        return true;
      } else if (returnIndexOfLSB(moveEast(blackKing) & whiteKing) != -1) {
        return true;
      } else if (returnIndexOfLSB(moveSouth(blackKing) & whiteKing) != -1) {
        return true;
      } else if (returnIndexOfLSB(moveWest(blackKing) & whiteKing) != -1) {
        return true;
      } else if (returnIndexOfLSB(moveNorthEast(blackKing) & whiteKing) != -1) {
        return true;
      } else if (returnIndexOfLSB(moveNorthWest(blackKing) & whiteKing) != -1) {
        return true;
      } else if (returnIndexOfLSB(moveSouthEast(blackKing) & whiteKing) != -1) {
        return true;
      } else if (returnIndexOfLSB(moveSouthWest(blackKing) & whiteKing) != -1) {
        return true;
      }
    }
  }
  return false;
}

// Handles 1-1 eg. Pawn Push relationships and 1-many eg. knight attacks.
void addValidMovesToMoves(
    std::vector<Move> &moves, std::bitset<64> startBitboard,
    std::bitset<64> endBitboard, PieceNames promotedPieceName = NONE,
    std::function<PieceNames(int squareIndex)> func = [](int squareIndex) {
      return NONE;
    }) {
  std::bitset<64> tmp = endBitboard;
  std::bitset<64> tmp1 = startBitboard;
  if (setZeroAndReturnIndexOfLSB(tmp) == -1 ||
      setZeroAndReturnIndexOfLSB(tmp1) == -1) {
    return;
  }
  while (true) {
    int tmp = setZeroAndReturnIndexOfLSB(startBitboard);
    int startIndex = (tmp == -1 ? startIndex : tmp);
    int endIndex = setZeroAndReturnIndexOfLSB(endBitboard);
    if (tmp == -1 && endIndex == -1) {
      break;
    } else {
      moves.push_back(
          Move(startIndex, endIndex, promotedPieceName, func(endIndex)));
    }
  }
};

void Bitboard::addWhitePawnCaptureMoves(std::vector<Move> &moves) {
  addValidMovesToMoves(moves, whitePawnEastCaptureStart(),
                       whitePawnEastCaptureTarget(), NONE);
  addValidMovesToMoves(moves, whitePawnWestCaptureStart(),
                       whitePawnWestCaptureTarget());
}
void Bitboard::addBlackPawnCaptureMoves(std::vector<Move> &moves) {
  addValidMovesToMoves(moves, blackPawnEastCaptureStart(),
                       blackPawnEastCaptureTarget());
  addValidMovesToMoves(moves, blackPawnWestCaptureStart(),
                       blackPawnWestCaptureTarget());
}
void Bitboard::addWhiteEnPassantMoves(std::vector<Move> &moves) {
  if (enPassantIndex == -1) {
    return;
  }
  if (whitePawns[enPassantIndex - 7]) {
    moves.push_back(Move(enPassantIndex - 7, enPassantIndex));
  } else if (whitePawns[enPassantIndex - 9]) {
    moves.push_back(Move(enPassantIndex - 9, enPassantIndex));
  }
}
void Bitboard::addBlackEnPassantMoves(std::vector<Move> &moves) {
  if (enPassantIndex == -1) {
    return;
  }
  if (blackPawns[enPassantIndex - 7]) {
    moves.push_back(Move(enPassantIndex - 7, enPassantIndex));
  } else if (blackPawns[enPassantIndex - 9]) {
    moves.push_back(Move(enPassantIndex - 9, enPassantIndex));
  }
}

void Bitboard::addWhitePromotionMoves(std::vector<Move> &moves) {
  std::bitset<64> seventhRank = 0xFF000000000000;
  const std::bitset<64> pawnsAbleToPromoteTarget =
      moveNorth(whitePawns & seventhRank) & getEmptySqures();
  const std::bitset<64> pawnAbleToPromoteStart =
      moveSouth(pawnsAbleToPromoteTarget);
  addValidMovesToMoves(moves, pawnAbleToPromoteStart, pawnsAbleToPromoteTarget,
                       WHITE_ROOK);
  addValidMovesToMoves(moves, pawnAbleToPromoteStart, pawnsAbleToPromoteTarget,
                       WHITE_KNIGHT);
  addValidMovesToMoves(moves, pawnAbleToPromoteStart, pawnsAbleToPromoteTarget,
                       WHITE_BISHOP);
  addValidMovesToMoves(moves, pawnAbleToPromoteStart, pawnsAbleToPromoteTarget,
                       WHITE_QUEEN);
}
void Bitboard::addBlackPromotionMoves(std::vector<Move> &moves) {
  std::bitset<64> secondRank = 0xFF00;
  const std::bitset<64> pawnsAbleToPromoteTarget =
      moveSouth(whitePawns & secondRank) & getEmptySqures();
  const std::bitset<64> pawnAbleToPromoteStart =
      moveNorth(pawnsAbleToPromoteTarget);
  addValidMovesToMoves(moves, pawnAbleToPromoteStart, pawnsAbleToPromoteTarget,
                       BLACK_ROOK);
  addValidMovesToMoves(moves, pawnAbleToPromoteStart, pawnsAbleToPromoteTarget,
                       BLACK_KNIGHT);
  addValidMovesToMoves(moves, pawnAbleToPromoteStart, pawnsAbleToPromoteTarget,
                       BLACK_BISHOP);
  addValidMovesToMoves(moves, pawnAbleToPromoteStart, pawnsAbleToPromoteTarget,
                       BLACK_QUEEN);
}

void Bitboard::addAllWhitePawnMoves(std::vector<Move> &moves) {
  addValidMovesToMoves(moves, whitePawnPushSingleStart(),
                       whitePawnPushSingleTarget());
  addValidMovesToMoves(moves, whitePawnPushDoubleStart(),
                       whitePawnPushDoubleTarget());
  addWhitePawnCaptureMoves(moves);
  addWhiteEnPassantMoves(moves);
  for (Move move : moves) {
    if (isMovePawnPromotion(move)) {
      move.promotedPieceName = WHITE_QUEEN;
      moves.push_back(Move(move.startIndex, move.endIndex, WHITE_ROOK));
      moves.push_back(Move(move.startIndex, move.endIndex, WHITE_KNIGHT));
      moves.push_back(Move(move.startIndex, move.endIndex, WHITE_BISHOP));
      return;
    }
  }
}
void Bitboard::addAllBlackPawnMoves(std::vector<Move> &moves) {
  addValidMovesToMoves(moves, blackPawnPushSingleStart(),
                       blackPawnPushSingleTarget());
  addValidMovesToMoves(moves, blackPawnPushDoubleStart(),
                       blackPawnPushDoubleTarget());
  addBlackPawnCaptureMoves(moves);
  for (Move move : moves) {
    if (isMovePawnPromotion(move)) {
      move.promotedPieceName = BLACK_QUEEN;
      moves.push_back(Move(move.startIndex, move.endIndex, BLACK_ROOK));
      moves.push_back(Move(move.startIndex, move.endIndex, BLACK_KNIGHT));
      moves.push_back(Move(move.startIndex, move.endIndex, BLACK_BISHOP));
      return;
    }
  }
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
  }
}

void addMovesForSlidingPieces(
    std::vector<Move> &moves,
    std::function<std::bitset<64>(std::bitset<64>)> func,
    std::bitset<64> startBitboard, std::bitset<64> emptySquares,
    std::bitset<64> enemySquares) {
  std::bitset<64> ownSquares = ~(emptySquares | enemySquares);
  std::vector<int> arrayOfSlidingPieceIndexes;
  for (int i = 0; i < 64; i++) {
    if (startBitboard[i]) {
      arrayOfSlidingPieceIndexes.push_back(i);
    }
  }
  for (int i : arrayOfSlidingPieceIndexes) {
    std::bitset<64> pieceBitboard;
    pieceBitboard[i] = 1;
    for (int j = 0; j < 8; j++) {
      pieceBitboard = func(pieceBitboard);
      int LSBIndex = returnIndexOfLSB(pieceBitboard);
      if (ownSquares[LSBIndex]) {
        break;
      } else if (enemySquares[LSBIndex]) {
        moves.push_back(Move(i, LSBIndex));
        break;
      }
      moves.push_back(Move(i, LSBIndex));
    }
  }
};
void Bitboard::addAllBishopAndQueenDiagonalMoves(std::vector<Move> &moves) {
  auto addDiagonalMoves =
      [&](std::function<std::bitset<64>(std::bitset<64>)> func) {
        std::bitset<64> startBitboard = whiteBishops | whiteQueens;
        if (!whiteToMove) {
          startBitboard = blackBishops | blackQueens;
          addMovesForSlidingPieces(moves, func, startBitboard, getEmptySqures(),
                                   getWhitePieceSquares());
        }
        addMovesForSlidingPieces(moves, func, startBitboard, getEmptySqures(),
                                 getBlackPieceSquares());
      };
  addDiagonalMoves(moveNorthWest);
  addDiagonalMoves(moveNorthEast);
  addDiagonalMoves(moveSouthWest);
  addDiagonalMoves(moveSouthEast);
}
void Bitboard::addAllRookAndQueenHorizontalMoves(std::vector<Move> &moves) {
  auto addHorizontalMoves =
      [&](std::function<std::bitset<64>(std::bitset<64>)> func,
          std::function<std::bitset<64>(std::bitset<64>)> oppositeFunc) {
        std::bitset<64> startBitboard = whiteRooks | whiteQueens;
        std::bitset<64> safeSquares = ~getWhitePieceSquares();
        if (!whiteToMove) {
          startBitboard = blackRooks | blackQueens;
          safeSquares = ~getBlackPieceSquares();
        }
        addMovesForSlidingPieces(moves, func, startBitboard, getEmptySqures(),
                                 getBlackPieceSquares());
      };
  addHorizontalMoves(moveNorth, moveSouth);
  addHorizontalMoves(moveSouth, moveNorth);
  addHorizontalMoves(moveEast, moveWest);
  addHorizontalMoves(moveWest, moveEast);
}
void Bitboard::addAllKingMoves(std::vector<Move> &moves) {
  std::bitset<64> board;
  std::bitset<64> safeSquares;
  if (whiteToMove) {
    board = whiteKing;
    safeSquares = ~getWhitePieceSquares();
  } else {
    board = blackKing;
    safeSquares = ~getBlackPieceSquares();
  }
  std::bitset<64> tmp = board;
  setZeroAndReturnIndexOfLSB(tmp);
  // we should make sure that there is only one king: statement above deletes
  // the current king; statement below should return -1 to signify the board
  // is empty
  assert(setZeroAndReturnIndexOfLSB(tmp) == -1);
  std::bitset<64> availableMoves = moveNorth(board) | moveNorthEast(board) |
                                   moveSouthEast(board) | moveSouthWest(board) |
                                   moveNorthWest(board) | moveEast(board) |
                                   moveSouth(board) | moveWest(board);
  availableMoves &= safeSquares;
  addValidMovesToMoves(moves, board, availableMoves);
  if (whiteToMove) {
    if (whiteCastleEast) {
      if (inCheck(true)) {
        return;
      }
      whiteKing[4] = 0;
      whiteKing[3] = 1;
      if (inCheck(true)) {
        whiteKing[3] = 0;
        whiteKing[4] = 1;
        return;
      }
      whiteKing[3] = 0;
      whiteKing[2] = 1;
      if (inCheck(true)) {
        whiteKing[2] = 0;
        whiteKing[4] = 1;
        return;
      }
      moves.push_back(Move(4, 2));
      whiteKing[2] = 0;
      whiteKing[4] = 1;
    }
    if (whiteCastleWest) {
      if (inCheck(true)) {
        return;
      }
      whiteKing[4] = 0;
      whiteKing[5] = 1;
      if (inCheck(true)) {
        whiteKing[4] = 1;
        whiteKing[5] = 0;
        return;
      }
      whiteKing[5] = 0;
      whiteKing[6] = 1;
      if (inCheck(true)) {
        whiteKing[6] = 0;
        whiteKing[4] = 1;
        return;
      }
      moves.push_back(Move(4, 6));
      whiteKing[6] = 0;
      whiteKing[4] = 1;
    }
    return;
  }
  if (blackCastleEast) {
    if (inCheck(false)) {
      return;
    }
    blackKing[60] = 0;
    blackKing[59] = 1;
    if (inCheck(false)) {
      blackKing[59] = 0;
      blackKing[60] = 1;
      return;
    }
    blackKing[59] = 0;
    blackKing[58] = 1;
    if (inCheck(false)) {
      blackKing[58] = 0;
      blackKing[60] = 1;
      return;
    }
    moves.push_back(Move(60, 58));
    blackKing[58] = 0;
    blackKing[60] = 1;
  }
  if (blackCastleWest) {
    if (inCheck(false)) {
      return;
    }
    blackKing[60] = 0;
    blackKing[61] = 1;
    if (inCheck(false)) {
      blackKing[61] = 0;
      blackKing[60] = 1;
      return;
    }
    blackKing[61] = 0;
    blackKing[62] = 1;
    if (inCheck(false)) {
      blackKing[62] = 0;
      blackKing[60] = 1;
      return;
    }
    moves.push_back(Move(60, 62));
    blackKing[62] = 0;
    blackKing[60] = 1;
  }
}
void Bitboard::addAllMoves(std::vector<Move> &moves) {
  addAllPawnMoves(moves);
  addAllKnightMoves(moves);
  addAllBishopAndQueenDiagonalMoves(moves);
  addAllRookAndQueenHorizontalMoves(moves);
  addAllKingMoves(moves);
}

void Bitboard::makeMoveAndUpdateClassVaribles(Move move) {
  if (whiteKing[move.startIndex] && move.endIndex == 2 &&
      move.startIndex == 4 && whiteCastleEast) {
    whiteCastleEast = false;
    whiteCastleWest = false;
    whiteKing[move.startIndex] = 0;
    whiteKing[2] = 1;
    makeMoveAndUpdateClassVaribles(Move(0, 3));
  } else if (whiteKing[move.startIndex] && move.endIndex == 6 &&
             move.startIndex == 4 && whiteCastleWest) {
    whiteCastleEast = false;
    whiteCastleWest = false;
    whiteKing[move.startIndex] = 0;
    whiteKing[6] = 1;
    makeMoveAndUpdateClassVaribles(Move(7, 5));
  } else if (blackKing[move.startIndex] && move.endIndex == 58 &&
             move.startIndex == 60 && blackCastleEast) {
    blackCastleEast = false;
    blackCastleWest = false;
    blackKing[move.startIndex] = 0;
    blackKing[58] = 1;
    makeMoveAndUpdateClassVaribles(Move(56, 59));
  } else if (blackKing[move.startIndex] && move.endIndex == 62 &&
             move.startIndex == 60 && blackCastleWest) {
    blackCastleEast = false;
    blackCastleWest = false;
    blackKing[move.startIndex] = 0;
    blackKing[62] = 1;
    makeMoveAndUpdateClassVaribles(Move(63, 61));
  }
  if (whiteKing[move.startIndex]) {
    whiteCastleEast = false;
    whiteCastleWest = false;
  } else if (blackKing[move.startIndex]) {
    blackCastleEast = false;
    blackCastleWest = false;
  }
  if (whiteRooks[move.startIndex]) {
    if (move.startIndex == 0) {
      whiteCastleEast = false;
    } else if (move.startIndex == 7) {
      whiteCastleWest = false;
    }
  } else if (whiteRooks[move.endIndex]) {
    if (move.endIndex == 0) {
      whiteCastleEast = false;
    } else if (move.endIndex == 7) {
      whiteCastleWest = false;
    }
  }
  enPassantIndex = -1;
  if (isMoveDoublePawnPush(move)) {
    enPassantIndex = whiteToMove ? move.startIndex + 8 : move.startIndex - 8;
  }
  if (isMoveEnPassant(move)) {
    if (whiteToMove) {
      blackPawns[move.endIndex - 8] = 0;
    } else {
      whitePawns[move.endIndex - 8] = 0;
    }
  }
  whiteToMove = !whiteToMove;
  int startIndex = move.startIndex;
  int endIndex = move.endIndex;
  auto makeMoveForSpecificBitboard = [&](std::bitset<64> &bitboard) {
    bitboard[startIndex] = 0;
    bitboard[endIndex] = 1;
  };
  if (getOccupiedSquares()[endIndex]) {
    if (whitePawns[endIndex]) {
      whitePawns[endIndex] = 0;
    } else if (whiteRooks[endIndex]) {
      whiteRooks[endIndex] = 0;
    } else if (whiteKnights[endIndex]) {
      whiteKnights[endIndex] = 0;
    } else if (whiteBishops[endIndex]) {
      whiteBishops[endIndex] = 0;
    } else if (whiteQueens[endIndex]) {
      whiteQueens[endIndex] = 0;
    } else if (whiteKing[endIndex]) {
      whiteKing[endIndex] = 0;
    } else if (blackPawns[endIndex]) {
      blackPawns[endIndex] = 0;
    } else if (blackRooks[endIndex]) {
      blackRooks[endIndex] = 0;
    } else if (blackKnights[endIndex]) {
      blackKnights[endIndex] = 0;
    } else if (blackBishops[endIndex]) {
      blackBishops[endIndex] = 0;
    } else if (blackQueens[endIndex]) {
      blackQueens[endIndex] = 0;
    } else if (blackKing[endIndex]) {
      blackKing[endIndex] = 0;
    }
  }
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
  int nonFlippedInternalIndex = 63;
  int i = 0;
  do {
    int flippedInternalIndex = nonFlippedInternalIndex ^ 7;
    switch (FENString[i]) {
    case 'r':
      blackRooks[flippedInternalIndex] = 1;
      nonFlippedInternalIndex--;
      break;
    case 'n':
      blackKnights[flippedInternalIndex] = 1;
      nonFlippedInternalIndex--;
      break;
    case 'b':
      blackBishops[flippedInternalIndex] = 1;
      nonFlippedInternalIndex--;
      break;
    case 'q':
      blackQueens[flippedInternalIndex] = 1;
      nonFlippedInternalIndex--;
      break;
    case 'k':
      blackKing[flippedInternalIndex] = 1;
      nonFlippedInternalIndex--;
      break;
    case 'R':
      whiteRooks[flippedInternalIndex] = 1;
      nonFlippedInternalIndex--;
      break;
    case 'N':
      whiteKnights[flippedInternalIndex] = 1;
      nonFlippedInternalIndex--;
      break;
    case 'B':
      whiteBishops[flippedInternalIndex] = 1;
      nonFlippedInternalIndex--;
      break;
    case 'Q':
      whiteQueens[flippedInternalIndex] = 1;
      nonFlippedInternalIndex--;
      break;
    case 'p':
      blackPawns[flippedInternalIndex] = 1;
      nonFlippedInternalIndex--;
      break;
    case 'P':
      whitePawns[flippedInternalIndex] = 1;
      nonFlippedInternalIndex--;
      break;
    case 'K':
      whiteKing[flippedInternalIndex] = 1;
      nonFlippedInternalIndex--;
      break;
    case '/':
      break;
    case '1':
      nonFlippedInternalIndex -= 1;
      break;
    case '2':
      nonFlippedInternalIndex -= 2;
      break;
    case '3':
      nonFlippedInternalIndex -= 3;
      break;
    case '4':
      nonFlippedInternalIndex -= 4;
      break;
    case '5':
      nonFlippedInternalIndex -= 5;
      break;
    case '6':
      nonFlippedInternalIndex -= 6;
      break;
    case '7':
      nonFlippedInternalIndex -= 7;
      break;
    case '8':
      nonFlippedInternalIndex -= 8;
      break;
    default:
      throw "Invalid FEN String parsing";
    }
    i++;
  } while (FENString[i] != ' ');
  i++;
  whiteToMove = (FENString[i] == 'w');
  i += 2;
  while (FENString[i] != ' ') {
    switch (FENString[i]) {
    case 'Q':
      whiteCastleWest = true;
      break;
    case 'K':
      whiteCastleEast = true;
      break;
    case 'q':
      blackCastleWest = true;
      break;
    case 'k':
      blackCastleEast = true;
      break;
    default:
      throw "Invalid FEN String parsing";
    }
    i++;
  }
  std::map<std::string, int> mapping{
      {"a3", 16}, {"b3", 17}, {"c3", 18}, {"d3", 19}, {"e3", 20}, {"f3", 21},
      {"f3", 22}, {"g3", 23}, {"a6", 40}, {"b6", 41}, {"c6", 42}, {"d6", 43},
      {"e6", 44}, {"f6", 45}, {"f6", 46}, {"g6", 47}};
  for (auto square : mapping) {
    if (FENString.find(square.first) < 64) {
      enPassantIndex = square.second;
      return;
    }
  }
}
void Bitboard::clearAllData() {
  whiteToMove = true;
  whiteCastleWest = true;
  whiteCastleEast = true;
  blackCastleEast = true;
  blackCastleWest = true;
  enPassantIndex = true;

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

void Bitboard::restoreStartingChessPosition() {
  loadFENString("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
}