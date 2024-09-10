int displayStats(char *filename) {
  Bool   done = False;
  XEvent curEvent;
  char   c;
  long   event_mask = 0xFFFFFFFF;
  long   nBuf = 2;
  int    i;

  /* Load data */
  FILE *fp = fopen(filename,"r");
  if (!fp) {
    printf("Nothing to draw\n");
    return;
  }
  fscanf(fp, "numR=%d\n", &numR);
  r                 = malloc(sizeof(float)*numR);
  mean_elongation   = malloc(sizeof(float)*numR);
  mean_polarization = malloc(sizeof(float)*numR);
  std_elongation    = malloc(sizeof(float)*numR);
  std_polarization  = malloc(sizeof(float)*numR);
  for (i=0; i < numR; i++)
    fscanf(fp,"r=%f,mean_elongation=%f,std_elongation=%f,mean_polarization=%f,std_polarization=%f\n",
          &r[i],&mean_elongation[i],&std_elongation[i],
          &mean_polarization[i],&std_polarization[i]);
  fclose(fp);
  minr = min(r,numR);
  maxr = max(r,numR);
  minElongation = min(mean_elongation,numR);
  maxElongation = max(mean_elongation,numR);
  minPolarization = min(mean_polarization,numR);
  maxPolarization = max(mean_polarization,numR);
  
  /* initialize the window  */
  initWindow( 600, 400 );

  drawFigure();

  while(!done) {

    /** Draw stuff here **/
    /*
    if (mode == MOVIE_MODE) {
      t2 = get_time_sec();
      if (t2-t1 > secondsPerFrame && file->curFrame < file->numFrames) {
        readFrame(Px,Py,Vx,Vy,file);
        drawFigure();
        t1 = t2;
      }
    }
    */

    usleep( 33 ); // sleep a little

    // check for events
    if(XCheckWindowEvent(curDisplay, curWindow, event_mask, &curEvent)) {

      switch (curEvent.type) {

      case KeyPress:
        /*
           access string using XLookupString(*event,*char,numChars,NULL,NULL)
        */
        if(XLookupString((XKeyEvent *)&curEvent, &c, 1, NULL, NULL) == 1) {
          switch(c) {
          case 'q':
	    // quit
	    done = True;
	    break;
          default:
            break;
          }
        }
        break;

      case Expose:
        refreshWindow();
        break;

      default:
       break;
      } // end switch over event type
    } // end if event
  } // end while

  closeWindow(nBuf);
  cleanup();
  return(0);
} // end displayStats