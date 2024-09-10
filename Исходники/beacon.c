void beacon_init (struct misc_config_s *pconfig, struct digi_config_s *pdigi)
{
	time_t now;
	int j;
	int count;
#if __WIN32__
	HANDLE beacon_th;
#else
	pthread_t beacon_tid;
#endif



#if DEBUG
	text_color_set(DW_COLOR_DEBUG);
	dw_printf ("beacon_init ( ... )\n");
#endif



/* 
 * Save parameters for later use.
 */
	g_misc_config_p = pconfig;
	g_digi_config_p = pdigi;

/*
 * Precompute the packet contents so any errors are 
 * Reported once at start up time rather than for each transmission.
 * If a serious error is found, set type to BEACON_IGNORE and that
 * table entry should be ignored later on.
 */
	for (j=0; j<g_misc_config_p->num_beacons; j++) {
	  int chan = g_misc_config_p->beacon[j].chan;

	  if (chan < 0) chan = 0;	/* For IGate, use channel 0 call. */

	  if (chan < pdigi->num_chans) {

	    if (strlen(pdigi->mycall[chan]) > 0 && strcasecmp(pdigi->mycall[chan], "NOCALL") != 0) {

              switch (g_misc_config_p->beacon[j].btype) {

	        case BEACON_OBJECT:

		  /* Object name is required. */

		  if (strlen(g_misc_config_p->beacon[j].objname) == 0) {
	            text_color_set(DW_COLOR_ERROR);
	            dw_printf ("Config file, line %d: OBJNAME is required for OBEACON.\n", g_misc_config_p->beacon[j].lineno);
		    g_misc_config_p->beacon[j].btype = BEACON_IGNORE;
		    continue;
		  }
		  /* Fall thru.  Ignore any warning about missing break. */

	        case BEACON_POSITION:

		  /* Location is required. */

		  if (g_misc_config_p->beacon[j].lat == G_UNKNOWN || g_misc_config_p->beacon[j].lon == G_UNKNOWN) {
	            text_color_set(DW_COLOR_ERROR);
	            dw_printf ("Config file, line %d: Latitude and longitude are required.\n", g_misc_config_p->beacon[j].lineno);
		    g_misc_config_p->beacon[j].btype = BEACON_IGNORE;
		    continue;
		  }	
		  break;

	        case BEACON_TRACKER:

#if defined(GPS_ENABLED) || defined(DEBUG_SIM)
		  g_using_gps++;
#else
	          text_color_set(DW_COLOR_ERROR);
	          dw_printf ("Config file, line %d: GPS tracker feature is not enabled.\n", g_misc_config_p->beacon[j].lineno);
	   	  g_misc_config_p->beacon[j].btype = BEACON_IGNORE;
	   	  continue;
#endif
		  break;

	        case BEACON_CUSTOM:

		  /* INFO is required. */

		  if (g_misc_config_p->beacon[j].custom_info == NULL) {
	            text_color_set(DW_COLOR_ERROR);
	            dw_printf ("Config file, line %d: INFO is required for custom beacon.\n", g_misc_config_p->beacon[j].lineno);
		    g_misc_config_p->beacon[j].btype = BEACON_IGNORE;
		    continue;
		  }	
		  break;

	        case BEACON_IGNORE:
		  break;
	      }
	    }
	    else {
	      text_color_set(DW_COLOR_ERROR);
	      dw_printf ("Config file, line %d: MYCALL must be set for beacon on channel %d. \n", g_misc_config_p->beacon[j].lineno, chan);
	      g_misc_config_p->beacon[j].btype = BEACON_IGNORE;
	    }
	  }
	  else {
	    text_color_set(DW_COLOR_ERROR);
	    dw_printf ("Config file, line %d: Invalid channel number %d for beacon. \n", g_misc_config_p->beacon[j].lineno, chan);
	    g_misc_config_p->beacon[j].btype = BEACON_IGNORE;
	  }
	}

/*
 * Calculate next time for each beacon.
 */

	now = time(NULL);

	for (j=0; j<g_misc_config_p->num_beacons; j++) {
#if DEBUG

	  text_color_set(DW_COLOR_DEBUG);
	  dw_printf ("beacon[%d] chan=%d, delay=%d, every=%d\n",
		j,
		g_misc_config_p->beacon[j].chan,
		g_misc_config_p->beacon[j].delay,
		g_misc_config_p->beacon[j].every);
#endif
	  g_misc_config_p->beacon[j].next = now + g_misc_config_p->beacon[j].delay;
	}


/*
 * Connect to GPS receiver if any tracker beacons are configured.
 * If open fails, disable all tracker beacons.
 */

#if DEBUG_SIM

	g_using_gps = 1;
	
#elif ENABLE_GPS

	if (g_using_gps > 0) {
	  int err;

	  err = dwgps_init();
	  if (err != 0) {
	    text_color_set(DW_COLOR_ERROR);
	    dw_printf ("All tracker beacons disabled.\n");
	    g_using_gps = 0;

	    for (j=0; j<g_misc_config_p->num_beacons; j++) {
              if (g_misc_config_p->beacon[j].btype == BEACON_TRACKER) {
		g_misc_config_p->beacon[j].btype = BEACON_IGNORE;
	      }
	    }
	  }

	}
#endif


/* 
 * Start up thread for processing only if at least one is valid.
 */

	count = 0;
	for (j=0; j<g_misc_config_p->num_beacons; j++) {
          if (g_misc_config_p->beacon[j].btype != BEACON_IGNORE) {
	    count++;
	  }
	}

	if (count >= 1) {

#if __WIN32__
	  beacon_th = (HANDLE)_beginthreadex (NULL, 0, &beacon_thread, NULL, 0, NULL);
	  if (beacon_th == NULL) {
	    text_color_set(DW_COLOR_ERROR);
	    dw_printf ("Could not create beacon thread\n");
	    return;
	  }
#else
	  int e;

	  e = pthread_create (&beacon_tid, NULL, beacon_thread, (void *)0);
	  if (e != 0) {
	    text_color_set(DW_COLOR_ERROR);
	    perror("Could not create beacon thread");
	    return;
	  }
#endif
	}


} /* end beacon_init */