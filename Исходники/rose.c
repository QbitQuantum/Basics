main()
{
	char buff[100];
	int cn, r, k, t, dt, lp, x, rx, ry;
	int oldx, oldy, newx, newy;
	int offx, offy;
	Point jstring();
	char *getstring();
	Point p;
	int nonstop = NONSTOP;

	local();
	request(MOUSE);
	/* random number seed is derived from position of dmd layer */
	srand(mouse.xy.x);
	request(KBD);
	for ( ;; ) {
		lp = dt = 0;
		if ( nonstop == 0 ) {
			/* ask for lp parameter */
			jmoveto(Pt(0,0));
			p = jstring("loops=");
			lp = getnum(p);
			jmoveto(Pt(0,0));
			jstring("loops=");
		}
		if ( lp < 0 )
			exit();
		if ( lp == 0 )
			lp = rand() % 31 + 1;

		if ( nonstop == 0 ) {
			/* ask for dt parameter */
			jmoveto(Pt(0,0));
			p = jstring("delta=");
			dt = getnum(p);
			jmoveto(Pt(0,0));
			jstring("delta=");
		}
		if ( dt <= 0 )
			dt = rand() % 358 + 1;

		/* clear screen */
		jrectf(Jrect,F_CLR);
		t=0; 
		oldx = offx = XMAX / 2;
		oldy = offy = YMAX / 2;
		cn = 1;
		/* draw rose */
		do {
			t=(t+dt)%360;
			x=(lp*t)%360;
			r = Isin(x);
			rx=muldiv(r,XMAX-1,1024);
			ry=muldiv(r,YMAX-1,1024);
			newx = offx + muldiv(rx,Icos(t),1024) / 2;
			newy = offy +  muldiv(ry,Isin(t),1024) / 2;
			jsegment(Pt(oldx,oldy),Pt(newx,newy),F_STORE);
			oldx=newx; 
			oldy=newy;
			/* give up the CPU every 10 times around */
			if ( cn++ > 10 ) {
				cn = 0;
				sleep(4);
			}
		} while ( t != 0 && (k=kbdchar()) != 'q' ) ;
		if ( nonstop == 1 ) {
			/* in nonstop mode, any key aborts */
			if ( k != -1 )
				exit();
			/* sleep 2 seconds between random patterns */
			sleep(120);
		}
	}
}