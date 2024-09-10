/*
 * Setup for paint screen
 */
static void
smartputPreparePaintScreen (CompScreen *s,
			    int        msSinceLastPaint)
{
    SMARTPUT_SCREEN (s);

    if (sps->animation && sps->grabIndex)
    {
	CompWindow *w;
	int        stesps;
	float      amount, chunk;

	amount = msSinceLastPaint * 0.025f * 2.5;
	stesps = amount / (0.5f * 0.5);
	if (!stesps)
	    stesps = 1;
	chunk = amount / (float)stesps;

	while (stesps--)
	{
	    Window endAnimationWindow = None;

	    sps->animation = 0;
	    for (w = s->windows; w; w = w->next)
	    {
		SMARTPUT_WINDOW (w);

		if (spw->animation)
		{
		    spw->animation = adjustSmartputVelocity (w);
		    sps->animation |= spw->animation;

		    spw->tx += spw->xVelocity * chunk;
		    spw->ty += spw->yVelocity * chunk;

		    if (!spw->animation)
		    {
			/* animation done */
			moveWindow (w, spw->targetX - w->attrib.x,
				    spw->targetY - w->attrib.y, TRUE, TRUE);
			syncWindowPosition (w);
			updateWindowAttributes (w, CompStackingUpdateModeNone);
			endAnimationWindow = w->id;
			spw->tx = spw->ty = 0;
		    }
		}
	    }
	    if (!sps->animation)
	    {
		/* unfocus moved window if enabled */
		if (endAnimationWindow)
		    sendWindowActivationRequest (s, endAnimationWindow);
		break;
	    }
	}
    }

    UNWRAP (sps, s, preparePaintScreen);
    (*s->preparePaintScreen) (s, msSinceLastPaint);
    WRAP (sps, s, preparePaintScreen, smartputPreparePaintScreen);
}