bool GameState::canMove(const pos& i_s,const pos& j_s,const pos& i_f,const pos& j_f) const {
	if(!gameStarted) { DEBUG("game hasn't started"); return false; } //are we moving pieces?
	if(i_s < 0 || j_s < 0 || i_s > 7 || j_s > 7 || i_f < 0 || j_f < 0 || i_f > 7 || j_f > 7) { DEBUG("not in board"); return false; } //is this inside the board?
	if(!piece(i_s,j_s)) { DEBUG("no piece"); return false; }
	if((piece(i_s,j_s) & COLOR_MASK) != toMove) { DEBUG("wrong color"); return false; } //is it this person's turn?
	if(piece(i_f,j_f)!=0) { DEBUG("moving to occupied"); return false; } // is there something occupying the spot to move to?
	if(frozen(i_s,j_s)) { DEBUG("frozen"); return false; }
	if(abs(i_f-i_s)+abs(j_f-j_s)!=1) { DEBUG("too far"); return false; }
	if(isPawn(piece(i_s,j_s))) {
		if((i_f-i_s) == (getColor(piece(i_s,j_s)) * 2 - 1)) { DEBUG("pawns don't move back"); return false; } //pawns going in the right direction?
	}
	return true;
}