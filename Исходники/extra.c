dblgood ()  {
	register int	n;			/* accumulated judgment */
	register int	OFFC = *offptr;		/* no. of computer's men off */
	register int	OFFO = *offopp;		/* no. of player's men off */

#ifdef DEBUG
	register int	i;
	if (trace == NULL)
		trace = fopen ("bgtrace","w");
#endif

						/* get real pip value */
	n = eval()*cturn;
#ifdef DEBUG
	fputs ("\nDoubles:\nBoard: ",trace);
	for (i = 0; i < 26; i++)
		fprintf (trace," %d",board[i]);
	fprintf (trace,"\n\tpip = %d, ",n);
#endif

						/* below adjusts pip value
						 * according to position
						 * judgments */

						/* check men moving off
						 * board */
	if (OFFC > -15 || OFFO > -15)  {
		if (OFFC < 0 && OFFO < 0)  {
			OFFC += 15;
			OFFO += 15;
			n +=((OFFC-OFFO)*7)/2;
		} else if (OFFC < 0)  {
			OFFC += 15;
			n -= OFFO*7/2;
		} else if (OFFO < 0)  {
			OFFO += 15;
			n += OFFC*7/2;
		}
		if (OFFC < 8 && OFFO > 8)
			n -= 7;
		if (OFFC < 10 && OFFO > 10)
			n -= 7;
		if (OFFC < 12 && OFFO > 12)
			n -= 7;
		if (OFFO < 8 && OFFC > 8)
			n += 7;
		if (OFFO < 10 && OFFC > 10)
			n += 7;
		if (OFFO < 12 && OFFC > 12)
			n += 7;
		n += ((OFFC-OFFO)*7)/2;
	}

#ifdef DEBUG
	fprintf (trace,"off = %d, ",n);
#endif

						/* see if men are trapped */
	n -= freemen(bar);
	n += freemen(home);
	n += trapped(home,-cturn);
	n -= trapped(bar,cturn);

#ifdef DEBUG
	fprintf (trace,"free = %d\n",n);
	fprintf (trace,"\tOFFC = %d, OFFO = %d\n",OFFC,OFFO);
	fflush (trace);
#endif

						/* double if 2-3 moves ahead */
	if (n > 10+rnum(7))
		return(1);
	return (0);
}