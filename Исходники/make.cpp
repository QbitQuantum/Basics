void unmakeMove(Move &move)
{
    unsigned int piece = move.getPiece();
    unsigned int captured = move.getCapture();
    unsigned int from = move.getFrom();
    unsigned int to = move.getTosq();

    Bitboard fromBitboard  = BITSET[from];
    Bitboard fromToBitboard = fromBitboard  | BITSET[to];

    switch (piece)
    {
        case 1: // white pawn:
            board.whitePawns           ^= fromToBitboard;
            board.whitePieces          ^= fromToBitboard;
            board.square[from]        = WHITE_PAWN;
            board.square[to]          = EMPTY;
            if (captured)
            {
                if (move.isEnpassant())
                {
                    board.blackPawns           ^= BITSET[to-8];
                    board.blackPieces          ^= BITSET[to-8];
                    board.occupiedSquares    ^= fromToBitboard | BITSET[to-8];
                    board.square[to-8]        = BLACK_PAWN;
                    board.totalBlackPawns     += PAWN_VALUE;
                    board.Material           -= PAWN_VALUE;
                }
                else
                {
                    unmakeCapture(captured, to);
                    board.occupiedSquares ^= fromBitboard;
                }
            }
            else board.occupiedSquares ^= fromToBitboard;

            if (move.isPromo())
            {
                unmakeWhitePromotion(move.getPromo(), to);
            }
            break;

        case 2: // white king:
            board.whiteKing             ^= fromToBitboard;
            board.whitePieces          ^= fromToBitboard;
            board.square[from]        = WHITE_KING;
            board.square[to]          = EMPTY;
            if (captured)
            {
                unmakeCapture(captured, to);
                board.occupiedSquares ^= fromBitboard;
            }
            else board.occupiedSquares ^= fromToBitboard;

            if (move.isCastle())
            {
                if (move.isCastleOO())
                {
                    board.whiteRooks         ^= BITSET[H1] | BITSET[F1];
                    board.whitePieces          ^= BITSET[H1] | BITSET[F1];
                    board.occupiedSquares    ^= BITSET[H1] | BITSET[F1];
                    board.square[H1]          = WHITE_ROOK;
                    board.square[F1]          = EMPTY;
                }
                else
                {
                    board.whiteRooks         ^= BITSET[A1] | BITSET[D1];
                    board.whitePieces          ^= BITSET[A1] | BITSET[D1];
                    board.occupiedSquares    ^= BITSET[A1] | BITSET[D1];
                    board.square[A1]          = WHITE_ROOK;
                    board.square[D1]          = EMPTY;
                }
            }
            break;

        case 3: // white knight:
            board.whiteKnights         ^= fromToBitboard;
            board.whitePieces          ^= fromToBitboard;
            board.square[from]        = WHITE_KNIGHT;
            board.square[to]          = EMPTY;
            if (captured)
            {
                unmakeCapture(captured, to);
                board.occupiedSquares ^= fromBitboard;
            }
            else board.occupiedSquares ^= fromToBitboard;
            break;

        case 5: // white bishop:
            board.whiteBishops         ^= fromToBitboard;
            board.whitePieces          ^= fromToBitboard;
            board.square[from]        = WHITE_BISHOP;
            board.square[to]          = EMPTY;
            if (captured)
            {
                unmakeCapture(captured, to);
                board.occupiedSquares ^= fromBitboard;
            }
            else board.occupiedSquares ^= fromToBitboard;

            break;

        case 6: // white rook:
            board.whiteRooks         ^= fromToBitboard;
            board.whitePieces          ^= fromToBitboard;
            board.square[from]        = WHITE_ROOK;
            board.square[to]          = EMPTY;
            if (captured)
            {
                unmakeCapture(captured, to);
                board.occupiedSquares ^= fromBitboard;
            }
            else board.occupiedSquares ^= fromToBitboard;
            break;

        case 7: // white queen:
            board.whiteQueens          ^= fromToBitboard;
            board.whitePieces          ^= fromToBitboard;
            board.square[from]        = WHITE_QUEEN;
            board.square[to]          = EMPTY;
            if (captured)
            {
                unmakeCapture(captured, to);
                board.occupiedSquares ^= fromBitboard;
            }
            else board.occupiedSquares ^= fromToBitboard;
            break;

        case 9: // black pawn:
            board.blackPawns           ^= fromToBitboard;
            board.blackPieces          ^= fromToBitboard;
            board.square[from]        = BLACK_PAWN;
            board.square[to]          = EMPTY;
            if (captured)
            {
                if (move.isEnpassant())
                {
                    board.whitePawns           ^= BITSET[to+8];
                    board.whitePieces          ^= BITSET[to+8];
                    board.occupiedSquares    ^= fromToBitboard | BITSET[to+8];
                    board.square[to+8]        = WHITE_PAWN;
                    board.totalWhitePawns     += PAWN_VALUE;
                    board.Material           += PAWN_VALUE;
                }
                else
                {
                    unmakeCapture(captured, to);
                    board.occupiedSquares ^= fromBitboard;
                }
            }
            else board.occupiedSquares ^= fromToBitboard;

            if (move.isPromo())
            {
                unmakeBlackPromotion(move.getPromo(), to);
            }
            break;

        case 10: // black king:
            board.blackKing             ^= fromToBitboard;
            board.blackPieces          ^= fromToBitboard;
            board.square[from]        = BLACK_KING;
            board.square[to]          = EMPTY;
            if (captured)
            {
                unmakeCapture(captured, to);
                board.occupiedSquares ^= fromBitboard;
            }
            else board.occupiedSquares ^= fromToBitboard;

            if (move.isCastle())
            {
                if (move.isCastleOO())
                {
                    board.blackRooks         ^= BITSET[H8] | BITSET[F8];
                    board.blackPieces          ^= BITSET[H8] | BITSET[F8];
                    board.occupiedSquares    ^= BITSET[H8] | BITSET[F8];
                    board.square[H8]          = BLACK_ROOK;
                    board.square[F8]          = EMPTY;
                }
                else
                {
                    board.blackRooks         ^= BITSET[A8] | BITSET[D8];
                    board.blackPieces          ^= BITSET[A8] | BITSET[D8];
                    board.occupiedSquares    ^= BITSET[A8] | BITSET[D8];
                    board.square[A8]          = BLACK_ROOK;
                    board.square[D8]          = EMPTY;
                }
            }
            break;

        case 11: // black knight:
            board.blackKnights         ^= fromToBitboard;
            board.blackPieces          ^= fromToBitboard;
            board.square[from]        = BLACK_KNIGHT;
            board.square[to]          = EMPTY;
            if (captured)
            {
                unmakeCapture(captured, to);
                board.occupiedSquares ^= fromBitboard;
            }
            else board.occupiedSquares ^= fromToBitboard;                  
            break;

        case 13: // black bishop:
            board.blackBishops         ^= fromToBitboard;
            board.blackPieces          ^= fromToBitboard;
            board.square[from]        = BLACK_BISHOP;
            board.square[to]          = EMPTY;
            if (captured)
            {
                unmakeCapture(captured, to);
                board.occupiedSquares ^= fromBitboard;
            }
            else board.occupiedSquares ^= fromToBitboard;                  
            break;

        case 14: // black rook:
            board.blackRooks         ^= fromToBitboard;
            board.blackPieces          ^= fromToBitboard;
            board.square[from]        = BLACK_ROOK;
            board.square[to]          = EMPTY;
            if (captured)
            {
                unmakeCapture(captured, to);
                board.occupiedSquares ^= fromBitboard;
            }
            else board.occupiedSquares ^= fromToBitboard;                  
            break;

        case 15: // black queen:
            board.blackQueens          ^= fromToBitboard;
            board.blackPieces          ^= fromToBitboard;
            board.square[from]        = BLACK_QUEEN;
            board.square[to]          = EMPTY;
            if (captured)
            {
                unmakeCapture(captured, to);
                board.occupiedSquares ^= fromBitboard;
            }
            else board.occupiedSquares ^= fromToBitboard;                  
            break;
    }

    board.nextMove = !board.nextMove;

    board.endOfSearch--;
    board.castleWhite         = board.gameLine[board.endOfSearch].castleWhite;
    board.castleBlack         = board.gameLine[board.endOfSearch].castleBlack;
    board.epSquare            = board.gameLine[board.endOfSearch].epSquare;
    board.fiftyMove           = board.gameLine[board.endOfSearch].fiftyMove;
    board.hashkey             = board.gameLine[board.endOfSearch].key; 
}