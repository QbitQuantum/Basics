int main(int argc, char **argv)
{
  int optind;
  char **playlist_array;
  int items;
  struct stat stat_buf;
  int i;

  setlocale(LC_ALL, "");
  bindtextdomain(PACKAGE, LOCALEDIR);
  textdomain(PACKAGE);

  ao_initialize();
  stat_format = stat_format_create();
  options_init(&options);
  file_options_init(file_opts);

  parse_std_configs(file_opts);
  options.playlist = playlist_create();
  optind = parse_cmdline_options(argc, argv, &options, file_opts);

  audio_play_arg.devices = options.devices;
  audio_play_arg.stat_format = stat_format;

  /* Add remaining arguments to playlist */
  for (i = optind; i < argc; i++) {
    if (stat(argv[i], &stat_buf) == 0) {

      if (S_ISDIR(stat_buf.st_mode)) {
	if (playlist_append_directory(options.playlist, argv[i]) == 0)
	  fprintf(stderr, 
		  _("Warning: Could not read directory %s.\n"), argv[i]);
      } else {
	playlist_append_file(options.playlist, argv[i]);
      }
    } else /* If we can't stat it, it might be a non-disk source */
      playlist_append_file(options.playlist, argv[i]);


  }


  /* Do we have anything left to play? */
  if (playlist_length(options.playlist) == 0) {
    cmdline_usage();
    exit(1);
  } else {
    playlist_array = playlist_to_array(options.playlist, &items);
    playlist_destroy(options.playlist);
    options.playlist = NULL;
  }

  /* Don't use status_message until after this point! */
  status_set_verbosity(options.verbosity);

  print_audio_devices_info(options.devices);

  
  /* Setup buffer */ 
  if (options.buffer_size > 0) {
    audio_buffer = buffer_create(options.buffer_size,
				 options.buffer_size * options.prebuffer / 100,
				 audio_play_callback, &audio_play_arg,
				 AUDIO_CHUNK_SIZE);
    if (audio_buffer == NULL) {
      status_error(_("Error: Could not create audio buffer.\n"));
      exit(1);
    }
  } else
    audio_buffer = NULL;


  /* Shuffle playlist */
  if (options.shuffle) {
    int i;
    
    srandom(time(NULL));
    
    for (i = 0; i < items; i++) {
      int j = i + random() % (items - i);
      char *temp = playlist_array[i];
      playlist_array[i] = playlist_array[j];
      playlist_array[j] = temp;
    }
  }

  /* Setup signal handlers and callbacks */

  ATEXIT (exit_cleanup);
  signal (SIGINT, signal_handler);
  signal (SIGTSTP, signal_handler);
  signal (SIGCONT, signal_handler);
  signal (SIGTERM, signal_handler);

  /* Play the files/streams */
  i = 0;
  while (i < items && !sig_request.exit) {
    play(playlist_array[i]);
    i++;
  }

  playlist_array_destroy(playlist_array, items);

  exit (0);
}