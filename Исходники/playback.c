int playbackFileInit (char *file)
{

#if DEBUG_LEVEL & DBG_PLBK
  logMsg (DBG_PLBK, "Playback routines using file: %s, ", file);
#endif

  if (playbackSetMode (NULL) == RECORD_MODE) {
    logMsg (DBG_PLBK, "mode: 'RECORD_MODE'\n");
  } else {
    logMsg (DBG_PLBK, "mode: 'PLAY_MODE'\n");
  }


  switch (playbackSetMode (NULL)) {

  case PLAY_MODE:

    if ((stream = fopen (file, "r")) == NULL) {

      logMsg (DBG_GEN, "Uh Oh! Couldn't open playback file: %s\n", strerror (errno));
      shutDown ();

    }

    /* Lead the header into memory */
    if (fread (&header, sizeof (struct playback_h), 1, stream) == 0) {

      logMsg (DBG_GEN, "Error reading in playback header: %s\n", strerror (errno));
      return 0;

    }

    break;

  case RECORD_MODE:

    if ((stream = fopen (file, "w")) == NULL) {

      logMsg (DBG_GEN, "Uh Oh! Couldn't create recoding file: %s\n",
              strerror (errno));
      shutdown ();

    }

    memset (&header, 0, sizeof (struct playback_h));

    header.major_ver = PLAYBACK_MAJOR_VER;
    header.minor_ver = PLAYBACK_MINOR_VER;
    header.max_events = MAX_PLAYBACK_EVENTS;

    /* Our initial start position can be found right after
     * the header
     */
    header.start_pos = sizeof (struct playback_h);

    gettimeofday (&header.start_t, NULL);

    /* Initialize the file with the header. Note that end_t is initially
     * left at zero
     */
    if (fwrite (&header, sizeof (struct playback_h), 1, stream) == 0) {

      logMsg (DBG_GEN, "Error initializing file with playback header: %s\n",
              strerror (errno));
      return 0;

    }

    /* Flush out the header */
    fflush (stream);
    break;

  default:

    logMsg (DBG_DEF,
            "Uh Oh! peepd asked to use invalid mode for playback. Please specify: {PLAY_MODE, RECORD_MODE}\n");
    shutdown ();

  }

#if DEBUG_LEVEL & DBG_PLBK
  logMsg (DBG_PLBK, "The playback header is:\n");
  logMsg (DBG_PLBK, "\tmajor ver:      [%d]\n", header.major_ver);
  logMsg (DBG_PLBK, "\tminor ver:      [%d]\n", header.minor_ver);
  logMsg (DBG_PLBK, "\tmax events:     [%d]\n", header.max_events);
  logMsg (DBG_PLBK, "\tevents written: [%d]\n", header.written);
  logMsg (DBG_PLBK, "\tstart pos:      [%d]\n", header.start_pos);
  logMsg (DBG_PLBK, "\tstart time:     [%lf]\n", TP_IN_FP_SECS (header.start_t));
  logMsg (DBG_PLBK, "\tend time:       [%lf]\n", TP_IN_FP_SECS (header.end_t));
#endif

  return 1;

}