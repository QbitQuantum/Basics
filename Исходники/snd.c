    int main(int argc, char **argv)
  #endif
#endif
{
  int i;

#if HAVE_GSL
  /* if HAVE_GSL and the environment variable GSL_IEEE_MODE exists, use it */
  /* GSL_IEEE_MODE=double-precision,mask-underflow,mask-denormalized */
  if (getenv("GSL_IEEE_MODE") != NULL) 
    gsl_ieee_env_setup();
  gsl_set_error_handler(snd_gsl_error);
#endif

#if ENABLE_NLS && HAVE_GETTEXT && defined(LOCALE_DIR)
  /* both flags needed to avoid idiotic confusion on the Sun */
  #if HAVE_SETLOCALE
    setlocale (LC_ALL, "");
  #endif
  bindtextdomain (PACKAGE, LOCALE_DIR);
  textdomain (PACKAGE);
  /*
    (bindtextdomain "snd" "/usr/local/share/locale")
    (textdomain "snd")
    (define _ gettext)
    (display (_ "no selection"))

    but that is limited to Snd's messages
  */
#endif

  ss = (snd_state *)CALLOC(1, sizeof(snd_state));
  ss->fam_ok = false;
  ss->startup_errors = NULL;
  mus_sound_initialize(); /* has to precede version check (mus_audio_moniker needs to be setup in Alsa/Oss) */

#if HAVE_FORTH || HAVE_GAUCHE || HAVE_RUBY
  xen_initialize();
#endif

  for (i = 1; i < argc; i++)
    {
      if (strcmp(argv[i], "--version") == 0)
	{
	  fprintf(stdout, version_info());
	  snd_exit(0);
	}
      else
	{
	  if (strcmp(argv[i], "--help") == 0)
	    {
	      fprintf(stdout, _("Snd is a sound editor; see http://ccrma.stanford.edu/software/snd/.\n"));
	      fprintf(stdout, version_info());
	      snd_exit(0);
	    }
	}
    }

  initialize_format_lists();
  snd_set_global_defaults(false);
#if MUS_DEBUGGING
  ss->Trap_Segfault = false;
#else
  ss->Trap_Segfault = DEFAULT_TRAP_SEGFAULT;
#endif
  ss->jump_ok = false;
  allocate_regions(max_regions(ss));
  ss->init_window_x = DEFAULT_INIT_WINDOW_X; 
  ss->init_window_y = DEFAULT_INIT_WINDOW_Y; 
  ss->init_window_width = DEFAULT_INIT_WINDOW_WIDTH; 
  ss->init_window_height = DEFAULT_INIT_WINDOW_HEIGHT;
  ss->click_time = 100;
  init_sound_file_extensions();

  ss->max_sounds = 4;                 /* expands to accommodate any number of files */
  ss->sound_sync_max = 0;
  ss->stopped_explicitly = false;     /* C-g sets this flag so that we can interrupt various loops */
  ss->checking_explicitly = false;
  ss->reloading_updated_file = 0;
  ss->selected_sound = NO_SELECTION;
  ss->sounds = (snd_info **)CALLOC(ss->max_sounds, sizeof(snd_info *));
  ss->print_choice = PRINT_SND;
  ss->graph_hook_active = false;
  ss->lisp_graph_hook_active = false;
  ss->error_lock = false;
  ss->exiting = false;
  ss->deferred_regions = 0;
  ss->fam_connection = NULL;
  ss->snd_error_data = NULL;
  ss->snd_error_handler = NULL;
  ss->snd_warning_data = NULL;
  ss->snd_warning_handler = NULL;
  ss->xen_error_data = NULL;
  ss->xen_error_handler = NULL;

#if USE_NO_GUI || HAVE_RUBY || HAVE_FORTH || HAVE_GAUCHE
  ss->catch_exists = 1; /* scm_shell for USE_NO_GUI case */
#else
  ss->catch_exists = 0;
#endif
#if HAVE_GL && MUS_WITH_GL2PS
  ss->gl_printing = false;
#endif
  g_xen_initialize();
  ss->search_proc = XEN_UNDEFINED;
  ss->search_expr = NULL;
  ss->search_tree = NULL;
  mus_error_set_handler(mus_error_to_snd);
  mus_print_set_handler(mus_print_to_snd);

  initialize_load_path(); /* merge SND_PATH entries into the load-path */

#ifdef SND_AS_PD_EXTERNAL
  return;
#else
  #ifdef SND_AS_WIDGET
    return(ss); 
  #else
    snd_doit(argc, argv);
    #if (!HAVE_GUILE)
      return(0);
    #endif
  #endif
#endif
}