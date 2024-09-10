static void
draw_dots(ModeInfo * mi, int in)
{

	float       i, inc;
	float       x, y;

	spiralstruct *sp = &spirals[MI_SCREEN(mi)];

	inc = TWOPI / (float) sp->dots;
	for (i = 0.0; i < TWOPI; i += inc) {
		x = sp->traildots[in].hx + COSF(i + sp->traildots[in].ha) *
			sp->traildots[in].hr;
		y = sp->traildots[in].hy + SINF(i + sp->traildots[in].ha) *
			sp->traildots[in].hr;
		XDrawPoint(MI_DISPLAY(mi), MI_WINDOW(mi), MI_GC(mi),
			   TFX(sp, x), TFY(sp, y));
	}
}