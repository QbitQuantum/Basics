ENTRYPOINT void
draw_braid(ModeInfo * mi)
{
	Display    *display = MI_DISPLAY(mi);
	Window      window = MI_WINDOW(mi);
	int         num_points = 500;
	float       t_inc;
	float       theta, psi;
	float       t, r_diff;
	int         i, s;
	float       x_1, y_1, x_2, y_2, r1, r2;
	float       color, color_use = 0.0, color_inc;
	braidtype  *braid;

	if (braids == NULL)
		return;
	braid = &braids[MI_SCREEN(mi)];

#ifdef STANDALONE
    if (braid->eraser) {
      braid->eraser = erase_window (MI_DISPLAY(mi), MI_WINDOW(mi), braid->eraser);
      return;
    }
#endif

	MI_IS_DRAWN(mi) = True;
	XSetLineAttributes(display, MI_GC(mi), braid->linewidth,
			   LineSolid,
			   (braid->linewidth <= 3 ? CapButt : CapRound),
			   JoinMiter);

	theta = (2.0 * M_PI) / (float) (braid->braidlength);
	t_inc = (2.0 * M_PI) / (float) num_points;
	color_inc = (float) MI_NPIXELS(mi) * braid->color_direction /
		(float) num_points;
	braid->startcolor += SPINRATE * color_inc;
	if (((int) braid->startcolor) >= MI_NPIXELS(mi))
		braid->startcolor = 0.0;

	r_diff = (braid->max_radius - braid->min_radius) / (float) (braid->nstrands);

	color = braid->startcolor;
	psi = 0.0;
	for (i = 0; i < braid->braidlength; i++) {
		psi += theta;
		for (t = 0.0; t < theta; t += t_inc) {
#ifdef COLORROUND
			color += color_inc;
			if (((int) color) >= MI_NPIXELS(mi))
				color = 0.0;
			color_use = color;
#endif
			for (s = 0; s < braid->nstrands; s++) {
				if (ABS(braid->braidword[i]) == s)
					continue;
				if (ABS(braid->braidword[i]) - 1 == s) {
					/* crosSINFg */
#ifdef COLORCOMP
					if (MI_NPIXELS(mi) > 2) {
						color_use = color + SPINRATE *
							braid->components[applywordbackto(braid, s, i)] +
							(psi + t) / 2.0 / M_PI * (float) MI_NPIXELS(mi);
						while (((int) color_use) >= MI_NPIXELS(mi))
							color_use -= (float) MI_NPIXELS(mi);
						while (((int) color_use) < 0)
							color_use += (float) MI_NPIXELS(mi);
					}
#endif
#ifdef COLORROUND
					if (MI_NPIXELS(mi) > 2) {
						color_use += SPINRATE * color_inc;
						while (((int) color_use) >= MI_NPIXELS(mi))
							color_use -= (float) MI_NPIXELS(mi);
					}
#endif
					r1 = braid->min_radius + r_diff * (float) (s);
					r2 = braid->min_radius + r_diff * (float) (s + 1);
					if (braid->braidword[i] > 0 ||
					    (FABSF(t - theta / 2.0) > theta / 7.0)) {
						x_1 = ((0.5 * (1.0 + SINF(t / theta * M_PI - M_PI_2)) * r2 +
							0.5 * (1.0 + SINF((theta - t) / theta * M_PI - M_PI_2)) * r1)) *
							COSF(t + psi) + braid->center_x;
						y_1 = ((0.5 * (1.0 + SINF(t / theta * M_PI - M_PI_2)) * r2 +
							0.5 * (1.0 + SINF((theta - t) / theta * M_PI - M_PI_2)) * r1)) *
							SINF(t + psi) + braid->center_y;
						x_2 = ((0.5 * (1.0 + SINF((t + t_inc) / theta * M_PI - M_PI_2)) * r2 +
							0.5 * (1.0 + SINF((theta - t - t_inc) / theta * M_PI - M_PI_2)) * r1)) *
							COSF(t + t_inc + psi) + braid->center_x;
						y_2 = ((0.5 * (1.0 + SINF((t + t_inc) / theta * M_PI - M_PI_2)) * r2 +
							0.5 * (1.0 + SINF((theta - t - t_inc) / theta * M_PI - M_PI_2)) * r1)) *
							SINF(t + t_inc + psi) + braid->center_y;
						if (MI_NPIXELS(mi) > 2)
							XSetForeground(display, MI_GC(mi), MI_PIXEL(mi, (int) color_use));
						else
							XSetForeground(display, MI_GC(mi), MI_WHITE_PIXEL(mi));

						XDrawLine(display, window, MI_GC(mi),
							  (int) (x_1), (int) (y_1), (int) (x_2), (int) (y_2));
					}
#ifdef COLORCOMP
					if (MI_NPIXELS(mi) > 2) {
						color_use = color + SPINRATE *
							braid->components[applywordbackto(braid, s + 1, i)] +
							(psi + t) / 2.0 / M_PI * (float) MI_NPIXELS(mi);
						while (((int) color_use) >= MI_NPIXELS(mi))
							color_use -= (float) MI_NPIXELS(mi);
						while (((int) color_use) < 0)
							color_use += (float) MI_NPIXELS(mi);
					}
#endif
					if (braid->braidword[i] < 0 ||
					    (FABSF(t - theta / 2.0) > theta / 7.0)) {
						x_1 = ((0.5 * (1.0 + SINF(t / theta * M_PI - M_PI_2)) * r1 +
							0.5 * (1.0 + SINF((theta - t) / theta * M_PI - M_PI_2)) * r2)) *
							COSF(t + psi) + braid->center_x;
						y_1 = ((0.5 * (1.0 + SINF(t / theta * M_PI - M_PI_2)) * r1 +
							0.5 * (1.0 + SINF((theta - t) / theta * M_PI - M_PI_2)) * r2)) *
							SINF(t + psi) + braid->center_y;
						x_2 = ((0.5 * (1.0 + SINF((t + t_inc) / theta * M_PI - M_PI_2)) * r1 +
							0.5 * (1.0 + SINF((theta - t - t_inc) / theta * M_PI - M_PI_2)) * r2)) *
							COSF(t + t_inc + psi) + braid->center_x;
						y_2 = ((0.5 * (1.0 + SINF((t + t_inc) / theta * M_PI - M_PI_2)) * r1 +
							0.5 * (1.0 + SINF((theta - t - t_inc) / theta * M_PI - M_PI_2)) * r2)) *
							SINF(t + t_inc + psi) + braid->center_y;
						if (MI_NPIXELS(mi) > 2)
							XSetForeground(display, MI_GC(mi), MI_PIXEL(mi, (int) color_use));
						else
							XSetForeground(display, MI_GC(mi), MI_WHITE_PIXEL(mi));

						XDrawLine(display, window, MI_GC(mi),
							  (int) (x_1), (int) (y_1), (int) (x_2), (int) (y_2));
					}
				} else {
					/* no crosSINFg */
#ifdef COLORCOMP
					if (MI_NPIXELS(mi) > 2) {
						color_use = color + SPINRATE *
							braid->components[applywordbackto(braid, s, i)] +
							(psi + t) / 2.0 / M_PI * (float) MI_NPIXELS(mi);
						while (((int) color_use) >= MI_NPIXELS(mi))
							color_use -= (float) MI_NPIXELS(mi);
						while (((int) color_use) < 0)
							color_use += (float) MI_NPIXELS(mi);
					}
#endif
#ifdef COLORROUND
					if (MI_NPIXELS(mi) > 2) {
						color_use += SPINRATE * color_inc;
						while (((int) color_use) >= MI_NPIXELS(mi))
							color_use -= (float) MI_NPIXELS(mi);
					}
#endif
					r1 = braid->min_radius + r_diff * (float) (s);
					x_1 = r1 * COSF(t + psi) + braid->center_x;
					y_1 = r1 * SINF(t + psi) + braid->center_y;
					x_2 = r1 * COSF(t + t_inc + psi) + braid->center_x;
					y_2 = r1 * SINF(t + t_inc + psi) + braid->center_y;
					if (MI_NPIXELS(mi) > 2)
						XSetForeground(display, MI_GC(mi), MI_PIXEL(mi, (int) color_use));
					else
						XSetForeground(display, MI_GC(mi), MI_WHITE_PIXEL(mi));

					XDrawLine(display, window, MI_GC(mi),
						  (int) (x_1), (int) (y_1), (int) (x_2), (int) (y_2));
				}
			}
		}
	}
	XSetLineAttributes(display, MI_GC(mi), 1, LineSolid, CapNotLast, JoinRound);

	if (++braid->age > MI_CYCLES(mi)) {
#ifdef STANDALONE
      braid->eraser = erase_window (MI_DISPLAY(mi), MI_WINDOW(mi), braid->eraser);
#endif
		init_braid(mi);
	}
}