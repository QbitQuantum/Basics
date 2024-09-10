void
_cairo_win32_debug_dump_hrgn (HRGN rgn, char *header)
{
    RGNDATA *rd;
    unsigned int z;

    if (header)
	fprintf (stderr, "%s\n", header);

    if (rgn == NULL) {
	fprintf (stderr, " NULL\n");
    }

    z = GetRegionData(rgn, 0, NULL);
    rd = (RGNDATA*) _cairo_malloc (z);
    z = GetRegionData(rgn, z, rd);

    fprintf (stderr, " %ld rects, bounds: %ld %ld %ld %ld\n",
	     rd->rdh.nCount,
	     rd->rdh.rcBound.left,
	     rd->rdh.rcBound.top,
	     rd->rdh.rcBound.right - rd->rdh.rcBound.left,
	     rd->rdh.rcBound.bottom - rd->rdh.rcBound.top);

    for (z = 0; z < rd->rdh.nCount; z++) {
	RECT r = ((RECT*)rd->Buffer)[z];
	fprintf (stderr, " [%d]: [%ld %ld %ld %ld]\n",
		 z, r.left, r.top, r.right - r.left, r.bottom - r.top);
    }

    free(rd);
    fflush (stderr);
}