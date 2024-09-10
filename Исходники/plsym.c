static void
plchar(signed char *vxygrid, PLFLT *xform, PLINT base, PLINT oline, PLINT uline,
       PLINT refx, PLINT refy, PLFLT scale, PLFLT xpmm, PLFLT ypmm,
       PLFLT *p_xorg, PLFLT *p_yorg, PLFLT *p_width)
{
    PLINT xbase, ybase, ydisp, lx, ly, cx, cy;
    PLINT k, penup;
    PLFLT x, y;
    PLINT llx[STLEN], lly[STLEN], l = 0;

    xbase = vxygrid[2];
    *p_width = vxygrid[3] - xbase;
    if (base == 0) {
	ybase = 0;
	ydisp = vxygrid[0];
    }
    else {
	ybase = vxygrid[0];
	ydisp = 0;
    }
    k = 4;
    penup = 1;

    for (;;) {
	cx = vxygrid[k++];
	cy = vxygrid[k++];
	if (cx == 64 && cy == 64) {
	  if (l) {
	    plP_draphy_poly(llx, lly, l);
	    l = 0;
	  }
	  break;
	}
	if (cx == 64 && cy == 0) {
	  if (l) {
	    plP_draphy_poly(llx, lly, l);
	    l = 0;
	  }
	  penup = 1;
	}
	else {
	    x = *p_xorg + (cx - xbase) * scale;
	    y = *p_yorg + (cy - ybase) * scale;
	    lx = refx + ROUND(xpmm * (xform[0] * x + xform[1] * y));
	    ly = refy + ROUND(ypmm * (xform[2] * x + xform[3] * y));
	    if (penup == 1) {
	      if (l) {
		plP_draphy_poly(llx, lly, l);
		l = 0;
	      }
	      llx[l] = lx;
	      lly[l++] = ly; /* store 1st point ! */
	      plP_movphy(lx, ly);
	      penup = 0;
	    }
	    else {
	      llx[l] = lx;
	      lly[l++] = ly;
	    }
	}
    }

    if (oline) {
	x = *p_xorg;
	y = *p_yorg + (30 + ydisp) * scale;
	lx = refx + ROUND(xpmm * (xform[0] * x + xform[1] * y));
	ly = refy + ROUND(ypmm * (xform[2] * x + xform[3] * y));
	plP_movphy(lx, ly);
	x = *p_xorg + *p_width * scale;
	lx = refx + ROUND(xpmm * (xform[0] * x + xform[1] * y));
	ly = refy + ROUND(ypmm * (xform[2] * x + xform[3] * y));
	plP_draphy(lx, ly);
    }
    if (uline) {
	x = *p_xorg;
	y = *p_yorg + (-5 + ydisp) * scale;
	lx = refx + ROUND(xpmm * (xform[0] * x + xform[1] * y));
	ly = refy + ROUND(ypmm * (xform[2] * x + xform[3] * y));
	plP_movphy(lx, ly);
	x = *p_xorg + *p_width * scale;
	lx = refx + ROUND(xpmm * (xform[0] * x + xform[1] * y));
	ly = refy + ROUND(ypmm * (xform[2] * x + xform[3] * y));
	plP_draphy(lx, ly);
    }
    *p_xorg = *p_xorg + *p_width * scale;
}