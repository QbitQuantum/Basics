rt_public void eif_show_console(void)
	/* Create a new DOS console if needed (i.e. in case of a Windows application. */
{
	if (!eif_console_allocated) {
		HANDLE eif_conin, eif_conout, eif_conerr;
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		BOOL bLaunched;
		int hCrt;
		STARTUPINFO l_info;
#ifndef EIF_BORLAND
		FILE *hf;
#endif
		RT_GET_CONTEXT

			/* Find out if the calling process has initialized the HANDLEs. */
		memset(&l_info, 0, sizeof(STARTUPINFO));
		GetStartupInfo(&l_info);
		if ((l_info.dwFlags & STARTF_USESTDHANDLES) != STARTF_USESTDHANDLES) {
			AllocConsole();
		}

			/* Get all default standard handles */
		eif_conin = GetStdHandle (STD_INPUT_HANDLE);
		eif_conout = GetStdHandle (STD_OUTPUT_HANDLE);
		eif_conerr = GetStdHandle (STD_ERROR_HANDLE);

			/* Check if handles are available, allocate console if not */
			/* Raise an I/O exception if we cannot get a valid handle */
		if ((eif_conin == 0) || (eif_conin == INVALID_HANDLE_VALUE)) {
			AllocConsole ();
			eif_conin = GetStdHandle (STD_INPUT_HANDLE);
		}
		if (eif_conin == INVALID_HANDLE_VALUE) {
			eio ();
		}
		if ((eif_conout == 0) || (eif_conout == INVALID_HANDLE_VALUE)){
			AllocConsole ();
			eif_conout = GetStdHandle (STD_OUTPUT_HANDLE);
		}
		if (eif_conout == INVALID_HANDLE_VALUE) {
			eio ();
		}
		if ((eif_conerr == 0) || (eif_conerr == INVALID_HANDLE_VALUE)) {
			AllocConsole ();
			eif_conerr = GetStdHandle (STD_ERROR_HANDLE);
		}
		if (eif_conerr == INVALID_HANDLE_VALUE) {
			eio ();
		}

			/* If console was manually created, we are most likely in
			 * a Windows application that tries to output something.
			 * Therefore we need to correctly associated all standard
			 * handles `stdin', `stdout' and `stderr' to the new
			 * created console.
			 * Code was adapted from http://codeguru.earthweb.com/console/Console.html
			 * But also checkout Microsoft support web site:
			 * 	http://support.microsoft.com/default.aspx?scid=kb;EN-US;q105305
			 * 
			 * Note: For Borland, the above trick does not work, one has to
			 *  duplicate the handle, unfortunately the solution does not work
			 *  with Microsoft which explains the ifdef statement.
			 */
		EIF_CONSOLE_LOCK;
		if (!eif_console_allocated) {
			if (_get_osfhandle (_fileno (stdout)) != (intptr_t) eif_conout) {
				hCrt = _open_osfhandle ((intptr_t) eif_conout, _O_TEXT);
#ifdef EIF_BORLAND
				dup2 (hCrt, _fileno(stdout));
#else
				hf = _fdopen (hCrt, "w");
				*stdout = *hf;
#endif
			  	setvbuf(stdout, NULL, _IONBF, 0);
			}

			if (_get_osfhandle (_fileno (stderr)) != (intptr_t) eif_conerr) {
				hCrt = _open_osfhandle ((intptr_t) eif_conerr, _O_TEXT);
#ifdef EIF_BORLAND
				dup2 (hCrt, _fileno(stderr));
#else
				hf = _fdopen (hCrt, "w");
				*stderr = *hf;
#endif
			  	setvbuf(stderr, NULL, _IONBF, 0);
			}

			if (_get_osfhandle (_fileno (stdin)) != (intptr_t) eif_conin) {
				hCrt = _open_osfhandle ((intptr_t) eif_conin, _O_TEXT | _O_RDONLY);
#ifdef EIF_BORLAND
				dup2 (hCrt, _fileno(stdin));
#else
				hf = _fdopen (hCrt, "r");
				*stdin = *hf;
#endif
			}

				/* We are computing the cursor position to figure out, if the application
				* has been launched from a DOS console or from the Windows Shell
				*/
			GetConsoleScreenBufferInfo(eif_conout, &csbi);
			bLaunched = ((csbi.dwCursorPosition.X == 0) && (csbi.dwCursorPosition.Y == 0));
			if ((csbi.dwSize.X <= 0) || (csbi.dwSize.Y <= 0))
				bLaunched = FALSE;

			if (bLaunched == TRUE)
				eif_register_cleanup (eif_console_cleanup);

			eif_console_allocated = TRUE;
		}
		EIF_CONSOLE_UNLOCK;
	}
}