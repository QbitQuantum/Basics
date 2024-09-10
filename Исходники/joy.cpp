// --------------------------------------------------------------
//	joy_process()
//
// Runs as a separate thread, and updates the state of the joystick
//
DWORD joy_process(DWORD lparam)
{
	MMRESULT		rs;
	JOYINFOEX	ji;
	int			i,state;
	joy_button_info	*bi;	

	for ( i = 0; i < JOY_TOTAL_BUTTONS; i++) {
		bi = &joy_buttons[i];
		bi->actual_state = 0;		// Don't set in flush code!
		bi->state		= 0;
		bi->down_count	= 0;
		bi->up_count	= 0;
		bi->down_time	= 0;
		bi->last_down_check = timer_get_milliseconds();
	}

	while (1) {
		// Wait for the thread to be signaled to end or 1/18th of a second to pass...
		if ( WaitForSingleObject( Joy_tell_thread_to_end_event, joy_pollrate )==WAIT_OBJECT_0)	{
			break;
		}

		memset(&ji, 0, sizeof(ji));
		ji.dwSize = sizeof(ji);
//		ji.dwFlags = JOY_RETURNBUTTONS | JOY_RETURNRAWDATA;
		ji.dwFlags = JOY_RETURNALL;

		EnterCriticalSection(&joy_lock);

		uint joy_state = 0;
		if (Cur_joystick >= 0) {
			rs = joyGetPosEx(Cur_joystick, &ji);
			// If there's an error, assume all buttons down.
			if (rs == JOYERR_NOERROR) {
				joy_state = ji.dwButtons;
			}
		}

		// Process ji.dwButtons
		for (i=0; i<JOY_TOTAL_BUTTONS; i++) {
			state = 0;
			if (i < JOY_NUM_BUTTONS) {
				state = joy_state & (1<<i);

			} else {
				// check for hat presses, which act like buttons
				switch (i) {
					case JOY_HATBACK:
						if (ji.dwPOV == JOY_POVBACKWARD)
							state = 1;
						break;

					case JOY_HATFORWARD:
						if (ji.dwPOV == JOY_POVFORWARD)
							state = 1;
						break;

					case JOY_HATLEFT:
						if (ji.dwPOV == JOY_POVLEFT)
							state = 1;
						break;

					case JOY_HATRIGHT:
						if (ji.dwPOV == JOY_POVRIGHT)
							state = 1;
						break;

					default:
						Int3();	// should never happen
						break;

				}	// end switch
			}	// end if


			if (state != joy_buttons[i].actual_state) {
				// Button position physically changed.
				joy_buttons[i].actual_state = state;

				if ( state )	{
					// went from up to down
					joy_buttons[i].down_count++;
					joy_buttons[i].down_time = 0;

					joy_buttons[i].state = 1;

////////////////////////////
/// SOMETHING TERRIBLE IS ABOUT TO HAPPEN.  I FEEL THIS IS NECESSARY FOR THE DEMO, SINCE
/// I DON'T WANT TO CALL CRITICAL SECTION CODE EACH FRAME TO CHECK ALL THE JOYSTICK BUTTONS.
/// PLEASE SEE ALAN FOR MORE INFORMATION.
////////////////////////////
#ifdef FS2_DEMO
					{
					extern void demo_reset_trailer_timer();
					demo_reset_trailer_timer();
					}
#endif
////////////////////////////
/// IT'S OVER.  SEE, IT WASN'T SO BAD RIGHT?  IT'S IS VERY UGLY LOOKING, I KNOW.
////////////////////////////


				} else {
					// went from down to up
					if ( joy_buttons[i].state )	{
						joy_buttons[i].up_count++;
					}
					joy_buttons[i].state = 0;
				}

			} else {
				// Didn't move... increment time down if down.
				if (joy_buttons[i].state) {
					joy_buttons[i].down_time += joy_pollrate;
				}
			}

		}  // end for

		LeaveCriticalSection(&joy_lock);
	}

	SetEvent(Joy_thread_says_its_done_event);	

	return 0;
}