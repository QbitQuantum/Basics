static void handle_mouse(const int numevents, DIDEVICEOBJECTDATA *ptrbuf)
{
	int i;
	Sint16 xrel, yrel;
	Uint8 state;
	Uint8 button;
	DWORD timestamp = 0;

	/* Sanity check. Mailing list reports this being NULL unexpectedly. */
	if (SDL_PublicSurface == NULL) {
		return;
	}

	/* If the mouse was lost, regain some sense of mouse state */
	if ( mouse_lost && (SDL_GetAppState() & SDL_APPMOUSEFOCUS) ) {
		POINT mouse_pos;
		Uint8 old_state;
		Uint8 new_state;

		/* Set ourselves up with the current cursor position */
		GetCursorPos(&mouse_pos);
		ScreenToClient(SDL_Window, &mouse_pos);
		post_mouse_motion( 0, (Sint16)mouse_pos.x, (Sint16)mouse_pos.y);

		/* Check for mouse button changes */
		old_state = SDL_GetMouseState(NULL, NULL);
		new_state = 0;
		{ /* Get the new DirectInput button state for the mouse */
#if DIRECTINPUT_VERSION >= 0x700
			DIMOUSESTATE2 distate;
#else
			DIMOUSESTATE distate;
#endif
			HRESULT result;

			result=IDirectInputDevice2_GetDeviceState(SDL_DIdev[1],
						sizeof(distate), &distate);
			if ( result != DI_OK ) {
				/* Try again next time */
				SetDIerror(
				"IDirectInputDevice2::GetDeviceState", result);
				return;
			}
			for ( i=3; i>=0; --i ) {
				if ( (distate.rgbButtons[i]&0x80) == 0x80 ) {
					new_state |= 0x01;
				}
				new_state <<= 1;
			}
		}
		for ( i=0; i<8; ++i ) {
			if ( (old_state&0x01) != (new_state&0x01) ) {
				button = (Uint8)(i+1);
				/* Map DI button numbers to SDL */
				switch ( button ) {
					case 2: button = SDL_BUTTON_RIGHT; break;
					case 3: button = SDL_BUTTON_MIDDLE; break;
					case 4: button = SDL_BUTTON_X1; break;
					case 5: button = SDL_BUTTON_X2; break;
					default: break;
				}
				if ( new_state & 0x01 ) {
					/* Grab mouse so we get mouse-up */
					if ( ++mouse_pressed > 0 ) {
						SetCapture(SDL_Window);
					}
					state = SDL_PRESSED;
				} else {
					/* Release mouse after all mouse-ups */
					if ( --mouse_pressed <= 0 ) {
						ReleaseCapture();
						mouse_pressed = 0;
					}
					state = SDL_RELEASED;
				}
				if ( mouse_buttons_swapped ) {
					if ( button == 1 ) button = 3;
					else
					if ( button == 3 ) button = 1;
				}
				posted = SDL_PrivateMouseButton(state, button,
									0, 0);
			}
			old_state >>= 1;
			new_state >>= 1;
		}
		mouse_lost = 0;
		return;
	}