XrmDatabase XtScreenDatabase(
    Screen *screen)
{
    int scrno;
    Bool doing_def;
    XrmDatabase db, olddb;
    XtPerDisplay pd;
    Status do_fallback;
    char *scr_resources;
    Display *dpy = DisplayOfScreen(screen);
    DPY_TO_APPCON(dpy);

    LOCK_APP(app);
    LOCK_PROCESS;
    if (screen == DefaultScreenOfDisplay(dpy)) {
	scrno = DefaultScreen(dpy);
	doing_def = True;
    } else {
	scrno = XScreenNumberOfScreen(screen);
	doing_def = False;
    }
    pd = _XtGetPerDisplay(dpy);
    if ((db = pd->per_screen_db[scrno])) {
	UNLOCK_PROCESS;
	UNLOCK_APP(app);
	return (doing_def ? XrmGetDatabase(dpy) : db);
    }
    scr_resources = XScreenResourceString(screen);

    if (ScreenCount(dpy) == 1) {
	db = pd->cmd_db;
	pd->cmd_db = NULL;
    } else {
	db = CopyDB(pd->cmd_db);
    }
    {   /* Environment defaults */
	char	filenamebuf[PATH_MAX];
	char	*filename;

	if (!(filename = getenv("XENVIRONMENT"))) {
	    int len;
#ifdef __MINGW32__
	    const char *slashDotXdefaultsDash = "/Xdefaults-";
#else
	    const char *slashDotXdefaultsDash = "/.Xdefaults-";
#endif

	    (void) GetRootDirName(filename = filenamebuf,
			PATH_MAX - strlen (slashDotXdefaultsDash) - 1);
	    (void) strcat(filename, slashDotXdefaultsDash);
	    len = strlen(filename);
	    GetHostname (filename+len, PATH_MAX-len);
	}
	(void)XrmCombineFileDatabase(filename, &db, False);
    }
    if (scr_resources)
    {   /* Screen defaults */
	XrmCombineDatabase(XrmGetStringDatabase(scr_resources), &db, False);
	XFree(scr_resources);
    }
    /* Server or host defaults */
    if (!pd->server_db)
	CombineUserDefaults(dpy, &db);
    else {
	(void) XrmCombineDatabase(pd->server_db, &db, False);
	pd->server_db = NULL;
    }

    if (!db)
	db = XrmGetStringDatabase("");
    pd->per_screen_db[scrno] = db;
    olddb = XrmGetDatabase(dpy);
    /* set database now, for XtResolvePathname to use */
    XrmSetDatabase(dpy, db);
    CombineAppUserDefaults(dpy, &db);
    do_fallback = 1;
    {   /* System app-defaults */
	char	*filename;

	if ((filename = XtResolvePathname(dpy, "app-defaults",
					 NULL, NULL, NULL, NULL, 0, NULL))) {
	    do_fallback = !XrmCombineFileDatabase(filename, &db, False);
	    XtFree(filename);
	}
    }
    /* now restore old database, if need be */
    if (!doing_def)
	XrmSetDatabase(dpy, olddb);
    if (do_fallback && pd->appContext->fallback_resources)
    {   /* Fallback defaults */
        XrmDatabase fdb = NULL;
	String *res;

	for (res = pd->appContext->fallback_resources; *res; res++)
	    XrmPutLineResource(&fdb, *res);
	(void)XrmCombineDatabase(fdb, &db, False);
    }
    UNLOCK_PROCESS;
    UNLOCK_APP(app);
    return db;
}