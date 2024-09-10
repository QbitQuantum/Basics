int calc_moves_multi(struct coin *cn, struct moveset *possible) {
	int i, count;
	enum direction dir;
	for(i=0; i<cn->num_dir; i++) {
		dir = cn->allowed[i];
		debug("\tmulti>\tdir = %s\n", dirname[cn->allowed[i]]);
		count = 1;
		while(isBlank(pos(cn, i, count))) {
			moveset_addMoves(possible, cn, pos(cn, i, count), 0);
			count++;
		}
		if(isOpp(pos(cn, i, count))) {
			moveset_addMoves(possible, cn, pos(cn, i, count), MOVE_FLAG_KILLED);
			count++;
		}
	}
}