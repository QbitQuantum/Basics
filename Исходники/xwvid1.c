 /*NP*/ void
trace_parcel (float pres, float temp, float dwpt)
	/*************************************************************/
	/*  TRACE_PARCEL                                             */
	/*  John Hart  NSSFC KCMO                                    */
	/*                                                           */
	/*  Plots parcel(pres, temp, dwpt) trajectory on SkewT       */
	/*  graphic.                                                 */
	/*                                                           */
	/*  pres             - Pressure of initial parcel(mb)        */
	/*  temp             - Temperature of initial parcel (c)     */
	/*  dwpt             - Dew Point of initial parcel (c)       */
	/*************************************************************/
{
  float i, p2, t2, t3;
  short x, y;

  if (!qc (pres) || !qc (temp) || !qc (dwpt))
    return;

  setcolor (31, draw_reg, gc);
  setlinestyle (4, 1);

  x = temp_to_pix (virtemp (pres, temp, dwpt), pres);
  y = pres_to_pix (pres);
  moveto (x, y);

  drylift (pres, temp, dwpt, &p2, &t2);
  x = temp_to_pix (virtemp (p2, t2, t2), p2);
  y = pres_to_pix (p2);
  lineto (x, y);

  for (i = p2 - 50; i >= 100; i = i - 50)
    {
      t3 = wetlift (p2, t2, i);
      x = temp_to_pix (virtemp (i, t3, t3), i);
      y = pres_to_pix (i);
      lineto (x, y);
    }
  t3 = wetlift (p2, t2, 100);
  x = temp_to_pix (virtemp (100, t3, t3), 100);
  y = pres_to_pix (100);
  lineto (x, y);
}