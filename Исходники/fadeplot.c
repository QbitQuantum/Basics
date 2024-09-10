static Bool
initSintab(ModeInfo * mi)
{
	fadeplotstruct *fp = &fadeplots[MI_SCREEN(mi)];
	int         i;
	float       x;

	fp->angles = NRAND(950) + 250;
	if ((fp->stab = (int *) malloc(fp->angles * sizeof (int))) == NULL) {
		free_fadeplot(mi);
		return False;
	}
	for (i = 0; i < fp->angles; i++) {
		x = SINF(2.0 * M_PI * i / fp->angles);
		fp->stab[i] = (int) (x * ABS(x) * fp->min) + fp->min;
	}
	return True;
}