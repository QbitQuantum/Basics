       bool capture_is_good(int move, const board_t * board, bool in_pv) {
#else
static bool capture_is_good(int move, const board_t * board, bool in_pv) {
#endif

   int piece, capture;
   int see_value; // WHM 11/22/08

   ASSERT(move_is_ok(move));
   ASSERT(board!=NULL);

   ASSERT(move_is_tactical(move,board));

   // special cases

   if (MOVE_IS_EN_PASSANT(move)) return true;
   if (move_is_under_promote(move)) return false; // REMOVE ME?  Keep, looks good to me.  WHM;
// if (MOVE_IS_PROMOTE(move)) return true; // WHM; promote-to-queen, measures a little weaker
//                                                 too many garbage lines going nuts.
   
   // captures and queen promotes
   capture = board->square[MOVE_TO(move)];
   piece = board->square[MOVE_FROM(move)];

   if (capture != Empty) {

      // capture

      ASSERT(move_is_capture(move,board));

      if (MOVE_IS_PROMOTE(move)) return true; // capture a piece on Rank8 and promote to queen
      
      if (VALUE_PIECE(capture) >= VALUE_PIECE(piece)) return true;
   }


// return see_move(move,board) >= 0; WHM 11/22/08

// WHM 11/22/08 START

   see_value = see_move(move,board);
   if (see_value >= 0) return true;

   if (TryNodePVQueenPromotes) {
      if (in_pv && MOVE_IS_PROMOTE(move)) {
          ASSERT(!move_is_under_promote(move));
          return true; // WHM:
      }
   }
   
   if (TryKingAttackSacs || TryKingBoxSacs || TryPasserSacs) {
      if (in_pv  &&  see_value > -ValueBishop  &&  capture != Empty) {
         ASSERT(COLOUR_IS(capture,COLOUR_OPP(board->turn)));
         // king attack sacs.  
         if (TryKingAttackSacs) {
            if (narrow_piece_attack_king(board, piece, MOVE_TO(move), KING_POS(board,COLOUR_OPP(board->turn)))) {
               return true;
            }
         }
         // sacrifice attacks around the narrow/close king box can be examined more fully.  Rybka lessons.  
         if (TryKingBoxSacs) {
            if (DISTANCE(MOVE_TO(move),KING_POS(board,COLOUR_OPP(board->turn))) <= 1) {
               return true;
            }
         }
         // passer sacrifices...
         if (TryPasserSacs) {
            if (PIECE_IS_PAWN(capture) && PAWN_RANK(MOVE_TO(move),COLOUR_OPP(board->turn)) >= Rank6) {
               return true;
            }
         }
      }
   } // WHM 11/22/08 END
   
   
   return false;
}