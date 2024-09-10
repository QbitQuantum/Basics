static int
ShowFlavor(WINDOW *strwin, WINDOW *txtwin, int flavor, int limit)
{
    const char *name = "?";
    bool limited = FALSE;
    bool wins = (txtwin != stdscr);
    int result;

    switch (flavor) {
    case eGetStr:
	name = wins ? "wget_wstr" : "get_wstr";
	break;
    case eGetNStr:
	limited = TRUE;
	name = wins ? "wgetn_wstr" : "getn_wstr";
	break;
    case eMvGetStr:
	name = wins ? "mvwget_wstr" : "mvget_wstr";
	break;
    case eMvGetNStr:
	limited = TRUE;
	name = wins ? "mvwgetn_wstr" : "mvgetn_wstr";
	break;
    case eMaxFlavor:
	break;
    }

    wmove(strwin, 0, 0);
    werase(strwin);

    if (limited) {
	wprintw(strwin, "%s(%d):", name, limit);
    } else {
	wprintw(strwin, "%s:", name);
    }
    result = limited ? limit : Remainder(txtwin);
    ShowPrompt(txtwin, result);

    wnoutrefresh(strwin);
    return result;
}