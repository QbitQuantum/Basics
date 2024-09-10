static Bool
startover(ModeInfo * mi)
{
	unistruct  *gp = &universes[MI_SCREEN(mi)];
	int         size = (int) MI_SIZE(mi);
	int         i, j;	/* more tmp */
	double      w1, w2;	/* more tmp */
	double      d, v, w, h;	/* yet more tmp */

	gp->step = 0;

	if (MI_COUNT(mi) < -MINGALAXIES)
		free_galaxies(gp);
	gp->ngalaxies = MI_COUNT(mi);
	if (gp->ngalaxies < -MINGALAXIES)
		gp->ngalaxies = NRAND(-gp->ngalaxies - MINGALAXIES + 1) + MINGALAXIES;
	else if (gp->ngalaxies < MINGALAXIES)
		gp->ngalaxies = MINGALAXIES;
	if (gp->galaxies == NULL)
		if ((gp->galaxies = (Galaxy *) calloc(gp->ngalaxies,
				sizeof (Galaxy))) == NULL) {
			free_galaxy(MI_DISPLAY(mi), gp);
			return False;
	}
	for (i = 0; i < gp->ngalaxies; ++i) {
		Galaxy     *gt = &gp->galaxies[i];
		double      sinw1, sinw2, cosw1, cosw2;

		if (MI_NPIXELS(mi) >= COLORS)
			do {
				gt->galcol = NRAND(COLORBASE) * COLORS;
			} while (gt->galcol + COLORBASE / 2 < GREEN + NOTGREEN &&
			      gt->galcol + COLORBASE / 2 > GREEN - NOTGREEN);
		else
			gt->galcol = 0;
		/* Galaxies still may have some green stars but are not all green. */

		if (gt->stars != NULL) {
			free(gt->stars);
			gt->stars = (Star *) NULL;
		}
		gt->nstars = (NRAND(MAX_STARS / 2)) + MAX_STARS / 2;
		if ((gt->stars = (Star *) malloc(gt->nstars *
				sizeof (Star))) == NULL) {
			free_galaxy(MI_DISPLAY(mi), gp);
			return False;
		}
		w1 = 2.0 * M_PI * FLOATRAND;
		w2 = 2.0 * M_PI * FLOATRAND;
		sinw1 = SINF(w1);
		sinw2 = SINF(w2);
		cosw1 = COSF(w1);
		cosw2 = COSF(w2);

		gp->mat[0][0] = cosw2;
		gp->mat[0][1] = -sinw1 * sinw2;
		gp->mat[0][2] = cosw1 * sinw2;
		gp->mat[1][0] = 0.0;
		gp->mat[1][1] = cosw1;
		gp->mat[1][2] = sinw1;
		gp->mat[2][0] = -sinw2;
		gp->mat[2][1] = -sinw1 * cosw2;
		gp->mat[2][2] = cosw1 * cosw2;

		gt->vel[0] = FLOATRAND * 2.0 - 1.0;
		gt->vel[1] = FLOATRAND * 2.0 - 1.0;
		gt->vel[2] = FLOATRAND * 2.0 - 1.0;
		gt->pos[0] = -gt->vel[0] * DELTAT *
			gp->f_hititerations + FLOATRAND - 0.5;
		gt->pos[1] = -gt->vel[1] * DELTAT *
			gp->f_hititerations + FLOATRAND - 0.5;
		gt->pos[2] = (-gt->vel[2] * DELTAT *
			gp->f_hititerations + FLOATRAND - 0.5) + Z_OFFSET;

		gt->mass = (int) (FLOATRAND * 1000.0) + 1;

		gp->size = GALAXYRANGESIZE * FLOATRAND + GALAXYMINSIZE;

		for (j = 0; j < gt->nstars; ++j) {
			Star       *st = &gt->stars[j];
			double      sinw, cosw;

			w = 2.0 * M_PI * FLOATRAND;
			sinw = SINF(w);
			cosw = COSF(w);
			d = FLOATRAND * gp->size;
			h = FLOATRAND * exp(-2.0 * (d / gp->size)) / 5.0 * gp->size;
			if (FLOATRAND < 0.5)
				h = -h;
			st->pos[0] = gp->mat[0][0] * d * cosw + gp->mat[1][0] * d * sinw +
				gp->mat[2][0] * h + gt->pos[0];
			st->pos[1] = gp->mat[0][1] * d * cosw + gp->mat[1][1] * d * sinw +
				gp->mat[2][1] * h + gt->pos[1];
			st->pos[2] = gp->mat[0][2] * d * cosw + gp->mat[1][2] * d * sinw +
				gp->mat[2][2] * h + gt->pos[2];

			v = sqrt(gt->mass * QCONS / sqrt(d * d + h * h));
			st->vel[0] = -gp->mat[0][0] * v * sinw + gp->mat[1][0] * v * cosw +
				gt->vel[0];
			st->vel[1] = -gp->mat[0][1] * v * sinw + gp->mat[1][1] * v * cosw +
				gt->vel[1];
			st->vel[2] = -gp->mat[0][2] * v * sinw + gp->mat[1][2] * v * cosw +
				gt->vel[2];

			st->vel[0] *= DELTAT;
			st->vel[1] *= DELTAT;
			st->vel[2] *= DELTAT;

			st->px = 0;
			st->py = 0;

			if (size < -MINSIZE)
				st->size = NRAND(-size - MINSIZE + 1) + MINSIZE;
			else if (size < MINSIZE)
				st->size = MINSIZE;
			else
				st->size = size;

			st->Z_size = st->size;

		}
	}

	MI_CLEARWINDOW(mi);

#if 0
	(void) printf("ngalaxies=%d, f_hititerations=%d\n",
		      gp->ngalaxies, gp->f_hititerations);
	(void) printf("f_deltat=%g\n", DELTAT);
	(void) printf("Screen: ");
	(void) printf("%dx%d pixel (%d-%d, %d-%d)\n",
	  (gp->clip.right - gp->clip.left), (gp->clip.bottom - gp->clip.top),
	       gp->clip.left, gp->clip.right, gp->clip.top, gp->clip.bottom);
#endif
	return True;
}