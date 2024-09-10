void __cdecl SilAssert (
		const char * expr,
		const char * filename,
		unsigned lineno
		)
{
	/*
	 * Build the assertion message, then display it.
	 */
	int nCode = IDIGNORE;
	char * pch;
	char assertbuf[ASSERTBUFSZ];
	char progname[MAX_PATH + 1];

	/*
		* Line 1: box intro line
		*/
	strcpy_s( assertbuf, ASSERTBUFSZ, BOXINTRO );
	strcat_s( assertbuf, ASSERTBUFSZ, dblnewline );

#if WIN32
	// TODO-Linux: Find filename of managed executable
	/*
		* Line 2: program line
		*/
	strcat_s( assertbuf, ASSERTBUFSZ, PROGINTRO );

	progname[MAX_PATH] = '\0';
	if ( !GetModuleFileName( NULL, progname, MAX_PATH ))
		strcpy_s( progname, ASSERTBUFSZ, "<program name unknown>");

	pch = (char *)progname;

	/* sizeof(PROGINTRO) includes the NULL terminator */
	if ( sizeof(PROGINTRO) + strlen(progname) + NEWLINESZ > MAXLINELEN )
	{
		int cch = (sizeof(PROGINTRO) + strlen(progname) + NEWLINESZ) - MAXLINELEN;
		pch += cch;
		strncpy_s( pch, sizeof(progname) - cch, dotdotdot, DOTDOTDOTSZ );
	}

	strcat_s( assertbuf, ASSERTBUFSZ, pch );
	strcat_s( assertbuf, ASSERTBUFSZ, newline );
#endif

	/*
		* Line 3: file line
		*/
	strcat_s( assertbuf, ASSERTBUFSZ, FILEINTRO );

	/* sizeof(FILEINTRO) includes the NULL terminator */
	if ( sizeof(FILEINTRO) + strlen(filename) + NEWLINESZ > MAXLINELEN )
	{
		size_t p, len, ffn;

		pch = (char *) filename;
		ffn = MAXLINELEN - sizeof(FILEINTRO) - NEWLINESZ;

		for ( len = strlen(filename), p = 1;
				pch[len - p] != '\\' && pch[len - p] != '/' && p < len;
				p++ );

		/* keeping pathname almost 2/3rd of full filename and rest
			* is filename
			*/
		if ( (ffn - ffn/3) < (len - p) && ffn/3 > p )
		{
			/* too long. using first part of path and the
				filename string */
			strncat_s( assertbuf, ASSERTBUFSZ, pch, ffn - DOTDOTDOTSZ - p );
			strcat_s( assertbuf, ASSERTBUFSZ, dotdotdot );
			strcat_s( assertbuf, ASSERTBUFSZ, pch + len - p );
		}
		else if ( ffn - ffn/3 > len - p )
		{
			/* pathname is smaller. keeping full pathname and putting
				* dotdotdot in the middle of filename
				*/
			p = p/2;
			strncat_s( assertbuf, ASSERTBUFSZ, pch, ffn - DOTDOTDOTSZ - p );
			strcat_s( assertbuf, ASSERTBUFSZ, dotdotdot );
			strcat_s( assertbuf, ASSERTBUFSZ, pch + len - p );
		}
		else
		{
			/* both are long. using first part of path. using first and
				* last part of filename.
				*/
			strncat_s( assertbuf, ASSERTBUFSZ, pch, ffn - ffn/3 - DOTDOTDOTSZ );
			strcat_s( assertbuf, ASSERTBUFSZ, dotdotdot );
			strncat_s( assertbuf, ASSERTBUFSZ, pch + len - p, ffn/6 - 1 );
			strcat_s( assertbuf, ASSERTBUFSZ, dotdotdot );
			strcat_s( assertbuf, ASSERTBUFSZ, pch + len - (ffn/3 - ffn/6 - 2) );
		}

	}
	else
		/* plenty of room on the line, just append the filename */
		strcat_s( assertbuf, ASSERTBUFSZ, filename );

	strcat_s( assertbuf, ASSERTBUFSZ, newline );

	/*
		* Line 4: line line
		*/
	strcat_s( assertbuf, ASSERTBUFSZ, LINEINTRO );
	_itoa_s( lineno, assertbuf + strlen(assertbuf), sizeof(assertbuf) - strlen(assertbuf), 10 );
	strcat_s( assertbuf, ASSERTBUFSZ, dblnewline );

	/*
		* Line 5: message line
		*/
	strcat_s( assertbuf, ASSERTBUFSZ, EXPRINTRO );

	/* sizeof(HELPINTRO) includes the NULL terminator */

	if (    strlen(assertbuf) +
			strlen(expr) +
			2*DBLNEWLINESZ +
			sizeof(INFOINTRO)-1 +
			sizeof(HELPINTRO) > ASSERTBUFSZ )
	{
		strncat_s( assertbuf, ASSERTBUFSZ,
			expr,
			ASSERTBUFSZ -
			(strlen(assertbuf) +
			DOTDOTDOTSZ +
			2*DBLNEWLINESZ +
			sizeof(INFOINTRO)-1 +
			sizeof(HELPINTRO)) );
		strcat_s( assertbuf, ASSERTBUFSZ, dotdotdot );
	}
	else
		strcat_s( assertbuf, ASSERTBUFSZ, expr );

	strcat_s( assertbuf, ASSERTBUFSZ, dblnewline );

	/*
		* Line 6, 7: info line
		*/

	strcat_s(assertbuf, ASSERTBUFSZ, INFOINTRO);
	strcat_s( assertbuf, ASSERTBUFSZ, dblnewline );

	/*
		* Line 8: help line
		*/
	strcat_s(assertbuf, ASSERTBUFSZ, HELPINTRO);

	// SIL addition: log the message using OutputDebugString

	if (g_ReportHook)
		g_ReportHook(_CRT_ASSERT, assertbuf);
	else
		OutputDebugString(assertbuf);

	// NOTE: this method is intented to be used by unmanaged apps only;
	// managed apps should use DebugProcs.AssertProc in DebugProcs.cs

	/*
	 * Write out via MessageBox
	 */
	if (g_fShowMessageBox)
	{
		nCode = MessageBoxA(NULL, assertbuf,
			"SIL Program Failure warning (Assert failed)",
			MB_ABORTRETRYIGNORE|MB_ICONHAND|MB_SETFOREGROUND|MB_TASKMODAL);

		/* Abort: abort the program */
		if (nCode == IDABORT)
		{
			/* raise abort signal */
			raise(SIGABRT);

			/* We usually won't get here, but it's possible that
				SIGABRT was ignored.  So exit the program anyway. */

			_exit(3);
		}

		/* Retry: call the debugger */
		if (nCode == IDRETRY)
		{
#if WIN32
			_DbgBreak();
#else
			raise(SIGTRAP);
#endif
			/* return to user code */
			return;
		}

		if (nCode != IDIGNORE)
			abort();
	}
	else // !g_fShowMessageBox
	{
		// if we don't show a message box we should at least abort (and output the assertion
		// text if we haven't done that already). Note that we don't call _exit(3) as above
		// so that we can trap the signal and ignore it in unit tests
		if (g_ReportHook)
			OutputDebugString(assertbuf);
		raise(SIGABRT);
	}

	/* Ignore: continue execution */
	return;
}