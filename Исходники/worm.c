ENTRYPOINT void
init_worm (ModeInfo * mi)
{
	wormstruct *wp;
	int         size = MI_SIZE(mi);
	int         i, j;

	if (worms == NULL) {
		if ((worms = (wormstruct *) calloc(MI_NUM_SCREENS(mi),
					       sizeof (wormstruct))) == NULL)
			return;
	}
	wp = &worms[MI_SCREEN(mi)];
	if (MI_NPIXELS(mi) <= 2 || MI_WIN_IS_USE3D(mi))
		wp->nc = 2;
	else
		wp->nc = MI_NPIXELS(mi);
	if (wp->nc > NUMCOLORS)
		wp->nc = NUMCOLORS;

	free_worms(wp);
	wp->nw = MI_BATCHCOUNT(mi);
	if (wp->nw < -MINWORMS)
		wp->nw = NRAND(-wp->nw - MINWORMS + 1) + MINWORMS;
	else if (wp->nw < MINWORMS)
		wp->nw = MINWORMS;
	if (!wp->worm)
		wp->worm = (wormstuff *) malloc(wp->nw * sizeof (wormstuff));

	if (!wp->size)
		wp->size = (int *) malloc(NUMCOLORS * sizeof (int));

	wp->maxsize = (REDRAWSTEP + 1) * wp->nw;	/*  / wp->nc + 1; */
	if (!wp->rects)
		wp->rects =
			(XRectangle *) malloc(wp->maxsize * NUMCOLORS * sizeof (XRectangle));


	if (!init_table) {
		init_table = 1;
		for (i = 0; i < SEGMENTS; i++) {
			sintab[i] = SINF(i * 2.0 * M_PI / SEGMENTS);
			costab[i] = COSF(i * 2.0 * M_PI / SEGMENTS);
		}
	}
	wp->xsize = MI_WIN_WIDTH(mi);
	wp->ysize = MI_WIN_HEIGHT(mi);
	wp->zsize = MAXZ - MINZ + 1;
	if (MI_NPIXELS(mi) > 2)
		wp->chromo = NRAND(MI_NPIXELS(mi));

	if (size < -MINSIZE)
		wp->circsize = NRAND(-size - MINSIZE + 1) + MINSIZE;
	else if (size < MINSIZE)
		wp->circsize = MINSIZE;
	else
		wp->circsize = size;

	for (i = 0; i < wp->nc; i++) {
		for (j = 0; j < wp->maxsize; j++) {
			wp->rects[i * wp->maxsize + j].width = wp->circsize;
			wp->rects[i * wp->maxsize + j].height = wp->circsize;

		}
	}
	(void) memset((char *) wp->size, 0, wp->nc * sizeof (int));

	wp->wormlength = (int) sqrt(wp->xsize + wp->ysize) *
		MI_CYCLES(mi) / 8;	/* Fudge this to something reasonable */
	for (i = 0; i < wp->nw; i++) {
		wp->worm[i].circ = (XPoint *) malloc(wp->wormlength * sizeof (XPoint));
		wp->worm[i].diffcirc = (int *) malloc(wp->wormlength * sizeof (int));

		for (j = 0; j < wp->wormlength; j++) {
			wp->worm[i].circ[j].x = wp->xsize / 2;
			wp->worm[i].circ[j].y = wp->ysize / 2;
			if (MI_WIN_IS_USE3D(mi))
				wp->worm[i].diffcirc[j] = 0;
		}
		wp->worm[i].dir = NRAND(SEGMENTS);
		wp->worm[i].dir2 = NRAND(SEGMENTS);
		wp->worm[i].tail = 0;
		wp->worm[i].x = wp->xsize / 2;
		wp->worm[i].y = wp->ysize / 2;
		wp->worm[i].z = SCREENZ - MINZ;
		wp->worm[i].redrawing = 0;
	}

	if (MI_WIN_IS_INSTALL(mi) && MI_WIN_IS_USE3D(mi)) {
		XSetForeground(MI_DISPLAY(mi), MI_GC(mi), MI_NONE_COLOR(mi));
		XFillRectangle(MI_DISPLAY(mi), MI_WINDOW(mi), MI_GC(mi),
			       0, 0, wp->xsize, wp->ysize);
	} else
		XClearWindow(MI_DISPLAY(mi), MI_WINDOW(mi));
}