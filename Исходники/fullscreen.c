gboolean xmms_fullscreen_enter(GtkWidget * win, gint * w, gint * h)
{
	gint i, close, how_close = -1, t, dummy;
	gboolean retval = FALSE;
	fullscreen_window_t *fwin;

	FULL_LOCK();
	fwin = getwindow(win);

	if (!fwin->display->is_full && !fwin->is_full
	    && fwin->display->can_full)
	{
		for (close = 0; close < fwin->display->num_modes; close++)
		{
			if ((fwin->display->modes[close]->hdisplay >= *w) &&
			    (fwin->display->modes[close]->vdisplay >= *h))
			{
				how_close = fwin->display->modes[close]->hdisplay - *w;
				break;
			}
		}

		for (i = close + 1; i < fwin->display->num_modes; i++)
		{
			if (fwin->display->modes[i]->vdisplay < *h)
				continue;
			t = fwin->display->modes[i]->hdisplay - *w;
			if (t >= 0 && t < how_close)
			{
				close = i;
				how_close = t;
			}
		}

		if (close < fwin->display->num_modes)
		{
			*w = fwin->display->modes[close]->hdisplay;
			*h = fwin->display->modes[close]->vdisplay;

			/* Save the old position/size */
			gdk_window_get_root_origin(fwin->window->window, &fwin->ox, &fwin->oy);
			gdk_window_get_size(fwin->window->window, &fwin->owidth, &fwin->oheight);

			/* Move it. */
			gdk_window_move_resize(fwin->window->window, 0, 0,
					       fwin->display->modes[close]->hdisplay,
					       fwin->display->modes[close]->vdisplay);

			/* Tell the WM not to mess with this window (no more decor) */
			gdk_window_hide(fwin->window->window);
			gdk_window_set_override_redirect(fwin->window->window, TRUE);
			gdk_window_show(fwin->window->window);

			/*
			 * XXX: HACK
			 * Something is ungrabbing the pointer shortly
			 * after the above unmap/override_redirect=TRUE/map
			 * is done.  I don't know what at this time, only
			 * that it's not XMMS, and that it's very very evil.
			 */
			gdk_flush();
			xmms_usleep(50000);

			/* Steal the keyboard/mouse */
			/* XXX: FIXME, use timeouts.. */
			for (t = 0; t < 10; t++)
			{
				dummy = gdk_pointer_grab(fwin->window->window,
							 TRUE, 0,
							 fwin->window->window,
							 NULL,
							 GDK_CURRENT_TIME);

				if (dummy == GrabSuccess)
					break;

				gtk_main_iteration_do(FALSE);
				xmms_usleep(10000);
			}
			gdk_keyboard_grab(fwin->window->window, TRUE,
					  GDK_CURRENT_TIME);

			/* Do the video mode switch.. */
			XF86VidModeSwitchToMode(fwin->display->display,
						DefaultScreen(fwin->display->display),
						fwin->display->modes[close]);

			XF86VidModeSetViewPort(fwin->display->display,
					       DefaultScreen(fwin->display->display),
					       0, 0);

			retval = TRUE;

			fwin->is_full = TRUE;
			fwin->display->is_full = TRUE;
		}
	}

	FULL_UNLOCK();

	return retval;
}