static int BuildCircle(REAL8 radius)
{
	int i,nrLines,xFloor;
	REAL8 xIncr,lineStart,lineEndIncl;
	HOR_CUT_LINE *l;
	PRECOND(radius != 0);
	radius /= (Side()*2);

	xFloor = (size_t)floor(radius);
	radius *= radius;
	nrLines = (xFloor*2)+1;
	l = (HOR_CUT_LINE *)ChkMalloc(sizeof(HOR_CUT_LINE)*nrLines);
	for(i=0; i < nrLines; i++) {
		/* mark not initialized */
		SET_MV_REAL4(&(l[i].start.f));
	}

	for (xIncr = 0; xIncr <= xFloor; xIncr+=1) {
	 REAL8 y = floor(sqrt(radius-sqr(xIncr))); 
	 Add2Lines(l,nrLines,xFloor,1,0, xIncr, y);
	 Add2Lines(l,nrLines,xFloor,1,0, xIncr,-y);
	 Add2Lines(l,nrLines,xFloor,1,0,-xIncr, y);
	 Add2Lines(l,nrLines,xFloor,1,0,-xIncr,-y);
	}
	for(i=0; i < nrLines; i++) {
		/* mark not initialized */
		if (!IS_MV_REAL4(&(l[i].start.f)))
			break;
	}
	POSTCOND(i < nrLines);
	lineStart = i;
	for(i = nrLines-1; i >=0;i--) {
		/* mark not initialized */
		if (!IS_MV_REAL4(&(l[i].start.f)))
			break;
	}
	POSTCOND(i >= 0);
	lineEndIncl = i;
	
	for (i=(int)lineStart ; i <= (int)lineEndIncl; i++) {
		PRECOND(!IS_MV_REAL4(&(l[i].start.f)));
		l[i].start.i = (int)Rint(l[i].start.f);
		l[i].end.i   = (int)Rint(l[i].end.f);
	}
	return 1;
}