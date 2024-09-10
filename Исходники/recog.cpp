static bool kbpk_draw (int wp, int wb, int bk) {

   ASSERT(SQUARE_IS_OK(wp));
   ASSERT(SQUARE_IS_OK(wb));
   ASSERT(SQUARE_IS_OK(bk));

   if (SQUARE_FILE(wp) == FileA
    && DISTANCE(bk,A8) <= 1
    && SQUARE_COLOUR(wb) != SQUARE_COLOUR(A8)) {
      return true;
   }

   return false;
}