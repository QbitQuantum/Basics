void newpos(void)
{
	cleardevice();
	x=0.0;y=0.0;z=0.0;
	sx=0.0;sy=0.0;
	xa=0.0;ya=0.0;za=0.0;
	sxa=0.0;sya=0.0;sxb=0.0;syb=0.0;
	sxs=0.0;sys=0.0;
	sr1=0.0;sr2=0.0;sr3=0.0;
	cr1=0.0;cr2=0.0;cr3=0.0;
	msx=0.0;msy=0.0;
	rx=0.0;ry=0.0;
	t1=0;t2=0;
	p1=0;
	rotation();
/*	for(t2=1;t2<=6;t2++) */
	for(t2=1;t2<=4;t2++)
	{
		setlinestyle(USERBIT_LINE,0xffff,NORM_WIDTH);

		/* get starting position */
/*		x=array1[p1][0];
		y=array1[p1][1];
		z=array1[p1][2]; */
		x=array2[p1][0];
		y=array2[p1][1];
		z=array2[p1][2];
		calc_3d();
		windows();
		sxa=sx;sya=sy;

		/* finish displaying side */
/*		for(t1=1;t1<=4;t1++) */
		for(t1=1;t1<=3;t1++)
		{
			p1++;
/*			x=array1[p1][0];
			y=array1[p1][1];
			z=array1[p1][2]; */
			x=array2[p1][0];
			y=array2[p1][1];
			z=array2[p1][2];
			calc_3d();
			windows();
			sxs=sx;
			sys=sy;
			sxb=sx;
			syb=sy;
			moveto(sxa,sya);
			lineto(sxb,syb);
			sxa=sxs;
			sya=sys;
		}
		p1++;
	}
}