/* this is called from main() in s_entry.c */
int sys_main(int argc, char **argv)
{
    int i, noprefs;
    char *prefsfile = "";
    sys_externalschedlib = 0;
    sys_extraflags = 0;
#ifdef PD_DEBUG
    fprintf(stderr, "Pd: COMPILED FOR DEBUGGING\n");
#endif
    /* use Win32 "binary" mode by default since we don't want the
     * translation that Win32 does by default */
#ifdef _WIN32
# ifdef _MSC_VER /* MS Visual Studio */
    _set_fmode( _O_BINARY );
# else  /* MinGW */
    {
        extern int _fmode;
        _fmode = _O_BINARY;
    }
# endif /* _MSC_VER */
#endif  /* _WIN32 */
#ifndef _WIN32
    /* long ago Pd used setuid to promote itself to real-time priority.
    Just in case anyone's installation script still makes it setuid, we
    complain to stderr and lose setuid here. */
    if (getuid() != geteuid())
    {
        fprintf(stderr, "warning: canceling setuid privilege\n");
        setuid(getuid());
    }
#endif  /* _WIN32 */
    pd_init();                                  /* start the message system */
    sys_findprogdir(argv[0]);                   /* set sys_progname, guipath */
    for (i = noprefs = 0; i < argc; i++)    /* prescan for prefs override */
    {
        if (!strcmp(argv[i], "-noprefs"))
            noprefs = 1;
        else if (!strcmp(argv[i], "-prefsfile") && i < argc-1)
            prefsfile = argv[i+1];
    }
    if (!noprefs)       /* load preferences before parsing args to allow ... */
        sys_loadpreferences(prefsfile, 1);  /* args to override prefs */
    if (sys_argparse(argc-1, argv+1))           /* parse cmd line args */
        return (1);
    sys_afterargparse();                    /* post-argparse settings */
    if (sys_verbose || sys_version) fprintf(stderr, "%s compiled %s %s\n",
        pd_version, pd_compiletime, pd_compiledate);
    if (sys_version)    /* if we were just asked our version, exit here. */
        return (0);
    sys_setsignalhandlers();
    if (sys_dontstartgui)
        clock_set((sys_fakefromguiclk =
            clock_new(0, (t_method)sys_fakefromgui)), 0);
    else if (sys_startgui(sys_libdir->s_name)) /* start the gui */
        return (1);
    if (sys_hipriority)
        sys_setrealtime(sys_libdir->s_name); /* set desired process priority */
    if (sys_externalschedlib)
        return (sys_run_scheduler(sys_externalschedlibname,
            sys_extraflagsstring));
    else if (sys_batch)
        return (m_batchmain());
    else
    {
            /* open audio and MIDI */
        sys_reopen_midi();
        if (audio_shouldkeepopen())
            sys_reopen_audio();
            /* run scheduler until it quits */
        return (m_mainloop());
    }
}