int kbhit(void)
{
	 INPUT_RECORD inp;
	 DWORD nread, nevents;
	 HANDLE hin;

    if (_cFlag)             /* has a character been ungetch'd? */
        return (1);

    hin = GetStdHandle(STD_INPUT_HANDLE);

    /* Discard console events until we come to a keydown event,
	  * or the event queue is empty.
	  */
	 while (GetNumberOfConsoleInputEvents(hin, &nevents) == TRUE && nevents > 0)
	 {
		  /* Take a look at the first input event in the queue.
			* If we can't peek at it, something bad happened.
			*/
		  if (PeekConsoleInput(hin, &inp, 1, &nread) != TRUE)
				break;

		  /* If the event is a key-down, a key has been hit.
			*/
		  if ((inp.EventType & KEY_EVENT) != 0 &&
				 inp.Event.KeyEvent.bKeyDown != 0)
				{
				dwControlKeyState = inp.Event.KeyEvent.dwControlKeyState;
				return (1);
				}

		  /* It's not a key-down event, discard it.
			* NOTE: this discards all other console input events, including
			* mouse events!  Thus, kbhit() should not be used in programs
			* that track the mouse or window resizing.
			*/
		  if (ReadConsoleInput(hin, &inp, 1, &nread) != TRUE)
				break;
	 }
	 return (0);
}