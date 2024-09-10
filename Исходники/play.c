static void
findstats(Pos p, Ori o)
{
	/* Recalculate cross assert and score total at 'p'
	 */
	Pos	left, right;
	Word lword, rword;
	Node n;
	Edge e;
	int	s;

	lword.n = rword.n = 0;
	if(EDGE(p))
		return;

	/* find word to the left */
	s = 0;
	for(left=PREV(p,o); HASLETTER(left); left = PREV(left,o))
		;
	left = NEXT(left,o);
	while (HASLETTER(left)) {
		lword.c[lword.n++] = LETTER(left);
		s += SCORE(left);
		left = NEXT(left,o);
	}
	/* find word to the right */
	for(right=NEXT(p,o); HASLETTER(right); right = NEXT(right,o)) {
		rword.c[rword.n++] = LETTER(right);
		s += SCORE(right);
	}
	if(DBG) {
		wordprint(&lword);
		print("X");
		wordprint(&rword);
		print(" [%d] ", s);
	}

	SIDE(p,o) = s;
	ISANCHOR(p) = true;

	/* calculate cross asserts */
	CROSS(p,o) = 0;
	n = traverse(root, &lword, 0);
	assert(n>=0);
	if(n>0)
		do {
			e = dict[n++];
			if ( (rword.n && isword(NODE(e), &rword)) || 
				 (!rword.n && TERM(e)) ) {
				CROSS(p,o) |= 1 << LET(e);
				DPRINT("%c, ", LET(e)+'a');
			}
		} while (!(LAST(e)));
	DPRINT("\n");
}