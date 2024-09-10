void __cdecl _ioinit (
        void
        )
{
        STARTUPINFO StartupInfo;
        int cfi_len;
	int fh;
	int i;
	ioinfo *pio;
	char *posfile;
	UNALIGNED long *posfhnd;
	long stdfh;
        DWORD htype;

	/*
	 * Allocate and initialize the first array of ioinfo structs. This
	 * array is pointed to by __pioinfo[0]
	 */
	if ( (pio = _malloc_crt( IOINFO_ARRAY_ELTS * sizeof(ioinfo) ))
	     == NULL )
	{
	    _amsg_exit( _RT_LOWIOINIT );
	}

	__pioinfo[0] = pio;
	_nhandle = IOINFO_ARRAY_ELTS;

	for ( ; pio < __pioinfo[0] + IOINFO_ARRAY_ELTS ; pio++ ) {
	    pio->osfile = 0;
	    pio->osfhnd = (long)INVALID_HANDLE_VALUE;
	    pio->pipech = 10;			/* linefeed/newline char */
#if     defined(_MT) && !defined(DLL_FOR_WIN32S)
	    pio->lockinitflag = 0;		/* uninitialized lock */
#endif
	}

        /*
         * Process inherited file handle information, if any
	 */
        GetStartupInfo( &StartupInfo );

	if ( (StartupInfo.cbReserved2 != 0) &&
	     (StartupInfo.lpReserved2 != NULL) )
	{
            /*
             * Get the number of handles inherited.
             */
	    cfi_len = *(UNALIGNED int *)(StartupInfo.lpReserved2);

	    /*
	     * Set pointers to the start of the passed file info and OS
	     * HANDLE values.
	     */
	    posfile = (char *)(StartupInfo.lpReserved2) + sizeof( int );
	    posfhnd = (UNALIGNED long *)(posfile + cfi_len);

	    /*
	     * Ensure cfi_len does not exceed the number of supported
	     * handles!
	     */
	    cfi_len = __min( cfi_len, _NHANDLE_ );

	    /*
	     * Allocate sufficient arrays of ioinfo structs to hold inherited
	     * file information.
	     */
	    for ( i = 1 ; _nhandle < cfi_len ; i++ ) {

		/*
		 * Allocate another array of ioinfo structs
		 */
		if ( (pio = _malloc_crt( IOINFO_ARRAY_ELTS * sizeof(ioinfo) ))
		    == NULL )
		{
		    /*
		     * No room for another array of ioinfo structs, reduce
		     * the number of inherited handles we process.
		     */
		    cfi_len = _nhandle;
		    break;
		}

		/*
		 * Update __pioinfo[] and _nhandle
		 */
		__pioinfo[i] = pio;
		_nhandle += IOINFO_ARRAY_ELTS;

		for ( ; pio < __pioinfo[i] + IOINFO_ARRAY_ELTS ; pio++ ) {
		    pio->osfile = 0;
		    pio->osfhnd = (long)INVALID_HANDLE_VALUE;
		    pio->pipech = 10;
#if     defined(_MT) && !defined(DLL_FOR_WIN32S)
		    pio->lockinitflag = 0;
#endif
		}
	    }

	    /*
	     * Validate and copy the passed file information
	     */
	    for ( fh = 0 ; fh < cfi_len ; fh++, posfile++, posfhnd++ ) {
		/*
		 * Copy the passed file info iff it appears to describe
		 * an open, valid file.
		 */
		if ( (*posfhnd != (long)INVALID_HANDLE_VALUE) &&
		     (*posfile & FOPEN) && (GetFileType( (HANDLE)(*posfhnd) )
		      != FILE_TYPE_UNKNOWN) )
		{
		    pio = _pioinfo( fh );
		    pio->osfhnd = *posfhnd;
		    pio->osfile = *posfile;
		}
	    }
	}

        /*
	 * If valid HANDLE-s for standard input, output and error were not
	 * inherited, try to obtain them directly from the OS. Also, set the
	 * appropriate bits in the osfile fields.
         */
	for ( fh = 0 ; fh < 3 ; fh++ ) {

            pio = __pioinfo[0] + fh;

	    if ( pio->osfhnd == (long)INVALID_HANDLE_VALUE ) {
		/*
		 * mark the handle as open in text mode.
		 */
		pio->osfile = (char)(FOPEN | FTEXT);

		if ( ((stdfh = (long)GetStdHandle( stdhndl(fh) ))
		     != (long)INVALID_HANDLE_VALUE) && ((htype =
		     GetFileType( (HANDLE)stdfh )) != FILE_TYPE_UNKNOWN) )
		{
		    /*
		     * obtained a valid HANDLE from GetStdHandle
		     */
		    pio->osfhnd = stdfh;

                    /*
		     * finish setting osfile: determine if it is a character
		     * device or pipe.
                     */
		    if ( (htype & 0xFF) == FILE_TYPE_CHAR )
			pio->osfile |= FDEV;
                    else if ( (htype & 0xFF) == FILE_TYPE_PIPE )
			pio->osfile |= FPIPE;
		}
		else {
		    /*
		     * if there is no valid HANDLE, treat the CRT handle as
		     * being open in text mode on a device (with
		     * INVALID_HANDLE_VALUE underlying it).
		     */
		    pio->osfile |= FDEV;
		}
            }
	    else  {
                /*
                 * handle was passed to us by parent process. make
                 * sure it is text mode.
                 */
		pio->osfile |= FTEXT;
	    }
	}

	/*
	 * Set the number of supported HANDLE-s to _nhandle
	 */
	(void)SetHandleCount( (unsigned)_nhandle );
}