char Ziehe_KreisNO90(short xr1,short zp1,short xr2,short zp2,short xrm,short zpm,char g03g02)
{
  double sx=(double)zp1,sy=(double)xr1,
	 ex=(double)zp2,ey=(double)xr2,
	 mx=(double)zpm,my=(double)xrm;
  double dx,dy,w,cosw,sinw;
  double rad1,rad2,stw,endw,step=(double)schritt_g02;
  char quadr1,quadr2,endprg=0;
  short x,y;

  dx=sx-mx;
  dy=sy-my;
  rad1=sqrt(dx*dx+dy*dy);
  cosw=dx/rad1;
  sinw=dy/rad1;
  stw=arc_wi(sinw,cosw,&quadr1);

  dx=ex-mx;
  dy=ey-my;
  rad2=sqrt(dx*dx+dy*dy);
  cosw=dx/rad2;
  sinw=dy/rad2;
  endw=arc_wi(sinw,cosw,&quadr2);

  if (quadr1!=quadr2) { /* Routine zZ noch nicht in Funktion */
			Meldung("M99 Quadranten-Fehler!");
			Status("Fehler!");
			getch();
			endprg=1;
		      }

  if (fabs(fabs(rad1)-fabs(rad2))>160)
    {
      Meldung("M99-0,8mm-Toleranz �berschritten");
      Status("Fehler");
      getch();
      endprg=1; /* Nur zZ */
    }

  if (!endprg)
    {
      if (g03g02)
	{ /* G02 */
	   if (endw<stw) stw-=360.0;
	   for(w=stw;w<endw && !endprg;w+=step)
	      {
		x=(short)(mx+rad1*cos(w*deg));
		y=(short)(my+rad1*sin(w*deg));
		Setzte_Stahl(y,x,tool);
		Koordinaten(y,x);
		xrad=y;
		zpos=x;
		Wait(prgconfig.wait_g01);
		endprg=Check_FlagTasten();
	      }
	} else { /* g03 */
		 if (endw>stw) endw-=360.0;
		 for(w=stw;w>endw && !endprg;w-=step)
		  {
		    x=(short)(mx+rad1*cos(w*deg));
		    y=(short)(my+rad1*sin(w*deg));
		    Setzte_Stahl(y,x,tool);
		    Koordinaten(y,x);
		    xrad=y;
		    zpos=x;
		    Wait(prgconfig.wait_g01);
		    endprg=Check_FlagTasten();
		  }
	       } /* von g03 */
    } /* von if !endprg */

    if (!endprg)
       {
	 Setzte_Stahl(xr2,zp2,tool);
	 xrad=xr2;
	 zpos=zp2;
	 Koordinaten(xr2,zp2);
       }

  return endprg;
}