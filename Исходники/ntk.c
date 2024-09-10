void
plD_esc_ntk(PLStream *pls, PLINT op, void *ptr)
{
  PLINT i,j;
  short *xa, *ya;
  Pixmap bitmap;
  static unsigned char bit_pat[] = {
    0x24, 0x01, 0x92, 0x00, 0x49, 0x00, 0x24, 0x00, 0x12, 0x00, 0x09, 0x00,
    0x04, 0x00, 0x02, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff};

  switch (op) {

  case PLESC_DASH:
    xa = (short *) malloc(sizeof(short) * pls->dev_npts);
    ya = (short *) malloc(sizeof(short) * pls->dev_npts);
    for (i = 0; i < pls->dev_npts; i++) {
      xa[i] = pls->dev_x[i];
      ya[i] = pls->dev_y[i];
    }

    j = sprintf(dash, "-dash {");
    for (i = 0; i < pls->nms; i++)
      j += sprintf(&dash[j]," %d %d",
		   (int) ceil(pls->mark[i]/1e3 * ppm),
		   (int) ceil(pls->space[i]/1e3 * ppm));
    sprintf(&dash[j], "}");
    plD_polyline_ntk(pls, xa, ya, pls->dev_npts);
    free(xa); free(ya);
    dash[0] = 0;
    break;

  case PLESC_FLUSH:
    tk_cmd("update");
    break;

  case PLESC_GETC:
    getcursor(pls, (PLGraphicsIn *) ptr);
    break;

  case PLESC_FILL:
    if (pls->patt != 0) {
      /* this is a hack! The real solution is in the if(0) bellow */
      pls->xpmm *= scale;
      pls->ypmm *= scale;
      plfill_soft( pls->dev_x, pls->dev_y, pls->dev_npts);
      pls->xpmm /= scale;
      pls->ypmm /= scale;
    } else {
      j = sprintf(cmd, "$plf.f2.c%d create polygon ", ccanv);
      for (i = 0; i < pls->dev_npts; i++)
	j += sprintf(&cmd[j], "%.1f %.1f ", pls->dev_x[i]/scale,
		     ymax-pls->dev_y[i]/scale);
      j += sprintf(&cmd[j]," -fill %s", curcolor);
      tk_cmd(cmd);
    }

    if (0) {
      if (pls->patt != 0) {
	Tk_DefineBitmap(interp, Tk_GetUid("foo"), bit_pat, 16, 16);
	bitmap = Tk_GetBitmap(interp, mainw, Tk_GetUid("patt"));
      }
      j = sprintf(cmd, "$plf.f2.c%d create polygon ", ccanv);
      for (i = 0; i < pls->dev_npts; i++)
	j += sprintf(&cmd[j], "%.1f %.1f ", pls->dev_x[i]/scale,
		     ymax-pls->dev_y[i]/scale);
      j += sprintf(&cmd[j]," -fill %s", curcolor);
      if (pls->patt != 0)
	sprintf(&cmd[j], " -stipple patt -outline black");

      tk_cmd(cmd);
  /*Tk_FreeBitmap(display, bitmap)*/
    }
    break;
  }
}