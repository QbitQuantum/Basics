/**
 * \brief Timer event handler
 *
 * Given virtual function is called by the parent window whenever a timer is
 * fired. In the context of effect-enabled windows, the timer is used to
 * implement window slide-in and slide-out animations.
 *
 * \param idTimer Specifies the timer identifier
 */
void GuiEffectWindow::onTimer(int idTimer)
{
	s_thread_mutex_lock(effectMutex);

	// check if we have a stale timer event
	if(effectTimer == NULL)
	{
		#ifdef DEBUG
		printf("stale timer %d\n", idTimer);
		#endif
		s_thread_mutex_unlock(effectMutex);
		return;
	}

	#ifdef DEBUG
	printf("GuiEffectWindow::onTimer: %d locked\n", idTimer);
	#endif

	switch(idTimer)
	{
	case OPEN_EFFECT_SLIDE_BOTTOM:

		if(windowPos.y >= originalPos.y)
		{
			stopTimer(effectTimer);
			effectTimer = NULL;
			break;
		}

		windowPos.y += originalPos.y - windowPos.y < effectVertSpeed ?
				originalPos.y - windowPos.y : effectVertSpeed;

		if(windowPos.y >= originalPos.y)
			refreshRealSurface = true;

		setWindowPos(windowPos);
		break;

	case OPEN_EFFECT_SLIDE_RIGHT:

		if(windowPos.x >= originalPos.x)
		{
			stopTimer(effectTimer);
			effectTimer = NULL;
			break;
		}

		windowPos.x += originalPos.x - windowPos.x < effectHorzSpeed ?
				originalPos.x - windowPos.x : effectHorzSpeed;

		if(windowPos.x >= originalPos.x)
			refreshRealSurface = true;


		#ifdef DEBUG
		printf("GuiEffectWindow::onTimer: open %d %d %d %d\n",
				windowPos.x, windowPos.y, windowPos.w, windowPos.h);
		#endif
		setWindowPos(windowPos);
		break;

	case OPEN_EFFECT_SLIDE_TOP:

		if(windowPos.y <= originalPos.y)
		{
			stopTimer(effectTimer);
			effectTimer = NULL;
			break;
		}

		windowPos.y -= windowPos.y - originalPos.y < effectVertSpeed ?
				windowPos.y - originalPos.y : effectVertSpeed;

		if(windowPos.y <= originalPos.y)
			refreshRealSurface = true;

		setWindowPos(windowPos);
		break;

	case OPEN_EFFECT_SLIDE_LEFT:

		if(windowPos.x <= originalPos.x)
		{
			stopTimer(effectTimer);
			effectTimer = NULL;
			break;
		}

		windowPos.x -= windowPos.x - originalPos.x < effectHorzSpeed ?
				windowPos.x - originalPos.x : effectHorzSpeed;

		if(windowPos.x <= originalPos.x)
			refreshRealSurface = true;

		setWindowPos(windowPos);
		break;

	case CLOSE_EFFECT_SLIDE_BOTTOM:

		if(windowPos.y >= wndHandle->surface->height)
		{
			stopTimer(effectTimer);
			effectTimer = NULL;

			if(showWindowType == HIDE_WINDOW)
			{
				s_window_hide(wndHandle);
			}
			else if(showWindowType == CLOSE_WINDOW)
			{
				returnCode = closeRetCode;
				isShuttingDown = true;
				s_window_quit(wndHandle);
			}
			break;
		}

		windowPos.y += effectVertSpeed;
		setWindowPos(windowPos);
		break;

	case CLOSE_EFFECT_SLIDE_RIGHT:

		if(windowPos.x >= wndHandle->surface->width)
		{
			stopTimer(effectTimer);
			effectTimer = NULL;

			if(showWindowType == HIDE_WINDOW)
			{
				s_window_hide(wndHandle);
			}
			else if(showWindowType == CLOSE_WINDOW)
			{
				returnCode = closeRetCode;
				isShuttingDown = true;
				s_window_quit(wndHandle);
			}
			break;
		}

		windowPos.x += effectHorzSpeed;

		#ifdef DEBUG
		printf("GuiEffectWindow::onTimer: close %d %d %d %d\n",
				windowPos.x, windowPos.y, windowPos.w, windowPos.h);
		#endif

		setWindowPos(windowPos);
		break;

	case CLOSE_EFFECT_SLIDE_TOP:

		if(windowPos.y + windowPos.h <= 0)
		{
			stopTimer(effectTimer);
			effectTimer = NULL;

			if(showWindowType == HIDE_WINDOW)
			{
				s_window_hide(wndHandle);
			}
			else if(showWindowType == CLOSE_WINDOW)
			{
				returnCode = closeRetCode;
				isShuttingDown = true;
				s_window_quit(wndHandle);
			}
			break;
		}

		windowPos.y -= effectVertSpeed;
		setWindowPos(windowPos);
		break;

	case CLOSE_EFFECT_SLIDE_LEFT:

		if(windowPos.x + windowPos.w <= 0)
		{
			stopTimer(effectTimer);
			effectTimer = NULL;

			if(showWindowType == HIDE_WINDOW)
			{
				s_window_hide(wndHandle);
			}
			else if(showWindowType == CLOSE_WINDOW)
			{
				returnCode = closeRetCode;
				isShuttingDown = true;
				s_window_quit(wndHandle);
			}
			break;
		}

		windowPos.x -= effectHorzSpeed;
		setWindowPos(windowPos);
		break;
	}

	s_thread_mutex_unlock(effectMutex);
	#ifdef DEBUG
	printf("GuiEffectWindow::onTimer: %d unlocked\n", idTimer);
	#endif
}