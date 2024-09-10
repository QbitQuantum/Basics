/*  Handle the velocity */
static void
throwPreparePaintScreen (CompScreen *s,
			int        ms)
{
    CompWindow *w;
    THROW_SCREEN (s);

    for (w = s->windows; w; w = w->next)
    {
	THROW_WINDOW (w);

	if (tw->moving)
	    tw->time += ms;

        tw->xVelocity /= (1.0 + (throwGetFrictionConstant (s) / 100));
	tw->yVelocity /= (1.0 + (throwGetFrictionConstant (s) / 100));

	if (!tw->moving && (
	    (tw->xVelocity < 0.0f || tw->xVelocity > 0.0f) ||
	    (tw->yVelocity < 0.0f || tw->yVelocity > 0.0)))
	{
	    int dx = roundf(tw->xVelocity * (ms / 10) * (throwGetVelocityX (s) / 10));
	    int dy = roundf (tw->yVelocity * (ms / 10) * (throwGetVelocityY (s) / 10));

	    if (throwGetConstrainX (s))
	    {
		if ((WIN_REAL_X (w) + dx) < 0)
		    dx = 0;
		else if ((WIN_REAL_X (w) + WIN_REAL_W (w) + dx) > w->screen->width)
		    dx = 0;
	    }
	    if (throwGetConstrainY (s))
	    {
		if ((WIN_REAL_Y (w) + dy) < 0)
		    dy = 0;
		else if ((WIN_REAL_Y (w) + WIN_REAL_H (w) + dy) > w->screen->height)
		    dy = 0;
	    }

	    moveWindow (w, dx, dy, TRUE, FALSE);
	    syncWindowPosition (w);
	}

    }

    UNWRAP (ts, s, preparePaintScreen);
    (*s->preparePaintScreen) (s, ms);
    WRAP (ts, s, preparePaintScreen, throwPreparePaintScreen);
}