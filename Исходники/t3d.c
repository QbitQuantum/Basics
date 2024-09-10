/*------------------------------------------------------------------*/
static void
fill_kugel(struct state *st, int i, Pixmap buf, int setcol)
{
  double ra;
  int m,col,inc=1,inr=3,d;
  d=(int)((ABS(st->kugeln[i].r1)*2));
  if (d==0) d=1;
  
#ifdef FASTDRAW
  if(st->fastdraw && d<st->fastch)
    {
#	ifdef FASTCOPY
      XCopyArea(st->dpy, st->fastmask, buf, st->andgc, sum1ton(d)-(d+1)/2, 1,d,d,
		(int)(st->kugeln[i].x1)-d/2, (int)(st->kugeln[i].y1)-d/2);
      XCopyArea(st->dpy, st->fastcircles, buf, st->orgc, sum1ton(d)-(d+1)/2, 1,d,d,
		(int)(st->kugeln[i].x1)-d/2, (int)(st->kugeln[i].y1)-d/2);
#	else
      XPutImage(st->dpy, buf, st->andgc, st->fastmask[d-1], 0, 0,
		(int)(st->kugeln[i].x1)-d/2, (int)(st->kugeln[i].y1)-d/2, d, d);
      XPutImage(st->dpy, buf, st->orgc, st->fastcircles[d-1], 0, 0,
		(int)(st->kugeln[i].x1)-d/2, (int)(st->kugeln[i].y1)-d/2, d, d);
#	endif
    }
  else
#endif
    {
      if(ABS(st->kugeln[i].r1)<6.0) inr=9;
      
      for (m=0;m<=28;m+=inr)
	{
	  ra=st->kugeln[i].r1*sqrt(1-m*m/(28.0*28.0));
#ifdef PRTDBX
	  printf("Radius: %f\n",ra);
#endif
	  if(-ra< 3.0) inc=14;
	  else if(-ra< 6.0) inc=8;
	  else if(-ra<20.0) inc=4;
	  else if(-ra<40.0) inc=2;
	  if(setcol)
	    {
	      if (m==27)
                col=33;
	      else
		col=(int)(m);

	      if (col>33)
                col=33;

              col/=3;
	      setink(st->colors[col].pixel);
	    }

#ifdef USE_POLYGON
          {
            int n, nr;
	  for (n=0,nr=0;n<=sines-1;n+=inc,nr++)
	    {
	      track[nr].x=st->kugeln[i].x1+(int)(ra*st->sinus[n])+(st->kugeln[i].r1-ra)/2;
	      track[nr].y=st->kugeln[i].y1+(int)(ra*st->cosinus[n])+(st->kugeln[i].r1-ra)/2;
	    }
	  XFillPolygon(st->dpy,buf,st->gc,track,nr,Convex,CoordModeOrigin);
          }
#else /* Use XFillArc */
	  XFillArc(st->dpy, buf, st->gc,
		   (int)(st->kugeln[i].x1+(st->kugeln[i].r1+ra)/2),
		   (int)(st->kugeln[i].y1+(st->kugeln[i].r1+ra)/2),
		   (int)-(2*ra+1), (int)-(2*ra+1), 0, 360*64);
#endif
	}
    }
}