i32 xwl_pollevent( xwl_event_t *event )
{
#ifdef _WIN32
	MSG msg;

	while ( PeekMessage( &msg, 0, 0, 0, PM_REMOVE ) )
	{
		TranslateMessage( &msg );
		DispatchMessage( &msg );
	}
#endif

#if LINUX
    XEvent ev;
    i32 i;
    xwl_window_handle_t *wh = 0;
    XEvent lastKeyReleaseEvent;

    for( i = 0; i < XWL_MAX_WINDOW_HANDLES; ++i )
    {
        wh = &xwl_windowHandles[i];
        if ( wh->handle.handle != 0 )
        {
            while (XCheckIfEvent( currentDisplay, &ev, &CheckEvent, wh->handle.handle) )
            {
                if ((ev.type == KeyPress) || (ev.type == KeyRelease) )
                {
                    if ( ev.xkey.keycode < 256 )
                    {
                        // To detect if it is a repeated key event, we check the current state of the key.
                        // - If the state is "down", KeyReleased events must obviously be discarded.
                        // - KeyPress events are a little bit harder to handle: they depend on the EnableKeyRepeat state,
                        //   and we need to properly forward the first one.
                        char keys[32];
                        XQueryKeymap(currentDisplay, keys);
                        if (keys[ev.xkey.keycode >> 3] & (1 << (ev.xkey.keycode % 8)))
                        {
                            // KeyRelease event + key down = repeated event --> discard
                            if (ev.type == KeyRelease)
                            {
                                lastKeyReleaseEvent = ev;
                                continue;
                            }

                            // KeyPress event + key repeat disabled + matching KeyRelease event = repeated event --> discard
                            if ((ev.type == KeyPress) &&
                                (lastKeyReleaseEvent.xkey.keycode == ev.xkey.keycode) &&
                                (lastKeyReleaseEvent.xkey.time == ev.xkey.time))
                            {
                                continue;
                            }
                        }
                    }
                }

                ProcessEvent( ev, wh );
            }
        }
    }