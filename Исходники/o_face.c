int
o_face(		/* determine if face intersects cube */
	OBJREC  *o,
	CUBE  *cu
)
{
	FVECT  cumin, cumax;
	FVECT  v1, v2;
	double  d1, d2;
	int  vloc;
	register FACE  *f;
	register int  i, j;
				/* get face arguments */
	f = getface(o);
	if (f->area == 0.0)		/* empty face */
		return(O_MISS);
					/* compute cube boundaries */
	for (j = 0; j < 3; j++)
		cumax[j] = (cumin[j] = cu->cuorg[j]-FTINY)
				+ cu->cusize + 2.0*FTINY;

	vloc = ABOVE | BELOW;		/* check vertices */
	for (i = 0; i < f->nv; i++)
		if ( (j = plocate(VERTEX(f,i), cumin, cumax)) )
			vloc &= j;
		else
			return(O_HIT);	/* vertex inside */

	if (vloc)			/* all to one side */
		return(O_MISS);
	
	for (i = 0; i < f->nv; i++) {	/* check edges */
		if ((j = i + 1) >= f->nv)
			j = 0;			/* wrap around */
		VCOPY(v1, VERTEX(f,i));		/* clip modifies */
		VCOPY(v2, VERTEX(f,j));		/* the vertices! */
		if (clip(v1, v2, cumin, cumax))
			return(O_HIT);		/* edge inside */
	}
					/* see if cube cuts plane */
	for (j = 0; j < 3; j++)
		if (f->norm[j] > 0.0) {
			v1[j] = cumin[j];
			v2[j] = cumax[j];
		} else {
			v1[j] = cumax[j];
			v2[j] = cumin[j];
		}
	if ((d1 = DOT(v1, f->norm) - f->offset) > FTINY)
		return(O_MISS);
	if ((d2 = DOT(v2, f->norm) - f->offset) < -FTINY)
		return(O_MISS);
					/* intersect face */
	for (j = 0; j < 3; j++)
		v1[j] = (v1[j]*d2 - v2[j]*d1)/(d2 - d1);
	if (inface(v1, f))
		return(O_HIT);
	
	return(O_MISS);		/* no intersection */
}