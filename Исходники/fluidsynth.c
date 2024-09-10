/*
 * main
 */
int main(int argc, char** argv)
{
  fluid_settings_t* settings;
  int arg1 = 1;
  char buf[512];
  int c, i;
  int interactive = 1;
  int midi_in = 1;
  fluid_player_t* player = NULL;
  fluid_midi_router_t* router = NULL;
  //fluid_sequencer_t* sequencer = NULL;
  fluid_midi_driver_t* mdriver = NULL;
  fluid_audio_driver_t* adriver = NULL;
  fluid_synth_t* synth = NULL;
  fluid_server_t* server = NULL;
  char* config_file = NULL;
  int audio_groups = 0;
  int audio_channels = 0;
  int with_server = 0;
  int dump = 0;
  int fast_render = 0;
  int connect_lash = 1;
  char *optchars = "a:C:c:dE:f:F:G:g:hijK:L:lm:nO:o:p:R:r:sT:Vvz:";
#ifdef LASH_ENABLED
  int enabled_lash = 0;		/* set to TRUE if lash gets enabled */
  fluid_lash_args_t *lash_args;

  lash_args = fluid_lash_extract_args (&argc, &argv);
#endif

  print_welcome ();

  settings = new_fluid_settings();

#ifdef GETOPT_SUPPORT	/* pre section of GETOPT supported argument handling */
  opterr = 0;

  while (1) {
    int option_index = 0;

    static struct option long_options[] = {
      {"audio-bufcount", 1, 0, 'c'},
      {"audio-bufsize", 1, 0, 'z'},
      {"audio-channels", 1, 0, 'L'},
      {"audio-driver", 1, 0, 'a'},
      {"audio-file-endian", 1, 0, 'E'},
      {"audio-file-format", 1, 0, 'O'},
      {"audio-file-type", 1, 0, 'T'},
      {"audio-groups", 1, 0, 'G'},
      {"chorus", 1, 0, 'C'},
      {"connect-jack-outputs", 0, 0, 'j'},
      {"disable-lash", 0, 0, 'l'},
      {"dump", 0, 0, 'd'},
      {"fast-render", 1, 0, 'F'},
      {"gain", 1, 0, 'g'},
      {"help", 0, 0, 'h'},
      {"load-config", 1, 0, 'f'},
      {"midi-channels", 1, 0, 'K'},
      {"midi-driver", 1, 0, 'm'},
      {"no-midi-in", 0, 0, 'n'},
      {"no-shell", 0, 0, 'i'},
      {"option", 1, 0, 'o'},
      {"portname", 1, 0, 'p'},
      {"reverb", 1, 0, 'R'},
      {"sample-rate", 1, 0, 'r'},
      {"server", 0, 0, 's'},
      {"verbose", 0, 0, 'v'},
      {"version", 0, 0, 'V'},
      {0, 0, 0, 0}
    };

    c = getopt_long(argc, argv, optchars, long_options, &option_index);
    if (c == -1) {
      break;
    }
#else	/* "pre" section to non getopt argument handling */
  for (i = 1; i < argc; i++) {
    char *optarg;

    /* Skip non switch arguments (assume they are file names) */
    if ((argv[i][0] != '-') || (argv[i][1] == '\0')) break;

    c = argv[i][1];

    optarg = strchr (optchars, c);	/* find the option character in optchars */
    if (optarg && optarg[1] == ':')	/* colon follows if switch argument expected */
    {
      if (++i >= argc)
      {
	printf ("Option -%c requires an argument\n", c);
	print_usage();
	exit(0);
      }
      else
      {
	optarg = argv[i];
	if (optarg[0] == '-')
	{
	  printf ("Expected argument to option -%c found switch instead\n", c);
	  print_usage();
	  exit(0);
	}
      }
    }
    else optarg = "";
#endif

    switch (c) {
#ifdef GETOPT_SUPPORT
    case 0:	/* shouldn't normally happen, a long option's flag is set to NULL */
      printf ("option %s", long_options[option_index].name);
      if (optarg) {
	printf (" with arg %s", optarg);
      }
      printf ("\n");
      break;
#endif
    case 'a':
      if (FLUID_STRCMP (optarg, "help") == 0)
      {
        printf ("-a options (audio driver):\n   ");
        show_settings_str_options (settings, "audio.driver");
        exit (0);
      }
      else fluid_settings_setstr(settings, "audio.driver", optarg);
      break;
    case 'C':
      if ((optarg != NULL) && ((strcmp(optarg, "0") == 0) || (strcmp(optarg, "no") == 0))) {
	fluid_settings_setint(settings, "synth.chorus.active", FALSE);
      } else {
	fluid_settings_setint(settings, "synth.chorus.active", TRUE);
      }
      break;
    case 'c':
      fluid_settings_setint(settings, "audio.periods", atoi(optarg));
      break;
    case 'd':
      fluid_settings_setint(settings, "synth.dump", TRUE);
      dump = 1;
      break;
    case 'E':
      if (FLUID_STRCMP (optarg, "help") == 0)
      {
        printf ("-E options (audio file byte order):\n   ");
        show_settings_str_options (settings, "audio.file.endian");

#if LIBSNDFILE_SUPPORT
        printf ("\nauto: Use audio file format's default endian byte order\n"
                "cpu: Use CPU native byte order\n");
#else
        printf ("\nNOTE: No libsndfile support!\n"
                "cpu: Use CPU native byte order\n");
#endif
        exit (0);
      }
      else fluid_settings_setstr(settings, "audio.file.endian", optarg);
      break;
    case 'f':
      config_file = optarg;
      break;
    case 'F':
      fluid_settings_setstr(settings, "audio.file.name", optarg);
      fast_render = 1;
      break;
    case 'G':
      audio_groups = atoi(optarg);
      break;
    case 'g':
      fluid_settings_setnum(settings, "synth.gain", atof(optarg));
      break;
    case 'h':
      print_help(settings);
      break;
    case 'i':
      interactive = 0;
      break;
    case 'j':
      fluid_settings_setint(settings, "audio.jack.autoconnect", 1);
      break;
    case 'K':
      fluid_settings_setint(settings, "synth.midi-channels", atoi(optarg));
      break;
    case 'L':
      audio_channels = atoi(optarg);
      fluid_settings_setint(settings, "synth.audio-channels", audio_channels);
      break;
    case 'l':			/* disable LASH */
      connect_lash = 0;
      break;
    case 'm':
      if (FLUID_STRCMP (optarg, "help") == 0)
      {
        printf ("-m options (MIDI driver):\n   ");
        show_settings_str_options (settings, "midi.driver");
        exit (0);
      }
      else fluid_settings_setstr(settings, "midi.driver", optarg);
      break;
    case 'n':
      midi_in = 0;
      break;
    case 'O':
      if (FLUID_STRCMP (optarg, "help") == 0)
      {
        printf ("-O options (audio file format):\n   ");
        show_settings_str_options (settings, "audio.file.format");

#if LIBSNDFILE_SUPPORT
        printf ("\ns8, s16, s24, s32: Signed PCM audio of the given number of bits\n");
        printf ("float, double: 32 bit and 64 bit floating point audio\n");
        printf ("u8: Unsigned 8 bit audio\n");
#else
        printf ("\nNOTE: No libsndfile support!\n");
#endif
        exit (0);
      }
      else fluid_settings_setstr(settings, "audio.file.format", optarg);
      break;
    case 'o':
      process_o_cmd_line_option(settings, optarg);
      break;
    case 'p' :
      fluid_settings_setstr(settings, "midi.portname", optarg);
      break;
    case 'R':
      if ((optarg != NULL) && ((strcmp(optarg, "0") == 0) || (strcmp(optarg, "no") == 0))) {
	fluid_settings_setint(settings, "synth.reverb.active", FALSE);
      } else {
	fluid_settings_setint(settings, "synth.reverb.active", TRUE);
      }
      break;
    case 'r':
      fluid_settings_setnum(settings, "synth.sample-rate", atof(optarg));
      break;
    case 's':
      with_server = 1;
      break;
    case 'T':
      if (FLUID_STRCMP (optarg, "help") == 0)
      {
        printf ("-T options (audio file type):\n   ");
        show_settings_str_options (settings, "audio.file.type");

#if LIBSNDFILE_SUPPORT
        printf ("\nauto: Determine type from file name extension, defaults to \"wav\"\n");
#else
        printf ("\nNOTE: No libsndfile support!\n");
#endif
        exit (0);
      }
      else fluid_settings_setstr(settings, "audio.file.type", optarg);
      break;
    case 'V':
      printf("FluidSynth %s\n", VERSION);
      exit (0);
      break;
    case 'v':
      fluid_settings_setint(settings, "synth.verbose", TRUE);
      break;
    case 'z':
      fluid_settings_setint(settings, "audio.period-size", atoi(optarg));
      break;
#ifdef GETOPT_SUPPORT
    case '?':
      printf ("Unknown option %c\n", optopt);
      print_usage();
      exit(0);
      break;
    default:
      printf ("?? getopt returned character code 0%o ??\n", c);
      break;
#else			/* Non getopt default case */
    default:
      printf ("Unknown switch '%c'\n", c);
      print_usage();
      exit(0);
      break;
#endif
    }	/* end of switch statement */
  }	/* end of loop */

#ifdef GETOPT_SUPPORT
  arg1 = optind;
#else
  arg1 = i;
#endif

  /* option help requested?  "-o help" */
  if (option_help)
  {
    printf ("FluidSynth settings:\n");
    fluid_settings_foreach (settings, settings, settings_foreach_func);
    exit (0);
  }

#ifdef WIN32
  SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS);
#endif

#ifdef LASH_ENABLED
  /* connect to the lash server */
  if (connect_lash)
    {
      enabled_lash = fluid_lash_connect (lash_args);
      fluid_settings_setint (settings, "lash.enable", enabled_lash ? 1 : 0);
    }
#endif

  /* The 'groups' setting is only relevant for LADSPA operation
   * If not given, set number groups to number of audio channels, because
   * they are the same (there is nothing between synth output and 'sound card')
   */
  if ((audio_groups == 0) && (audio_channels != 0)) {
      audio_groups = audio_channels;
  }
  fluid_settings_setint(settings, "synth.audio-groups", audio_groups);

  if (fast_render) {
    midi_in = 0;
    interactive = 0;
    with_server = 0;
    fluid_settings_setstr(settings, "player.timing-source", "sample");  
    fluid_settings_setint(settings, "synth.parallel-render", 1); /* TODO: Fast_render should not need this, but currently do */
  }
  
  /* create the synthesizer */
  synth = new_fluid_synth(settings);
  if (synth == NULL) {
    fprintf(stderr, "Failed to create the synthesizer\n");
    exit(-1);
  }

  cmd_handler = new_fluid_cmd_handler(synth);
  if (cmd_handler == NULL) {
    fprintf(stderr, "Failed to create the command handler\n");
    goto cleanup;
  }

  /* load the soundfonts (check that all non options are SoundFont or MIDI files) */
  for (i = arg1; i < argc; i++) {
    if (fluid_is_soundfont(argv[i]))
    {
      if (fluid_synth_sfload(synth, argv[i], 1) == -1)
	fprintf(stderr, "Failed to load the SoundFont %s\n", argv[i]);
    }
    else if (!fluid_is_midifile(argv[i]))
      fprintf (stderr, "Parameter '%s' not a SoundFont or MIDI file or error occurred identifying it.\n",
	       argv[i]);
  }

#ifdef HAVE_SIGNAL_H
/*   signal(SIGINT, handle_signal); */
#endif

  /* start the synthesis thread */
  if (!fast_render) {
    adriver = new_fluid_audio_driver(settings, synth);
    if (adriver == NULL) {
      fprintf(stderr, "Failed to create the audio driver\n");
      goto cleanup;
    }
  }


  /* start the midi router and link it to the synth */
#if WITH_MIDI
  if (midi_in) {
    /* In dump mode, text output is generated for events going into and out of the router.
     * The example dump functions are put into the chain before and after the router..
     */
    //sequencer = new_fluid_sequencer2(0);

    router = new_fluid_midi_router(
      settings,
      dump ? fluid_midi_dump_postrouter : fluid_synth_handle_midi_event,
      (void*)synth);

    if (router == NULL) {
      fprintf(stderr, "Failed to create the MIDI input router; no MIDI input\n"
	      "will be available. You can access the synthesizer \n"
	      "through the console.\n");
    } else {
      fluid_synth_set_midi_router(synth, router); /* Fixme, needed for command handler */
//      fluid_sequencer_register_fluidsynth(sequencer, synth);
      mdriver = new_fluid_midi_driver(
	settings,
	dump ? fluid_midi_dump_prerouter : fluid_midi_router_handle_midi_event,
	(void*) router);
      if (mdriver == NULL) {
	fprintf(stderr, "Failed to create the MIDI thread; no MIDI input\n"
		"will be available. You can access the synthesizer \n"
		"through the console.\n");
      }
    }
  }
#endif

  /* run commands specified in config file */
  if (config_file != NULL) {
    fluid_source(cmd_handler, config_file);
  } else if (fluid_get_userconf(buf, 512) != NULL) {
    fluid_source(cmd_handler, buf);
  } else if (fluid_get_sysconf(buf, 512) != NULL) {
    fluid_source(cmd_handler, buf);
  }



  /* play the midi files, if any */
  for (i = arg1; i < argc; i++) {
    if ((argv[i][0] != '-') && fluid_is_midifile(argv[i])) {

      if (player == NULL) {
	player = new_fluid_player(synth);
	if (player == NULL) {
	  fprintf(stderr, "Failed to create the midifile player.\n"
		  "Continuing without a player.\n");
	  break;
	}
      }

      fluid_player_add(player, argv[i]);
    }
  }

  if (player != NULL) {
    fluid_player_play(player);
  }

  /* run the server, if requested */
#if !defined(MACINTOSH)
  if (with_server) {
    server = new_fluid_server(settings, newclient, synth);
    if (server == NULL) {
      fprintf(stderr, "Failed to create the server.\n"
	     "Continuing without it.\n");
    }
  }
#endif


#ifdef LASH_ENABLED
  if (enabled_lash)
    fluid_lash_create_thread (synth);
#endif

  /* run the shell */
  if (interactive) {
    printf ("Type 'help' for help topics.\n\n");

    /* In dump mode we set the prompt to "". The UI cannot easily
     * handle lines, which don't end with CR.  Changing the prompt
     * cannot be done through a command, because the current shell
     * does not handle empty arguments.  The ordinary case is dump ==
     * 0.
     */
    fluid_settings_setstr(settings, "shell.prompt", dump ? "" : "> ");
    fluid_usershell(settings, cmd_handler);
  }

  if (fast_render) {
    char *filename;
    if (player == NULL) {
      fprintf(stderr, "No midi file specified!\n");
      goto cleanup;
    } 

    fluid_settings_dupstr (settings, "audio.file.name", &filename);
    printf ("Rendering audio to file '%s'..\n", filename);
    if (filename) FLUID_FREE (filename);

    fast_render_loop(settings, synth, player);
  }

 cleanup:

#if !defined(MACINTOSH) && !defined(WIN32)
  if (server != NULL) {
    /* if the user typed 'quit' in the shell, kill the server */
    if (!interactive) {
      fluid_server_join(server);
    }
    delete_fluid_server(server);
  }
#endif

  if (cmd_handler != NULL) {
    delete_fluid_cmd_handler(cmd_handler);
  }

  if (player != NULL) {
    /* if the user typed 'quit' in the shell, stop the player */
    if (interactive) {
      fluid_player_stop(player);
    }
    if (adriver != NULL || !fluid_settings_str_equal(settings,  "player.timing-source", "sample")) {
      /* if no audio driver and sample timers are used, nothing makes the player advance */  
      fluid_player_join(player);
    }
    delete_fluid_player(player);
  }

  if (router) {
#if WITH_MIDI
    if (mdriver) {
      delete_fluid_midi_driver(mdriver);
    }
    delete_fluid_midi_router(router);
#endif
  }

  /*if (sequencer) {
    delete_fluid_sequencer(sequencer);
  }*/

  if (adriver) {
    delete_fluid_audio_driver(adriver);
  }

  if (synth) {
    delete_fluid_synth(synth);
  }

  if (settings) {
    delete_fluid_settings(settings);
  }

  return 0;
}

static fluid_cmd_handler_t* newclient(void* data, char* addr)
{
  fluid_synth_t* synth = (fluid_synth_t*) data;
  return new_fluid_cmd_handler(synth);
}