GLUTwindow *
__glutCreateWindow(GLUTwindow * parent,
  int x, int y, int width, int height)
{
  GLUTwindow *window;
  XSetWindowAttributes wa;
  unsigned long attribMask;
  int winnum;
  int i;

#if defined(WIN32)
  WNDCLASS wc;
  if (!GetClassInfo(GetModuleHandle(NULL), "GLUT", &wc))
    __glutOpenWin32Connection(NULL);
#else
  if (!__glutDisplay)
    __glutOpenXConnection(NULL);
#endif
  winnum = getUnusedWindowSlot();
  window = (GLUTwindow *) malloc(sizeof(GLUTwindow));
  if (!window)
    __glutFatalError("out of memory.");
  window->num = winnum;

#if !defined(WIN32)
  window->vis = __glutDetermineWindowVisual(&window->treatAsSingle,
    &window->visAlloced);
  if (!window->vis) {
    __glutFatalError(
      "visual with necessary capabilities not found.");
  }
  __glutSetupColormap(window->vis, &window->colormap, &window->cmap);
#endif
  window->eventMask = StructureNotifyMask | ExposureMask;

  attribMask = CWBackPixmap | CWBorderPixel | CWColormap | CWEventMask;
  wa.background_pixmap = None;
  wa.border_pixel = 0;
  wa.colormap = window->cmap;
  wa.event_mask = window->eventMask;
  if (parent) {
    if (parent->eventMask & GLUT_HACK_STOP_PROPAGATE_MASK)
      wa.event_mask |= GLUT_HACK_STOP_PROPAGATE_MASK;
    attribMask |= CWDontPropagate;
    wa.do_not_propagate_mask = parent->eventMask & GLUT_DONT_PROPAGATE_FILTER_MASK;
  } else {
    wa.do_not_propagate_mask = 0;
  }

  /* Stash width and height before Win32's __glutAdjustCoords
     possibly overwrites the values. */
  window->width = width;
  window->height = height;
  window->forceReshape = True;

#if defined(WIN32)
  __glutAdjustCoords(parent ? parent->win : NULL, &x, &y, &width, &height);
  window->win = XCreateWindow(__glutDisplay,
    parent == NULL ? __glutRoot : parent->win,
    x, y, width, height, 0,
    0, InputOutput, 0,
    attribMask, &wa);
  window->hdc = GetDC(window->win);
  /* Must set the XHDC for fake glXChooseVisual & fake
     glXCreateContext & fake XAllocColorCells. */
  XHDC = window->hdc;
  window->vis = __glutDetermineWindowVisual(&window->treatAsSingle,
    &window->visAlloced);
  if (!window->vis) {
    __glutFatalError(
      "visual with necessary capabilities not found.");
  }
  if (!SetPixelFormat(window->hdc,
      ChoosePixelFormat(window->hdc, window->vis),
      window->vis))
    __glutFatalError("SetPixelFormat() failed in glutCreateWindow().");
  __glutSetupColormap(window->vis, &window->colormap, &window->cmap);
  /* Make sure subwindows get a windowStatus callback. */
  if (parent)
    PostMessage(parent->win, WM_ACTIVATE, 0, 0);
#else
  window->win = XCreateWindow(__glutDisplay,
    parent == NULL ? __glutRoot : parent->win,
    x, y, width, height, 0,
    window->vis->depth, InputOutput, window->vis->visual,
    attribMask, &wa);
#endif
  window->renderWin = window->win;
  window->ctx = glXCreateContext(__glutDisplay, window->vis,
    None, __glutTryDirect);
  if (!window->ctx) {
    __glutFatalError(
      "failed to create OpenGL rendering context.");
  }
  window->renderCtx = window->ctx;
#if !defined(WIN32)
  window->isDirect = glXIsDirect(__glutDisplay, window->ctx);
  if (__glutForceDirect) {
    if (!window->isDirect)
      __glutFatalError("direct rendering not possible.");
  }
#endif

  window->parent = parent;
  if (parent) {
    window->siblings = parent->children;
    parent->children = window;
  } else {
    window->siblings = NULL;
  }
  window->overlay = NULL;
  window->children = NULL;
  window->display = __glutDefaultDisplay;
  window->reshape = __glutDefaultReshape;
  window->mouse = NULL;
  window->motion = NULL;
  window->windowStatus = NULL;
  window->visibility = NULL;
  window->passive = NULL;
  window->entry = NULL;
  window->special = NULL;
  window->buttonBox = NULL;
  window->dials = NULL;
  window->spaceMotion = NULL;
  window->spaceRotate = NULL;
  window->spaceButton = NULL;
  window->tabletMotion = NULL;
  window->tabletButton = NULL;
  window->tabletPos[0] = -1;
  window->tabletPos[1] = -1;
  window->keyboard = NULL;
  window->shownState = 0;
  window->visState = -1;  /* not VisibilityUnobscured,
                             VisibilityPartiallyObscured, or
                             VisibilityFullyObscured */
  window->entryState = -1;  /* not EnterNotify or LeaveNotify */
  window->workMask = GLUT_MAP_WORK;
  window->desiredMapState = NormalState;
  window->desiredConfMask = 0;
  window->buttonUses = 0;
  window->cursor = GLUT_CURSOR_INHERIT;
  window->prevWorkWin = __glutWindowWorkList;
  __glutWindowWorkList = window;
  for (i = 0; i < GLUT_MAX_MENUS; i++) {
    window->menu[i] = 0;
  }
  __glutWindowList[winnum] = window;
  __glutSetWindow(window);

  __glutDetermineMesaSwapHackSupport();

  if (window->treatAsSingle) {
    /* We do this because either the window really is single
       buffered (in which case this is redundant, but harmless,
       because this is the initial single-buffered context
       state); or we are treating a double buffered window as a
       single-buffered window because the system does not appear
       to export any suitable single- buffered visuals (in which
       the following are necessary). */
    glDrawBuffer(GL_FRONT);
    glReadBuffer(GL_FRONT);
  }
  return window;
}