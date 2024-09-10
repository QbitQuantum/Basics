/******************************************************************************
Description.: this is the main worker thread
              it loops forever, grabs a fresh frame and calculates focus
Input Value.:
Return Value:
******************************************************************************/
void *worker_thread( void *arg ) {
  int frame_size=0;
  double sv=-1.0, max_sv=100.0, delta=500;
  int focus=255, step=10, max_focus=100, search_focus=1;

  if ( (frame = malloc(256*1024)) == NULL ) {
    OPRINT("not enough memory for worker thread\n");
    exit(EXIT_FAILURE);
  }

  /* set cleanup handler to cleanup allocated ressources */
  pthread_cleanup_push(worker_cleanup, NULL);

  while ( !pglobal->stop ) {
    DBG("waiting for fresh frame\n");
    pthread_cond_wait(&pglobal->db_update, &pglobal->db);

    /* read buffer */
    frame_size = pglobal->size;
    memcpy(frame, pglobal->buf, frame_size);

    pthread_mutex_unlock( &pglobal->db );

    /* process frame */
    sv = getFrameSharpnessValue(frame, frame_size);
    DBG("sharpness is: %f\n", sv);

    if ( search_focus || (ABS(sv-max_sv) > delta) ) {
      DBG("adjusting focus: %d\n", focus);

      /* entered because focus changed */
      if ( !search_focus ) {
        DBG("starting to search for focus\n");
        max_focus    = 255;
        focus        = 255;
        max_sv       = -1.0;
        search_focus = 1;
      }

      if ( focus <= 0 ) {
        focus = max_focus;
        DBG("max focus found at: %d\n", max_focus);
        search_focus = 0;
      }

      if ( search_focus ) {
        if (sv > max_sv) {
          /* sharpness is better then max now */
          DBG("found better focus at: %d\n", focus);
          max_focus = focus;
          max_sv = sv;
        }

        focus = MIN(MAX(focus-step,0), 255);
        DBG("decrement focus now to: %d\n", focus);
        //focus = pglobal->in.cmd(IN_CMD_FOCUS_SET, focus);
      }
    }

    if ( (delay > 0) && !search_focus ) {
      usleep(1000*delay);
    }
  }

  pthread_cleanup_pop(1);

  return NULL;
}