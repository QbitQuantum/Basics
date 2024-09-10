ENTRYPOINT void
draw_rotor (ModeInfo * mi)
{
	Display    *display = MI_DISPLAY(mi);
	GC          gc = MI_GC(mi);
	register elem *pelem;
	int         thisx, thisy;
	int         i;
	int         x_1, y_1, x_2, y_2;
	rotorstruct *rp;

	if (rotors == NULL)
		return;
	rp = &rotors[MI_SCREEN(mi)];
	if (rp->elements == NULL)
		return;

	MI_IS_DRAWN(mi) = True;
	if (!rp->iconifiedscreen) {
		thisx = rp->centerx;
		thisy = rp->centery;
	} else {
		thisx = rp->prevcenterx;
		thisy = rp->prevcentery;
	}
	XSetLineAttributes(MI_DISPLAY(mi), MI_GC(mi), rp->linewidth,
			   LineSolid, CapButt, JoinMiter);
	for (i = rp->num, pelem = rp->elements; --i >= 0; pelem++) {
		if (pelem->radius_drift_max <= pelem->radius_drift_now) {
			pelem->start_radius = pelem->end_radius;
			pelem->end_radius = (float) NRAND(40000) / 100.0 - 200.0;
			pelem->radius_drift_max = (float) NRAND(100000) + 10000.0;
			pelem->radius_drift_now = 0.0;
		}
		if (pelem->ratio_drift_max <= pelem->ratio_drift_now) {
			pelem->start_ratio = pelem->end_ratio;
			pelem->end_ratio = (float) NRAND(2000) / 100.0 - 10.0;
			pelem->ratio_drift_max = (float) NRAND(100000) + 10000.0;
			pelem->ratio_drift_now = 0.0;
		}
		pelem->ratio = pelem->start_ratio +
			(pelem->end_ratio - pelem->start_ratio) /
			pelem->ratio_drift_max * pelem->ratio_drift_now;
		pelem->angle = rp->angle * pelem->ratio;
		pelem->radius = pelem->start_radius +
			(pelem->end_radius - pelem->start_radius) /
			pelem->radius_drift_max * pelem->radius_drift_now;

		thisx += (int) (COSF(pelem->angle) * pelem->radius);
		thisy += (int) (SINF(pelem->angle) * pelem->radius);

		pelem->ratio_drift_now += 1.0;
		pelem->radius_drift_now += 1.0;
	}
	if (rp->firsttime)
		rp->firsttime = False;
	else {
		XSetForeground(display, gc, MI_BLACK_PIXEL(mi));

		x_1 = (int) rp->save[rp->rotor].x;
		y_1 = (int) rp->save[rp->rotor].y;
		x_2 = (int) rp->save[rp->prev].x;
		y_2 = (int) rp->save[rp->prev].y;

		if (rp->iconifiedscreen) {
			x_1 = x_1 * rp->centerx / rp->prevcenterx;
			x_2 = x_2 * rp->centerx / rp->prevcenterx;
			y_1 = y_1 * rp->centery / rp->prevcentery;
			y_2 = y_2 * rp->centery / rp->prevcentery;
		}
		XDrawLine(display, MI_WINDOW(mi), gc, x_1, y_1, x_2, y_2);

		if (MI_NPIXELS(mi) > 2) {
			XSetForeground(display, gc, MI_PIXEL(mi, rp->pix));
			if (++rp->pix >= MI_NPIXELS(mi))
				rp->pix = 0;
		} else
			XSetForeground(display, gc, MI_WHITE_PIXEL(mi));

		x_1 = rp->lastx;
		y_1 = rp->lasty;
		x_2 = thisx;
		y_2 = thisy;

		if (rp->iconifiedscreen) {
			x_1 = x_1 * rp->centerx / rp->prevcenterx;
			x_2 = x_2 * rp->centerx / rp->prevcenterx;
			y_1 = y_1 * rp->centery / rp->prevcentery;
			y_2 = y_2 * rp->centery / rp->prevcentery;
		}
		XDrawLine(display, MI_WINDOW(mi), gc, x_1, y_1, x_2, y_2);
	}
	rp->save[rp->rotor].x = rp->lastx = thisx;
	rp->save[rp->rotor].y = rp->lasty = thisy;

	++rp->rotor;
	rp->rotor %= rp->nsave;
	++rp->prev;
	rp->prev %= rp->nsave;
	if (rp->forward) {
		rp->angle += 0.01;
		if (rp->angle >= MAXANGLE) {
			rp->angle = MAXANGLE;
			rp->forward = False;
		}
	} else {
		rp->angle -= 0.1;
		if (rp->angle <= 0) {
			rp->angle = 0.0;
			rp->forward = True;
		}
	}
	if (rp->redrawing) {
		int         j;

		for (i = 0; i < REDRAWSTEP; i++) {
			j = (rp->rotor - rp->redrawpos + rp->nsave) % rp->nsave;

			x_1 = (int) rp->save[j].x;
			y_1 = (int) rp->save[j].y;
			x_2 = (int) rp->save[(j - 1 + rp->nsave) % rp->nsave].x;
			y_2 = (int) rp->save[(j - 1 + rp->nsave) % rp->nsave].y;

			if (rp->iconifiedscreen) {
				x_1 = x_1 * rp->centerx / rp->prevcenterx;
				x_2 = x_2 * rp->centerx / rp->prevcenterx;
				y_1 = y_1 * rp->centery / rp->prevcentery;
				y_2 = y_2 * rp->centery / rp->prevcentery;
			}
			XDrawLine(display, MI_WINDOW(mi), gc, x_1, y_1, x_2, y_2);

			if (++(rp->redrawpos) >= rp->nsave) {
				rp->redrawing = 0;
				break;
			}
		}
	}
	XSetLineAttributes(MI_DISPLAY(mi), MI_GC(mi), 1,
			   LineSolid, CapButt, JoinMiter);
}