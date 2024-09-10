int
main(void)
{

  XGCValues       controlGCVals;
  int             i,code;
  view2DStruct    viewData;

  char property[256];
  char *prop = &property[0];
  char *str_type[20];
  XrmValue value;


  /**** Set up display ****/
  if ((dsply = XOpenDisplay(getenv("DISPLAY"))) == NULL)
    fprintf(stderr,"Could not open the display.\n");
  scrn  = DefaultScreen(dsply);
  rtWindow  = RootWindow(dsply,scrn);

  /**** link Xwindows to viewports - X10 feature ****/
  table        = XCreateAssocTable(nbuckets);

  /**** Create FriCAS color map ****/
  totalColors = XInitSpadFill(dsply,scrn,&colorMap,
                              &totalHues,&totalSolidShades,
                              &totalDitheredAndSolids,&totalShades);

  if (totalColors < 0) {
    fprintf(stderr,">>Error: Could not allocate all the necessary colors.\n");
    exitWithAck(RootWindow(dsply,scrn),Window,-1);
  }

  mergeDatabases();


  /*** Determine whether monochrome or color is used ***/
  if (XrmGetResource(rDB,"Axiom.2D.monochrome","",str_type,&value) == True)
    (void) strncpy(prop,value.addr,(int)value.size);
  else
    (void) strcpy(prop, "off");

  mono = ((totalSolid == 2) || (strcmp(prop,"on") == 0));

  if (XrmGetResource(rDB,"Axiom.2D.inverse","",str_type,&value) == True)
    (void) strncpy(prop,value.addr,(int)value.size);
  else
    (void) strcpy(prop, "off");

  if (mono)
    if (strcmp(prop,"on") == 0) {             /* 0 if equal (inverse video) */
      foregroundColor = WhitePixel(dsply,scrn);
      backgroundColor = BlackPixel(dsply,scrn);
    } else {                                  /* off (no inverse video) */
      foregroundColor = BlackPixel(dsply,scrn);
      backgroundColor = WhitePixel(dsply,scrn);
    }
  else   /* inverse of inverse in color (for some strange reason) */
    if (strcmp(prop,"on") == 0) {         /* 0 if equal (inverse video) */
      foregroundColor = WhitePixel(dsply,scrn);
      backgroundColor = BlackPixel(dsply,scrn);
    } else {                                  /* off (no inverse video) */
      foregroundColor = BlackPixel(dsply,scrn);
      backgroundColor = WhitePixel(dsply,scrn);
    }


  /* read default file name for postScript output */
  if (XrmGetResource(rDB,
                     "Axiom.2D.postscriptFile",
                     "",
                     str_type, &value) == True)
    (void) strncpy(prop,value.addr,(int)value.size);
  else
    (void) strcpy(prop, "axiom2D.ps");

  PSfilename = (char *)malloc(strlen(prop)+1);
  strcpy(PSfilename,prop);



  /**** Open global fonts ****/
  serverFont = XQueryFont(dsply,XGContextFromGC(DefaultGC(dsply,scrn)));

  if (XrmGetResource(rDB,
                     "Axiom.2D.messageFont",
                     "Axiom.2D.Font",
                     str_type, &value) == True)
    (void) strncpy(prop,value.addr,(int)value.size);
  else
    (void) strcpy(prop,messageFontDefault);
  if ((globalFont = XLoadQueryFont(dsply, prop)) == NULL) {
    fprintf(stderr,
            "Warning:  could not get the %s font for messageFont\n",prop);
    globalFont = serverFont;
  }

  if (XrmGetResource(rDB,
                     "Axiom.2D.buttonFont",
                     "Axiom.2D.Font",
                     str_type, &value) == True)
    (void) strncpy(prop,value.addr,(int)value.size);
  else
    (void) strcpy(prop,buttonFontDefault);
  if ((buttonFont = XLoadQueryFont(dsply, prop)) == NULL) {
    fprintf(stderr,
            "Warning:  could not get the %s font for buttonFont\n",prop);
    buttonFont = serverFont;
  }

  if (XrmGetResource(rDB,
                     "Axiom.2D.headerFont",
                     "Axiom.2D.Font",
                     str_type, &value) == True)
     (void) strncpy(prop,value.addr,(int)value.size);
  else
    (void) strcpy(prop,headerFontDefault);

  if ((headerFont = XLoadQueryFont(dsply, prop)) == NULL) {
    fprintf(stderr,
            "Warning:  could not get the %s font for headerFont\n",prop);
    headerFont = serverFont;
  }

  if (XrmGetResource(rDB,
                     "Axiom.2D.titleFont",
                     "Axiom.2D.Font",
                     str_type,&value) == True)
    (void) strncpy(prop,value.addr,(int)value.size);
  else
    (void) strcpy(prop,titleFontDefault);

  if ((titleFont = XLoadQueryFont(dsply, prop)) == NULL) {
    fprintf(stderr,
            "Warning:  could not get the %s font for titleFont\n",prop);
    titleFont = serverFont;
  }

  if (XrmGetResource(rDB,
                     "Axiom.2D.graphFont",
                     "Axiom.2D.Font",
                     str_type,&value) == True)
    (void) strncpy(prop,value.addr,(int)value.size);
  else
    (void) strcpy(prop,graphFontDefault);

  if ((graphFont = XLoadQueryFont(dsply, prop)) == NULL) {
    fprintf(stderr,
            "Warning:  could not get the %s font for graphFont\n",prop);
    graphFont = serverFont;
  }

  if (XrmGetResource(rDB,
                     "Axiom.2D.unitFont",
                     "Axiom.2D.Font",
                     str_type,&value) == True)
    (void) strncpy(prop,value.addr,(int)value.size);
  else
    (void) strcpy(prop,unitFontDefault);

  if ((unitFont = XLoadQueryFont(dsply, prop)) == NULL) {
     fprintf(stderr,
             "Warning:  could not get the %s font for unitFont\n",prop);
     unitFont = serverFont;
  }


  /**** Create widely used Graphic Contexts ****/
  PSGlobalInit();
  /* must initiate before using any G/PS functions
     need character name: used as postscript GC variable
     need to create ps GCs for all GCs used by drawings in viewWindow */

  /* globalGC1 */

  controlGCVals.foreground = monoColor(axesColorDefault);
  controlGCVals.background = backgroundColor;
  globalGC1 = XCreateGC(dsply,rtWindow,GCForeground | GCBackground ,
                        &controlGCVals);
  carefullySetFont(globalGC1,globalFont);


  /* create the equivalent GCs for ps */
  PSCreateContext(globalGC1, "globalGC1", psNormalWidth, psButtCap,
                  psMiterJoin, psWhite, psBlack);

  /* controlMessageGC */

  controlGCVals.foreground = controlMessageColor;
  controlMessageGC = XCreateGC(dsply,rtWindow,GCForeground | GCBackground
                               ,&controlGCVals);
  carefullySetFont(controlMessageGC,globalFont);

  /* globalGC2 */

  controlGCVals.foreground = monoColor(labelColor);
  controlGCVals.background = backgroundColor;
  globalGC2 = XCreateGC(dsply,rtWindow,GCForeground | GCBackground,
                        &controlGCVals);
  carefullySetFont(globalGC2,buttonFont);
  PSCreateContext(globalGC2, "globalGC2", psNormalWidth, psButtCap,
                  psMiterJoin, psWhite, psBlack);

  /* trashGC  */

  trashGC = XCreateGC(dsply,rtWindow,0,&controlGCVals);
  carefullySetFont(trashGC,buttonFont);
  PSCreateContext(trashGC, "trashGC", psNormalWidth, psButtCap,
                  psMiterJoin, psWhite, psBlack);

  /* globGC */

  globGC = XCreateGC(dsply,rtWindow,0,&controlGCVals);
  carefullySetFont(globGC,headerFont);
  PSCreateContext(globGC, "globGC", psNormalWidth, psButtCap,
                  psMiterJoin, psWhite, psBlack);

  /* anotherGC  */

  controlGCVals.line_width = colorWidth;
  anotherGC  = XCreateGC(dsply,rtWindow,GCBackground,&controlGCVals);
  carefullySetFont(anotherGC,titleFont);
  PSCreateContext(anotherGC, "anotherGC", psNormalWidth, psButtCap,
                  psMiterJoin, psWhite, psBlack);

  /* processGC */

  gcVals.background = backgroundColor;
  processGC         = XCreateGC(dsply,rtWindow,GCBackground ,&gcVals);
  carefullySetFont(processGC,buttonFont);

  /* graphGC */

  graphGC           = XCreateGC(dsply,rtWindow,GCBackground,&gcVals);
  carefullySetFont(graphGC,graphFont);
  PSCreateContext(graphGC, "graphGC", psNormalWidth, psButtCap,
                  psMiterJoin, psWhite, psBlack);

  /* unitGC */

  unitGC            = XCreateGC(dsply,rtWindow,GCBackground ,&gcVals);
  carefullySetFont(unitGC,unitFont);
  PSCreateContext(unitGC, "unitGC", psNormalWidth, psButtCap,
                  psMiterJoin, psWhite, psBlack);

  /**** Initialize Graph States ****/

  for (i=0; i<maxGraphs; i++) {
    graphStateArray[i].scaleX = 0.9;
    graphStateArray[i].scaleY = 0.9;
    graphStateArray[i].deltaX = 0.0;
    graphStateArray[i].deltaY = 0.0;
    graphStateArray[i].centerX = 0.0;
    graphStateArray[i].centerY = 0.0;
    graphStateArray[i].pointsOn  = yes;
    graphStateArray[i].connectOn = yes;
    graphStateArray[i].splineOn  = no;
    graphStateArray[i].axesOn    = yes;
    graphStateArray[i].unitsOn   = no;
    graphStateArray[i].showing   = no;
    graphStateArray[i].selected  = no;
    graphStateBackupArray[i] = graphStateArray[i];
  }

  /**** Get Data from the Viewport Manager ****/

  i = 123;
  code=check(write(Socket,&i,intSize));

  /* Check if I am getting stuff from FriCAS or, if I am viewAlone. */
  readViewman(&viewAloned,intSize);
  readViewman(&viewData,sizeof(view2DStruct));
  readViewman(&i,intSize);

  if (!(viewData.title = (char *)malloc(i))) {
    fprintf(stderr,
            "ERROR: Ran out of memory trying to receive the title.\n");
    exitWithAck(RootWindow(dsply,scrn),Window,-1);
  }
  readViewman(viewData.title,i);

  for (i=0; i<maxGraphs; i++) {
    readViewman(&(graphArray[i].key),intSize);
    if (graphArray[i].key) {            /** this graph slot has data **/
      getGraphFromViewman(i);
    } /* if graph exists (graphArray[i].key is not zero) */
  } /* for i in graphs */

  viewport = makeView2D(&viewData);
  control = viewport->controlPanel;

  bsdSignal(SIGTERM,goodbye,DontRestartSystemCalls);

  /* send acknowledgement to viewport manager */
  i = 345;
  check(write(Socket,&(viewport->viewWindow),sizeof(Window)));

  processEvents();

  goodbye(-1);
  return(0);  /* control never reaches here but compiler complains */
} /* main() */