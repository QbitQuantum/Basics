/* http://wvware.sourceforge.net/caolan/Polyline.html */
static GpStatus
Polyline (MetafilePlayContext *context, BYTE *data)
{
	GpStatus status;
	int p;
	/* variable number of parameters */
	SHORT num = GETS(WP1);

#ifdef DEBUG_WMF
	printf ("Polyline %d points", num);
#endif
	SHORT x1 = GETS(WP2);
	SHORT y1 = GETS(WP3);
	int n = 4;
	for (p = 1; p < num; p++) {
		SHORT x2 = GETS(WP(n));
		n++;
		SHORT y2 = GETS(WP(n));
		n++;
#ifdef DEBUG_WMF_2
		printf ("\n\tdraw from %d,%d to %d,%d", x1, y1, x2, y2);
#endif
		GpPen *pen = gdip_metafile_GetSelectedPen (context);
		status = GdipDrawLine (context->graphics, pen, x1, y1, x2, y2);
		if (status != Ok)
			return status;

		x1 = x2;
		y1 = y2;
	}
	return Ok;
}