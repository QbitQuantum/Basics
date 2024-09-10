/* CCRETVAL */
int
Inputl(void)
{
    CCRETVAL retval;
    KEYCMD  cmdnum = 0;
    unsigned char tch;		/* the place where read() goes */
    Char    ch;
    int     num;		/* how many chars we have read at NL */
    int	    expnum;
    struct varent *crct = inheredoc ? NULL : adrof(STRcorrect);
    struct varent *autol = adrof(STRautolist);
    struct varent *matchbeep = adrof(STRmatchbeep);
    struct varent *imode = adrof(STRinputmode);
    Char   *SaveChar, *CorrChar;
    int     matchval;		/* from tenematch() */
    int     nr_history_exp;     /* number of (attempted) history expansions */
    COMMAND fn;
    int curlen = 0;
    int newlen;
    int idx;
    Char *autoexpand;

    if (!MapsAreInited)		/* double extra just in case */
	ed_InitMaps();

    ClearDisp();		/* reset the display stuff */
    ResetInLine(0);		/* reset the input pointers */
    if (GettingInput)
	MacroLvl = -1;		/* editor was interrupted during input */

    if (imode && imode->vec != NULL) {
	if (!Strcmp(*(imode->vec), STRinsert))
	    inputmode = MODE_INSERT;
	else if (!Strcmp(*(imode->vec), STRoverwrite))
	    inputmode = MODE_REPLACE;
    }

#if defined(FIONREAD) && !defined(OREO)
    if (!Tty_raw_mode && MacroLvl < 0) {
# ifdef SUNOS4
	long chrs = 0;
# else /* !SUNOS4 */
	/* 
	 * *Everyone* else has an int, but SunOS wants long!
	 * This breaks where int != long (alpha)
	 */
	int chrs = 0;
# endif /* SUNOS4 */

	(void) ioctl(SHIN, FIONREAD, (ioctl_t) & chrs);
	if (chrs == 0) {
	    if (Rawmode() < 0)
		return 0;
	}
    }
#endif /* FIONREAD && !OREO */

    GettingInput = 1;
    NeedsRedraw = 0;
    tellwhat = 0;

    if (RestoreSaved) {
	copyn(InputBuf, SavedBuf.s, INBUFSIZE);/*FIXBUF*/
	LastChar = InputBuf + LastSaved;
	Cursor = InputBuf + CursSaved;
	Hist_num = HistSaved;
	HistSaved = 0;
	RestoreSaved = 0;
    }
    if (HistSaved) {
	Hist_num = HistSaved;
	GetHistLine();
	HistSaved = 0;
    }
    if (Expand) {
	(void) e_up_hist(0);
	Expand = 0;
    }
    Refresh();			/* print the prompt */

    for (num = OKCMD; num == OKCMD;) {	/* while still editing this line */
#ifdef DEBUG_EDIT
	if (Cursor > LastChar)
	    xprintf("Cursor > LastChar\r\n");
	if (Cursor < InputBuf)
	    xprintf("Cursor < InputBuf\r\n");
	if (Cursor > InputLim)
	    xprintf("Cursor > InputLim\r\n");
	if (LastChar > InputLim)
	    xprintf("LastChar > InputLim\r\n");
	if (InputLim != &InputBuf[INBUFSIZE - 2])/*FIXBUF*/
	    xprintf("InputLim != &InputBuf[INBUFSIZE-2]\r\n");
	if ((!DoingArg) && (Argument != 1))
	    xprintf("(!DoingArg) && (Argument != 1)\r\n");
	if (CcKeyMap[0] == 0)
	    xprintf("CcKeyMap[0] == 0 (maybe not inited)\r\n");
#endif

	/* if EOF or error */
	if ((num = GetNextCommand(&cmdnum, &ch)) != OKCMD) {
	    break;
	}

	if (cmdnum >= NumFuns) {/* BUG CHECK command */
#ifdef DEBUG_EDIT
	    xprintf(CGETS(6, 1, "ERROR: illegal command from key 0%o\r\n"), ch);
#endif
	    continue;		/* try again */
	}

	/* now do the real command */
	retval = (*CcFuncTbl[cmdnum]) (ch);

	/* save the last command here */
	LastCmd = cmdnum;

	/* make sure fn is initialized */
	fn = (retval == CC_COMPLETE_ALL) ? LIST_ALL : LIST;

	/* use any return value */
	switch (retval) {

	case CC_REFRESH:
	    Refresh();
	    /*FALLTHROUGH*/
	case CC_NORM:		/* normal char */
	    Argument = 1;
	    DoingArg = 0;
	    /*FALLTHROUGH*/
	case CC_ARGHACK:	/* Suggested by Rich Salz */
	    /* <*****@*****.**> */
	    curchoice = -1;
	    curlen = (int) (LastChar - InputBuf);
	    break;		/* keep going... */

	case CC_EOF:		/* end of file typed */
	    curchoice = -1;
	    curlen = (int) (LastChar - InputBuf);
	    num = 0;
	    break;

	case CC_WHICH:		/* tell what this command does */
	    tellwhat = 1;
	    *LastChar++ = '\n';	/* for the benifit of CSH */
	    num = (int) (LastChar - InputBuf);	/* number characters read */
	    break;

	case CC_NEWLINE:	/* normal end of line */
	    curlen = 0;
	    curchoice = -1;
	    matchval = 1;
	    if (crct && crct->vec != NULL && (!Strcmp(*(crct->vec), STRcmd) ||
			 !Strcmp(*(crct->vec), STRall))) {
		Char *Origin;

                PastBottom();
		Origin = Strsave(InputBuf);
		cleanup_push(Origin, xfree);
		SaveChar = LastChar;
		if (SpellLine(!Strcmp(*(crct->vec), STRcmd)) == 1) {
		    Char *Change;

                    PastBottom();
		    Change = Strsave(InputBuf);
		    cleanup_push(Change, xfree);
		    *Strchr(Change, '\n') = '\0';
		    CorrChar = LastChar;	/* Save the corrected end */
		    LastChar = InputBuf;	/* Null the current line */
		    SoundBeep();
		    printprompt(2, short2str(Change));
		    cleanup_until(Change);
		    Refresh();
		    if (xread(SHIN, &tch, 1) < 0) {
#ifdef convex
		        /*
			 * need to print error message in case file
			 * is migrated
			 */
                        if (errno)
                            stderror(ERR_SYSTEM, progname, strerror(errno));
#else
			cleanup_until(Origin);
			break;
#endif
		    }
		    ch = tch;
		    if (ch == 'y' || ch == ' ') {
			LastChar = CorrChar;	/* Restore the corrected end */
			xprintf("%s", CGETS(6, 2, "yes\n"));
		    }
		    else {
			Strcpy(InputBuf, Origin);
			LastChar = SaveChar;
			if (ch == 'e') {
			    xprintf("%s", CGETS(6, 3, "edit\n"));
			    *LastChar-- = '\0';
			    Cursor = LastChar;
			    printprompt(3, NULL);
			    ClearLines();
			    ClearDisp();
			    Refresh();
			    cleanup_until(Origin);
			    break;
			}
			else if (ch == 'a') {
			    xprintf("%s", CGETS(6, 4, "abort\n"));
		            LastChar = InputBuf;   /* Null the current line */
			    Cursor = LastChar;
			    printprompt(0, NULL);
			    Refresh();
			    cleanup_until(Origin);
			    break;
			}
			xprintf("%s", CGETS(6, 5, "no\n"));
		    }
		    flush();
		}
		cleanup_until(Origin);
	    } else if (crct && crct->vec != NULL &&
		!Strcmp(*(crct->vec), STRcomplete)) {
                if (LastChar > InputBuf && LastChar[-1] == '\n') {
                    LastChar[-1] = '\0';
                    LastChar--;
                    Cursor = LastChar;
                }
                match_unique_match = 1;  /* match unique matches */
		matchval = CompleteLine();
                match_unique_match = 0;
        	curlen = (int) (LastChar - InputBuf);
		if (matchval != 1) {
                    PastBottom();
		}
		if (matchval == 0) {
		    xprintf("%s", CGETS(6, 6, "No matching command\n"));
		} else if (matchval == 2) {
		    xprintf("%s", CGETS(6, 7, "Ambiguous command\n"));
		}
	        if (NeedsRedraw) {
		    ClearLines();
		    ClearDisp();
		    NeedsRedraw = 0;
	        }
	        Refresh();
	        Argument = 1;
	        DoingArg = 0;
		if (matchval == 1) {
                    PastBottom();
                    *LastChar++ = '\n';
                    *LastChar = '\0';
		}
        	curlen = (int) (LastChar - InputBuf);
            }
	    else
		PastBottom();

	    if (matchval == 1) {
	        tellwhat = 0;	/* just in case */
	        Hist_num = 0;	/* for the history commands */
		/* return the number of chars read */
	        num = (int) (LastChar - InputBuf);
	        /*
	         * For continuation lines, we set the prompt to prompt 2
	         */
	        printprompt(1, NULL);
	    }
	    break;

	case CC_CORRECT:
	    if (tenematch(InputBuf, Cursor - InputBuf, SPELL) < 0)
		SoundBeep();		/* Beep = No match/ambiguous */
	    curlen = Repair();
	    break;

	case CC_CORRECT_L:
	    if (SpellLine(FALSE) < 0)
		SoundBeep();		/* Beep = No match/ambiguous */
	    curlen = Repair();
	    break;


	case CC_COMPLETE:
	case CC_COMPLETE_ALL:
	case CC_COMPLETE_FWD:
	case CC_COMPLETE_BACK:
	    switch (retval) {
	    case CC_COMPLETE:
		fn = RECOGNIZE;
		curlen = (int) (LastChar - InputBuf);
		curchoice = -1;
		rotate = 0;
		break;
	    case CC_COMPLETE_ALL:
		fn = RECOGNIZE_ALL;
		curlen = (int) (LastChar - InputBuf);
		curchoice = -1;
		rotate = 0;
		break;
	    case CC_COMPLETE_FWD:
		fn = RECOGNIZE_SCROLL;
		curchoice++;
		rotate = 1;
		break;
	    case CC_COMPLETE_BACK:
		fn = RECOGNIZE_SCROLL;
		curchoice--;
		rotate = 1;
		break;
	    default:
		abort();
	    }
	    if (InputBuf[curlen] && rotate) {
		newlen = (int) (LastChar - InputBuf);
		for (idx = (int) (Cursor - InputBuf); 
		     idx <= newlen; idx++)
			InputBuf[idx - newlen + curlen] =
			InputBuf[idx];
		LastChar = InputBuf + curlen;
		Cursor = Cursor - newlen + curlen;
	    }
	    curlen = (int) (LastChar - InputBuf);


	    nr_history_exp = 0;
	    autoexpand = varval(STRautoexpand);
	    if (autoexpand != STRNULL)
		nr_history_exp += ExpandHistory();

	    /* try normal expansion only if no history references were found */
	    if (nr_history_exp == 0 ||
		Strcmp(autoexpand, STRonlyhistory) != 0) {
		/*
		 * Modified by Martin Boyer ([email protected]):
		 * A separate variable now controls beeping after
		 * completion, independently of autolisting.
		 */
		expnum = (int) (Cursor - InputBuf);
		switch (matchval = tenematch(InputBuf, Cursor-InputBuf, fn)){
		case 1:
		    if (non_unique_match && matchbeep &&
			matchbeep->vec != NULL &&
			(Strcmp(*(matchbeep->vec), STRnotunique) == 0))
			SoundBeep();
		    break;
		case 0:
		    if (matchbeep && matchbeep->vec != NULL) {
			if (Strcmp(*(matchbeep->vec), STRnomatch) == 0 ||
			    Strcmp(*(matchbeep->vec), STRambiguous) == 0 ||
			    Strcmp(*(matchbeep->vec), STRnotunique) == 0)
			    SoundBeep();
		    }
		    else
			SoundBeep();
		    break;
		default:
		    if (matchval < 0) {	/* Error from tenematch */
			curchoice = -1;
			SoundBeep();
			break;
		    }
		    if (matchbeep && matchbeep->vec != NULL) {
			if ((Strcmp(*(matchbeep->vec), STRambiguous) == 0 ||
			     Strcmp(*(matchbeep->vec), STRnotunique) == 0))
			    SoundBeep();
		    }
		    else
			SoundBeep();
		    /*
		     * Addition by David C Lawrence <*****@*****.**>: If an 
		     * attempted completion is ambiguous, list the choices.  
		     * (PWP: this is the best feature addition to tcsh I have 
		     * seen in many months.)
		     */
		    if (autol && autol->vec != NULL && 
			(Strcmp(*(autol->vec), STRambiguous) != 0 || 
					 expnum == Cursor - InputBuf)) {
			if (adrof(STRhighlight) && MarkIsSet) {
			    /* clear highlighting before showing completions */
			    MarkIsSet = 0;
			    ClearLines();
			    ClearDisp();
			    Refresh();
			    MarkIsSet = 1;
			}
			PastBottom();
			fn = (retval == CC_COMPLETE_ALL) ? LIST_ALL : LIST;
			(void) tenematch(InputBuf, Cursor-InputBuf, fn);
		    }
		    break;
		}
	    }
	    if (NeedsRedraw) {
		PastBottom();
		ClearLines();
		ClearDisp();
		NeedsRedraw = 0;
	    }
	    Refresh();
	    Argument = 1;
	    DoingArg = 0;
	    break;

	case CC_LIST_CHOICES:
	case CC_LIST_ALL:
	    if (InputBuf[curlen] && rotate) {
		newlen = (int) (LastChar - InputBuf);
		for (idx = (int) (Cursor - InputBuf); 
		     idx <= newlen; idx++)
			InputBuf[idx - newlen + curlen] =
			InputBuf[idx];
		LastChar = InputBuf + curlen;
		Cursor = Cursor - newlen + curlen;
	    }
	    curlen = (int) (LastChar - InputBuf);
	    if (curchoice >= 0)
		curchoice--;

	    fn = (retval == CC_LIST_ALL) ? LIST_ALL : LIST;
	    /* should catch ^C here... */
	    if (tenematch(InputBuf, Cursor - InputBuf, fn) < 0)
		SoundBeep();
	    Refresh();
	    Argument = 1;
	    DoingArg = 0;
	    break;


	case CC_LIST_GLOB:
	    if (tenematch(InputBuf, Cursor - InputBuf, GLOB) < 0)
		SoundBeep();
	    curlen = Repair();
	    break;

	case CC_EXPAND_GLOB:
	    if (tenematch(InputBuf, Cursor - InputBuf, GLOB_EXPAND) <= 0)
		SoundBeep();		/* Beep = No match */
	    curlen = Repair();
	    break;

	case CC_NORMALIZE_PATH:
	    if (tenematch(InputBuf, Cursor - InputBuf, PATH_NORMALIZE) <= 0)
		SoundBeep();		/* Beep = No match */
	    curlen = Repair();
	    break;

	case CC_EXPAND_VARS:
	    if (tenematch(InputBuf, Cursor - InputBuf, VARS_EXPAND) <= 0)
		SoundBeep();		/* Beep = No match */
	    curlen = Repair();
	    break;

	case CC_NORMALIZE_COMMAND:
	    if (tenematch(InputBuf, Cursor - InputBuf, COMMAND_NORMALIZE) <= 0)
		SoundBeep();		/* Beep = No match */
	    curlen = Repair();
	    break;

	case CC_HELPME:
	    xputchar('\n');
	    /* should catch ^C here... */
	    (void) tenematch(InputBuf, LastChar - InputBuf, PRINT_HELP);
	    Refresh();
	    Argument = 1;
	    DoingArg = 0;
	    curchoice = -1;
	    curlen = (int) (LastChar - InputBuf);
	    break;

	case CC_FATAL:		/* fatal error, reset to known state */
#ifdef DEBUG_EDIT
	    xprintf(CGETS(7, 8, "*** editor fatal ERROR ***\r\n\n"));
#endif				/* DEBUG_EDIT */
	    /* put (real) cursor in a known place */
	    ClearDisp();	/* reset the display stuff */
	    ResetInLine(1);	/* reset the input pointers */
	    Refresh();		/* print the prompt again */
	    Argument = 1;
	    DoingArg = 0;
	    curchoice = -1;
	    curlen = (int) (LastChar - InputBuf);
	    break;

	case CC_ERROR:
	default:		/* functions we don't know about */
	    if (adrof(STRhighlight)) {
		ClearLines();
		ClearDisp();
		Refresh();
	    }
	    DoingArg = 0;
	    Argument = 1;
	    SoundBeep();
	    flush();
	    curchoice = -1;
	    curlen = (int) (LastChar - InputBuf);
	    break;
	}
    }
    (void) Cookedmode();	/* make sure the tty is set up correctly */
    GettingInput = 0;
    flush();			/* flush any buffered output */
    return num;
}