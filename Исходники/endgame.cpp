int kxk_eval(const position_t *pos) {
  int winner = pos->material[WHITE]? WHITE : BLACK;
  int loser = winner^1;
  int result;

  result = (pos->material[winner] 
            + MateTable[KingSquare(pos, loser)]
            + DistanceBonus[DISTANCE(KingSquare(pos, winner), 
				     KingSquare(pos, loser))]);

  if(HasQueens(pos, winner) || HasRooks(pos, winner) ||
     pos->material[winner] >= 8*P_VALUE)
    result += KNOWN_WIN;

  return (winner == pos->side)? result : -result;
}