/* Normalise the histogram so that it integrates to unity, taking the width of
 * the bins into account.
 * nh       - number of histogram bins
 * h        - histogram
 * binwidth - width of each histogram bin (1/scale)
 *
 * required: nh, h, binwidth
 * modified: h
 */
static void normhist(int nh, double h[], double binwidth, int *psh)
{
	double sh = 0.0;
	int i;
	for(i=0; i<nh; i++)
		sh += h[i];
	for(i=0; i<nh; i++)
		h[i]/= binwidth*sh;
	*psh = RINT(sh);
}