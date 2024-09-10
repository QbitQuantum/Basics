bool piece_attack_king(const board_t * board, int piece, int from, int king) {

   const inc_t * inc_ptr;
   int code;
   const int * delta_ptr;
   int delta, inc;
   int to;
   int sq;

   ASSERT(board!=NULL);
   ASSERT(piece_is_ok(piece));
   ASSERT(SQUARE_IS_OK(from));
   ASSERT(SQUARE_IS_OK(king));

   inc_ptr = PIECE_INC(piece);

   code = PieceCode[piece];
   ASSERT(code>=0&&code<4);

   if (PIECE_IS_SLIDER(piece)) {

      for (delta_ptr = PieceDeltaDelta[code][DeltaOffset+(king-from)]; (delta=*delta_ptr) != DeltaNone; delta_ptr++) {

         ASSERT(delta_is_ok(delta));

         inc = DeltaIncLine[DeltaOffset+delta];
         ASSERT(inc!=IncNone);

         to = from + delta;

         sq = from;
         do {
            sq += inc;
         //   if (sq == to && SQUARE_IS_OK(to)) {
         //      ASSERT(DISTANCE(to,king)==1);
         //      return true; 
			if (DISTANCE(sq,king)<=2){
				  return true; 
			}
            
         } while (board->square[sq] == Empty);
      }

   } else { // non-slider

      for (delta_ptr = PieceDeltaDelta[code][DeltaOffset+(king-from)]; (delta=*delta_ptr) != DeltaNone; delta_ptr++) {

         ASSERT(delta_is_ok(delta));

         to = from + delta;

         if (SQUARE_IS_OK(to)) {
            ASSERT(DISTANCE(to,king)==1);
            return true;
         }
      }
   }

   return false;
}