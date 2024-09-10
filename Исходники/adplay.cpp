int main(int argc, char *argv[])
{
  char          inkey=0, *prgdir, *curdir, *program_name;
  bool          ext, validcfg, quit = false, bkgply = false, batchply = false;
  unsigned int	opt, prgdrive, i;
  CWindow       *focus;

#ifdef DEBUG
  f_log = fopen(DEBUG_FILE,"wt");
#endif

  std::cout << ADPLAYVERS << ", Copyright (c) 2000 - 2006 Simon Peter <*****@*****.**>" << std::endl << std::endl;

  // check that no other instance is running
  {
    char *adplayenv = getenv("ADPLAY");

    if(adplayenv && !strcmp(adplayenv,"S")) {
      std::cout << "AdPlay already running!" << std::endl;
      exit(EXIT_FAILURE);
    } else
      setenv("ADPLAY","S",1); // flag our instance
  }

  // Build program executable name
  program_name = strrchr(argv[0], '\\') ? strrchr(argv[0], '\\') + 1 : argv[0];

  CAdPlug::debug_output("debug.log"); // Redirect AdPlug's debug to file
  // Build path to default configuration file (in program's directory)
  SPLITPATH(argv[0],configfile,configfile+2,NULL,NULL);
  strcat(configfile,CONFIGFILE);

  loadconfig(configfile,DEFCONFIG);       // load default configuration

  // parse commandline for general options
  while((opt = getopt(argc,argv)))
    switch(opt) {
    case 1:	// display help
    case 2:
      std::cout << "Usage: " << program_name << " [options]" << std::endl << std::endl;
      std::cout << "Options can be set with '-' or '/' respectively." << std::endl << std::endl;
      std::cout << " -?, -h      Display commandline help" << std::endl <<
	" -p port     Set OPL2 port" << std::endl <<
	" -o          Force OPL2 port" << std::endl <<
	" -f file     Use alternate configuration file" << std::endl <<
	" -c section  Load another configuration section" << std::endl <<
	" -b file     Immediate background playback using " <<
	"specified file" << std::endl <<
	" -q files    Immediate (batch mode) playback using " <<
	"specified files" << std::endl;
      showcursor();
      exit(EXIT_SUCCESS);
    case 3:	// set OPL2 port
      opl.setport(atoi(argv[myoptind++]));
      break;
    case 4: // force OPL2 port
      oplforce = true;
      break;
    case 7:	// background playback
      bkgply = true;
      break;
    case 8: // batch mode playback
      batchply = true;
      break;
    }

  // Bail out if OPL2 not detected and not force
  if(!opl.detect() && !oplforce) {
    std::cout << "No OPL2 detected!" << std::endl;
    showcursor();
    exit(EXIT_FAILURE);
  }

  // Hand our database to AdPlug
  CAdPlug::set_database(&mydb);

  /*** Background playback mode ***/
  if(bkgply)
    if(!(p = CAdPlug::factory(argv[myoptind],&opl))) {
      std::cout << "[" << argv[myoptind] << "]: unsupported file type!" << std::endl;
      exit(EXIT_FAILURE);
    } else {
      std::cout << "Background playback... (type EXIT to stop)" << std::endl;
#ifdef HAVE_WCC_TIMER_H
      tmInit(poll_player,0xffff,DEFSTACK);
#elif defined HAVE_GCC_TIMER_H
      timer_init(poll_player);
#endif
      dopoll = true;
#ifdef __WATCOMC__
      _heapshrink();
#endif
      system(getenv("COMSPEC"));
#ifdef HAVE_WCC_TIMER_H
      tmClose();
#elif defined HAVE_GCC_TIMER_H
      timer_deinit();
#endif
      stop();
      exit(EXIT_SUCCESS);
    }

  /*** Batch playback mode ***/
  if(batchply) {
#ifdef HAVE_WCC_TIMER_H
    tmInit(poll_player,0xffff,DEFSTACK);
#elif defined HAVE_GCC_TIMER_H
    timer_init(poll_player);
#endif

    for(i = myoptind; i < argc; i++)
      if(!(p = CAdPlug::factory(argv[i],&opl))) {
	std::cout << "[" << argv[i] << "]: unsupported file type!" << std::endl;
#ifdef HAVE_WCC_TIMER_H
	tmClose();
#elif defined HAVE_GCC_TIMER_H
	timer_deinit();
#endif
	exit(EXIT_FAILURE);
      } else {
	dopoll = firsttime = true;
	std::cout << "Playing [" << argv[i] << "] ..." << std::endl;
	while(firsttime) ;	// busy waiting
	stop();
	dopoll = false;
      }

#ifdef HAVE_WCC_TIMER_H
    tmClose();
#elif defined HAVE_GCC_TIMER_H
    timer_deinit();
#endif
    exit(EXIT_SUCCESS);
  }

  /*** interactive (GUI) mode ***/
  getvideoinfo(&dosvideo);        // Save previous video state

  // register our windows with the window manager
  wnds.reg(titlebar); wnds.reg(filesel); wnds.reg(songwnd);
  wnds.reg(instwnd); wnds.reg(volbars); wnds.reg(mastervol);
  wnds.reg(infownd);

  // load default GUI layout
  validcfg = loadcolors(configfile,DEFCONFIG);

  // reparse commandline for GUI options
  myoptind = 1;     // reset option parser
  while((opt = getopt(argc,argv)))
    switch(opt) {
    case 5:	// set config file
      strcpy(configfile,argv[myoptind++]);
      if(loadcolors(configfile,DEFCONFIG))
	validcfg = true;
      break;
    case 6:	// load config section
      loadcolors(configfile,argv[myoptind++]);
      break;
    }

  // bail out if no configfile could be loaded
  if(!validcfg) {
    std::cout << "No valid default GUI layout could be loaded!" << std::endl;
    exit(EXIT_FAILURE);
  }

  // init GUI
  if((tmpfn = TEMPNAM(getenv("TEMP"),"_AP")))
#ifdef __WATCOMC__
    mkdir(tmpfn);
#else
  mkdir(tmpfn, S_IWUSR);
#endif
  prgdir = getcwd(NULL, PATH_MAX); _dos_getdrive(&prgdrive);
  setadplugvideo();
#ifdef HAVE_WCC_TIMER_H
  tmInit(poll_player,0xffff,DEFSTACK);
#elif defined HAVE_GCC_TIMER_H
  timer_init(poll_player);
#endif
  songwnd.setcaption("Song Info"); volbars.setcaption("VBars");
  titlebar.setcaption(ADPLAYVERS); filesel.setcaption("Directory");
  mastervol.setcaption("Vol"); filesel.refresh(); mastervol.set(63);
  display_help(infownd); filesel.setfocus(); reset_windows();

  // main loop
  do {
    if(p) {	// auto-update windows
      //                        wait_retrace();
      idle_ms(1000/70);
      refresh_songinfo(songwnd);
      refresh_volbars(volbars,opl);

      if(onsongend && !firsttime) {	// song ended
	switch(onsongend) {
	case 1:	// auto-rewind
	  dopoll = false; while(inpoll) ;	// critical section...
	  p->rewind(subsong);
	  last_ms = time_ms = 0.0f;
	  dopoll = true;	// ...End critical section
	  break;
	case 2:	// stop playback
	  stop();
	  reset_windows();
	  break;
	}
      }
    }

    // Check for keypress and read in, if any
    if(kbhit()) {
      if(!(inkey = toupper(getch()))) {
	ext = true;
	inkey = toupper(getch());
      } else
	ext = false;

      focus = CWindow::getfocus(); // cache focused window
      dbg_printf("main(): Key pressed: %d %s\n",
		 inkey, ext ? "(Ext)" : "(Norm)");
    } else
      inkey = 0;

    if(ext)	// handle all extended keys
      switch(inkey) {
      case 15:        // [Shift]+[TAB] - Back cycle windows
	window_cycle(true);
	break;
      case 59:	// [F1] - display help
	display_help(infownd);
	infownd.setfocus();
	wnds.update();
	break;
      case 60:	// [F2] - change screen layout
	curdir = getcwd(NULL, PATH_MAX);
	chdir(prgdir);
	select_colors();
	chdir(curdir);
	free(curdir);
	clearscreen(backcol);
	filesel.refresh();
	wnds.update();
	break;
      case 72:        // [Up Arrow] - scroll up
	if(focus == &filesel) {
	  filesel.select_prev();
	  filesel.update();
	} else if(focus == &infownd) {
	  infownd.scroll_up();
	  infownd.update();
	} else if(focus == &instwnd) {
	  instwnd.scroll_up();
	  instwnd.update();
	}
	break;
      case 80:        // [Down Arrow] - scroll down
	if(focus == &filesel) {
	  filesel.select_next();
	  filesel.update();
	} else if(focus == &infownd) {
	  infownd.scroll_down();
	  infownd.update();
	} else if(focus == &instwnd) {
	  instwnd.scroll_down();
	  instwnd.update();
	}
	break;
      case 75:	// [Left Arrow] - previous subsong
	if(p && subsong) {
	  subsong--;
	  dopoll = false; while(inpoll) ;	// critical section...
	  totaltime = p->songlength(subsong);
	  p->rewind(subsong);
	  last_ms = time_ms = 0.0f;
	  dopoll = true;	// ...End critical section
	}
	break;
      case 77:	// [Right Arrow] - next subsong
	if(p && subsong < p->getsubsongs()-1) {
	  subsong++;
	  dopoll = false; while(inpoll) ;	// critical section...
	  totaltime = p->songlength(subsong);
	  p->rewind(subsong);
	  last_ms = time_ms = 0.0f;
	  dopoll = true;	// ...End critical section
	}
	break;
      case 73:        // [Page Up] - scroll up half window
	if(focus == &filesel) {
	  filesel.select_prev(filesel.getsizey() / 2);
	  filesel.update();
	} else if(focus == &infownd) {
	  infownd.scroll_up(infownd.getsizey() / 2);
	  infownd.update();
	} else if(focus == &instwnd) {
	  instwnd.scroll_up(instwnd.getsizey() / 2);
	  instwnd.update();
	}
	break;
      case 81:        // [Page Down] - scroll down half window
	if(focus == &filesel) {
	  filesel.select_next(filesel.getsizey() / 2);
	  filesel.update();
	} else if(focus == &infownd) {
	  infownd.scroll_down(infownd.getsizey() / 2);
	  infownd.update();
	} else if(focus == &instwnd) {
	  instwnd.scroll_down(instwnd.getsizey() / 2);
	  instwnd.update();
	}
	break;
      case 71:        // [Home] - scroll to start
	if(focus == &filesel) {
	  filesel.setselection(0);
	  filesel.update();
	} else if(focus == &infownd) {
	  infownd.scroll_set(0);
	  infownd.update();
	} else if(focus == &instwnd) {
	  instwnd.scroll_set(0);
	  instwnd.update();
	}
	break;
      case 79:        // [End] - scroll to end
	if(focus == &filesel) {
	  filesel.setselection(0xffff);
	  filesel.update();
	} else if(focus == &infownd) {
	  infownd.scroll_set(0xffff);
	  infownd.update();
	} else if(focus == &instwnd) {
	  instwnd.scroll_set(0xffff);
	  instwnd.update();
	}
	break;
      }
    else		// handle all normal keys
      switch(inkey) {
      case 9:         // [TAB] - Cycle through windows
	window_cycle();
	break;
      case 13:        // [Return] - Activate
	if(focus == &filesel)
	  activate();
	break;
      case 27:        // [ESC] - Stop music / Exit to DOS
	if(p) {
	  stop();
	  reset_windows();
	} else
	  quit = true;
	break;
      case ' ':	// [Space] - fast forward
	fast_forward(FF_MSEC);
	break;
      case 'M':	// refresh song info
	refresh_songdesc(infownd);
	break;
      case 'D':	// shell to DOS
	dosshell(getenv("COMSPEC"));
	filesel.refresh(); wnds.update();
	break;
      case '+':       // [+] - Increase volume
	adjust_volume(-1);
	break;
      case '-':       // [-] - Decrease volume
	adjust_volume(+1);
	break;
      }
  } while(!quit);

  // deinit
#ifdef HAVE_WCC_TIMER_H
    tmClose();
#elif defined HAVE_GCC_TIMER_H
    timer_deinit();
#endif
  stop();
  setvideoinfo(&dosvideo);
  {
    unsigned int dummy;
    _dos_setdrive(prgdrive, &dummy);
  }
  chdir(prgdir);
  free(prgdir);
  if(tmpfn) { rmdir(tmpfn); free(tmpfn); }
#ifdef DEBUG
  dbg_printf("main(): clean shutdown.\n");
  fclose(f_log);
#endif
  return EXIT_SUCCESS;
}