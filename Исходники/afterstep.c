/***********************************************************************
 *  Procedure:
 *	main - start of afterstep
 ************************************************************************/
int
main (int argc, char **argv, char **envp)
{
    register int i ;
	
	int start_viewport_x = 0 ;
	int start_viewport_y = 0 ;
	int start_desk = 0 ;

#ifdef LOCAL_DEBUG
#if 0
	LOCAL_DEBUG_OUT( "calibrating sleep_a_millisec : %s","" );
	for( i = 0 ; i < 500 ; ++i )
		sleep_a_millisec( 10 );
	LOCAL_DEBUG_OUT( "500 sliip_a_millisec(10) completed%s","" );
	for( i = 0 ; i < 50 ; ++i )
		sleep_a_millisec( 100 );
	LOCAL_DEBUG_OUT( "50 sliip_a_millisec(100) completed%s","" );
	for( i = 0 ; i < 10 ; ++i )
		sleep_a_millisec( 300 );
	LOCAL_DEBUG_OUT( "10 sliip_a_millisec(300) completed%s","" );
#endif
#endif

	_as_grab_screen_func = GrabEm;
	_as_ungrab_screen_func = UngrabEm;

	original_DISPLAY_string = getenv("DISPLAY");
	if (original_DISPLAY_string)
		original_DISPLAY_string = mystrdup(original_DISPLAY_string);

#ifdef DEBUG_TRACE_X
	trace_window_id2name_hook = &window_id2name;
#endif
	set_DeadPipe_handler(DeadPipe);

#if !HAVE_DECL_ENVIRON
	override_environ( envp );
#endif
    InitMyApp( CLASS_AFTERSTEP, argc, argv, NULL, AfterStep_usage, 0);

	LinkAfterStepConfig();

    AfterStepState = MyArgs.flags ;
    clear_flags( AfterStepState, ASS_NormalOperation );
	set_flags( AfterStepState, ASS_SuppressDeskBack );

#ifdef __CYGWIN__
    CloseOnExec = ASCloseOnExec ;
#endif

#if defined(LOG_FONT_CALLS)
	fprintf (stderr, "logging font calls now\n");
#endif

    /* These signals are mandatory : */
    signal (SIGUSR1, Restart);
    /* These signals we would like to handle only if those are not handled already (by debugger): */
    IgnoreSignal(SIGINT);
    IgnoreSignal(SIGHUP);
    IgnoreSignal(SIGQUIT);
    IgnoreSignal(SIGTERM);

    if( ConnectX( ASDefaultScr, AS_ROOT_EVENT_MASK ) < 0  )
	{
		show_error( "Hostile X server encountered - unable to proceed :-(");
		return 1;/* failed to accure window management selection - other wm is running */
	}


	ASDBus_fd = asdbus_init();

	XSetWindowBackground( dpy, Scr.Root, Scr.asv->black_pixel );
	Scr.Look.desktop_animation_tint = get_random_tint_color();

    cover_desktop();
	if( get_flags( AfterStepState, ASS_Restarting ))
	{	
		show_progress( "AfterStep v.%s is restarting ...", VERSION );
		display_progress( True, "AfterStep v.%s is restarting ...", VERSION );
	}else
	{	
    	show_progress( "AfterStep v.%s is starting up ...", VERSION );
		display_progress( True, "AfterStep v.%s is starting up ...", VERSION );
	}

	if (ASDBus_fd>=0)
	{
    	show_progress ("Successfuly accured System DBus connection.");	
		asdbus_RegisterSMClient(SMClientID_string);
	}
	
SHOW_CHECKPOINT;
	InitSession();
SHOW_CHECKPOINT;
	XSync (dpy, 0);
SHOW_CHECKPOINT;
    set_parent_hints_func( afterstep_parent_hints_func ); /* callback for collect_hints() */
SHOW_CHECKPOINT;
    SetupModules();
SHOW_CHECKPOINT;
	SetupScreen();
SHOW_CHECKPOINT;
	event_setup( True /*Bool local*/ );
SHOW_CHECKPOINT;
	/*
     *  Lets init each and every screen separately :
     */
	
    for (i = 0; i < Scr.NumberOfScreens; i++)
	{
        show_progress( "Initializing screen %d ...", i );
        display_progress( True, "Initializing screen %d ...", i );

        if (i != Scr.screen)
        {
            if( !get_flags(MyArgs.flags, ASS_SingleScreen) )
            {
                int pid = spawn_child( MyName, (i<MAX_USER_SINGLETONS_NUM)?i:-1, i, NULL, None, C_NO_CONTEXT, True, True, NULL );
                if( pid >= 0 )
                    show_progress( "\t instance of afterstep spawned with pid %d.", pid );
                else
                    show_error( "failed to launch instance of afterstep to handle screen #%d", i );
            }
        }else
        {
            make_screen_envvars(ASDefaultScr);
            putenv (Scr.rdisplay_string);
            putenv (Scr.display_string);
            if( is_output_level_under_threshold( OUTPUT_LEVEL_PROGRESS ) )
            {
                show_progress( "\t screen[%d].size = %ux%u", Scr.screen, Scr.MyDisplayWidth, Scr.MyDisplayHeight );
                display_progress( True, "    screen[%d].size = %ux%u", Scr.screen, Scr.MyDisplayWidth, Scr.MyDisplayHeight );
                show_progress( "\t screen[%d].root = %lX", Scr.screen, Scr.Root );
                show_progress( "\t screen[%d].color_depth = %d", Scr.screen, Scr.asv->true_depth );
                display_progress( True, "    screen[%d].color_depth = %d", Scr.screen, Scr.asv->true_depth );
                show_progress( "\t screen[%d].colormap    = 0x%lX", Scr.screen, Scr.asv->colormap );
                show_progress( "\t screen[%d].visual.id         = %X",  Scr.screen, Scr.asv->visual_info.visualid );
                display_progress( True, "    screen[%d].visual.id         = %X",  Scr.screen, Scr.asv->visual_info.visualid );
                show_progress( "\t screen[%d].visual.class      = %d",  Scr.screen, Scr.asv->visual_info.class );
                display_progress( True, "    screen[%d].visual.class      = %d",  Scr.screen, Scr.asv->visual_info.class );
                show_progress( "\t screen[%d].visual.red_mask   = 0x%8.8lX", Scr.screen, Scr.asv->visual_info.red_mask   );
                show_progress( "\t screen[%d].visual.green_mask = 0x%8.8lX", Scr.screen, Scr.asv->visual_info.green_mask );
                show_progress( "\t screen[%d].visual.blue_mask  = 0x%8.8lX", Scr.screen, Scr.asv->visual_info.blue_mask  );
                show_progress( "\t screen[%d].rdisplay_string = \"%s\"", Scr.screen, Scr.rdisplay_string );
                show_progress( "\t screen[%d].display_string = \"%s\"", Scr.screen, Scr.display_string );
                display_progress( True, "    screen[%d].display_string = \"%s\"", Scr.screen, Scr.display_string );
            }
        }
    }

   /* make sure we're on the right desk, and the _WIN_DESK property is set */
    Scr.CurrentDesk = INVALID_DESK ;
    if( get_flags( Scr.wmprops->set_props, WMC_ASDesks )  )
	{
		start_desk = Scr.wmprops->as_current_desk ;
    }else if( get_flags( Scr.wmprops->set_props, WMC_DesktopCurrent )  )
    {
        int curr = Scr.wmprops->desktop_current ;
        start_desk = curr;
        if( get_flags( Scr.wmprops->set_props, WMC_DesktopViewport ) &&
            curr < Scr.wmprops->desktop_viewports_num )
        {
            /* we have to do that prior to capturing any window so that they'll get in
             * correct position and will not end up outside of the screen */
            start_viewport_x = Scr.wmprops->desktop_viewport[curr<<1] ;
			start_viewport_y = Scr.wmprops->desktop_viewport[(curr<<1)+1] ;
        }
    }
    if( get_flags( Scr.wmprops->set_props, WMC_ASViewport )  )
	{
		start_viewport_x = Scr.wmprops->as_current_vx ;
		start_viewport_y = Scr.wmprops->as_current_vy ;
	}
	/* temporarily setting up desktop 0 */
	ChangeDesks(0);

    /* Load config ... */
    /* read config file, set up menus, colors, fonts */
    LoadASConfig (0, PARSE_EVERYTHING);

    /* Reparent all the windows and setup pan frames : */
    XSync (dpy, 0);
   /***********************************************************/
#ifndef DONT_GRAB_SERVER                    /* grabbed   !!!!!*/
	grab_server();                		/* grabbed   !!!!!*/
#endif										/* grabbed   !!!!!*/
    init_screen_panframes(ASDefaultScr);            /* grabbed   !!!!!*/
    display_progress( True, "Capturing all windows ..." );
    CaptureAllWindows (ASDefaultScr);               /* grabbed   !!!!!*/
    display_progress( False, "Done." );
    check_screen_panframes(ASDefaultScr);           /* grabbed   !!!!!*/
    ASSync( False );
#ifndef DONT_GRAB_SERVER                    /* grabbed   !!!!!*/
	ungrab_server();					/* UnGrabbed !!!!!*/
#endif										/* UnGrabbed !!!!!*/
	/**********************************************************/
    XDefineCursor (dpy, Scr.Root, Scr.Feel.cursors[ASCUR_Default]);

    display_progress( True, "Seting initial viewport to %+d%+d ...", Scr.wmprops->as_current_vx, Scr.wmprops->as_current_vy );

    SetupFunctionHandlers();
    display_progress( True, "Processing all pending events ..." );
    ConfigureNotifyLoop();
    display_progress( True, "All done." );
    remove_desktop_cover();

	if( !get_flags(AfterStepStartupFlags, ASSF_BypassAutoexec))
    	DoAutoexec(get_flags( AfterStepState, ASS_Restarting));
	
	/* once all the windows are swallowed and placed in its proper desks - we cas restore proper
	   desktop/viewport : */
	clear_flags( AfterStepState, ASS_SuppressDeskBack );
	ChangeDeskAndViewport ( start_desk, start_viewport_x, start_viewport_y, False);

    /* all system Go! we are completely Operational! */
    set_flags( AfterStepState, ASS_NormalOperation);

#if (defined(LOCAL_DEBUG)||defined(DEBUG)) && defined(DEBUG_ALLOCS)
    LOCAL_DEBUG_OUT( "printing memory%s","");
    spool_unfreed_mem( "afterstep.allocs.startup", NULL );
#endif
    LOCAL_DEBUG_OUT( "entering main loop%s","");

    HandleEvents ();
	return (0);
}