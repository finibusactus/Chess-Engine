#ifndef BOARD_HPP
#define BOARD_HPP

#include <bitset>
#include <vector>

enum PieceNames {
  WHITE_ROOK,
  WHITE_KNIGHT,
  WHITE_BISHOP,
  WHITE_QUEEN,
  WHITE_KING,
  BLACK_ROOK,
  BLACK_KNIGHT,
  BLACK_BISHOP,
  BLACK_QUEEN,
  BLACK_KING,
  NONE
};

struct Move {
  int startIndex;
  int endIndex;
  PieceNames promotedPieceName;
  PieceNames capturedPieceName;
  bool isMoveEnPasssant;
  Move(int _startIndex, int _endIndex, PieceNames _promotedPieceName = NONE,
       PieceNames _capturedPieceName = NONE, bool _isMoveEnPassant = false)
      : startIndex(_startIndex), endIndex(_endIndex),
        promotedPieceName(_promotedPieceName),
        capturedPieceName(_capturedPieceName),
        isMoveEnPasssant(_isMoveEnPassant) {}
};

/*
Some functions may change class variables eg.
makeMoveAndUpdateClassVariables(Move move).
NOTE: some functions to calcualate moves and search will DEPEND (unpure) on
class variables such as whiteToMove etc. (mostly functions such as
addAllPawnMoves and search))

Some implementation functions will modify parameters but these should also be
clealy listed by void func(&parameter) eg.
addAllPawnMoves(std::vector<Move> &moves) */
class Bitboard {
public:
  Bitboard();
  void printBoard();
  void loadFENString(std::string FENString);

public:
  bool whiteToMove;
  bool whiteCastleWest;
  bool whiteCastleEast;
  bool blackCastleEast;
  bool blackCastleWest;
  int enPassantIndex;

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

  // These functions do not handle promotions and do not return anything for a
  // pawn on the 7th / 2nd rank promoting.
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

  bool isMoveDoublePawnPush(Move move);
  bool isMoveEnPassant(Move move);
  bool isMovePawnPromotion(Move move);
  bool inCheck(bool whiteSide);

  void addWhitePawnCaptureMoves(std::vector<Move> &moves);
  void addBlackPawnCaptureMoves(std::vector<Move> &moves);
  void addWhiteEnPassantMoves(std::vector<Move> &moves);
  void addBlackEnPassantMoves(std::vector<Move> &moves);
  void addWhitePromotionMoves(std::vector<Move> &moves);
  void addBlackPromotionMoves(std::vector<Move> &moves);

  void addAllWhitePawnMoves(std::vector<Move> &moves);
  void addAllBlackPawnMoves(std::vector<Move> &moves);

  void addAllPawnMoves(std::vector<Move> &moves);
  void addAllKnightMoves(std::vector<Move> &moves);
  void addAllBishopAndQueenDiagonalMoves(std::vector<Move> &moves);
  void addAllRookAndQueenHorizontalMoves(std::vector<Move> &moves);
  void addAllKingMoves(std::vector<Move> &moves);
  void addAllMoves(std::vector<Move> &moves);
  void makeMoveAndUpdateClassVaribles(Move move);

  void clearAllData();
  void restoreStartingChessPosition();
};
#endif
