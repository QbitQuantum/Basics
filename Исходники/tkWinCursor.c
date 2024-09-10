TkCursor *
TkGetCursorByName(
    Tcl_Interp *interp,		/* Interpreter to use for error reporting. */
    Tk_Window tkwin,		/* Window in which cursor will be used. */
    Tk_Uid string)		/* Description of cursor. See manual entry for
				 * details on legal syntax. */
{
    struct CursorName *namePtr;
    TkWinCursor *cursorPtr;
    int argc;
    const char **argv = NULL;

    /*
     * All cursor names are valid lists of one element (for
     * Unix-compatability), even unadorned system cursor names.
     */

    if (Tcl_SplitList(interp, string, &argc, &argv) != TCL_OK) {
	return NULL;
    }
    if (argc == 0) {
	goto badCursorSpec;
    }

    cursorPtr = (TkWinCursor *) ckalloc(sizeof(TkWinCursor));
    cursorPtr->info.cursor = (Tk_Cursor) cursorPtr;
    cursorPtr->winCursor = NULL;
    cursorPtr->system = 0;

    if (argv[0][0] == '@') {
	/*
	 * Check for system cursor of type @<filename>, where only the name is
	 * allowed. This accepts any of:
	 *	-cursor @/winnt/cursors/globe.ani
	 *	-cursor @C:/Winnt/cursors/E_arrow.cur
	 *	-cursor {@C:/Program\ Files/Cursors/bart.ani}
	 *      -cursor {{@C:/Program Files/Cursors/bart.ani}}
	 *	-cursor [list @[file join "C:/Program Files" Cursors bart.ani]]
	 */

	if (Tcl_IsSafe(interp)) {
	    Tcl_AppendResult(interp, "can't get cursor from a file in",
		    " a safe interpreter", NULL);
	    ckfree((char *) argv);
	    ckfree((char *) cursorPtr);
	    return NULL;
	}
	cursorPtr->winCursor = LoadCursorFromFileA(&(argv[0][1]));
    } else {
	/*
	 * Check for the cursor in the system cursor set.
	 */

	for (namePtr = cursorNames; namePtr->name != NULL; namePtr++) {
	    if (strcmp(namePtr->name, argv[0]) == 0) {
		cursorPtr->winCursor = LoadCursor(NULL, namePtr->id);
		break;
	    }
	}

	if (cursorPtr->winCursor == NULL) {
	    /*
	     * Hmm, it is not in the system cursor set. Check to see if it is
	     * one of our application resources.
	     */

	    cursorPtr->winCursor = LoadCursorA(Tk_GetHINSTANCE(), argv[0]);
	} else {
	    cursorPtr->system = 1;
	}
    }

    if (cursorPtr->winCursor == NULL) {
	ckfree((char *) cursorPtr);
    badCursorSpec:
	ckfree((char *) argv);
	Tcl_AppendResult(interp, "bad cursor spec \"", string, "\"", NULL);
	return NULL;
    } else {
	ckfree((char *) argv);
	return (TkCursor *) cursorPtr;
    }
}