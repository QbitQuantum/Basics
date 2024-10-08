int
main (int argc, char **argv)
{

#ifdef WIN32
  HGLRC sdl_gl_context = 0;
  HDC sdl_dc = 0;
#else
  SDL_SysWMinfo info;
  Display *sdl_display = NULL;
  Window sdl_win = 0;
  GLXContext sdl_gl_context = NULL;
#endif

  GMainLoop *loop = NULL;
  GstPipeline *pipeline = NULL;
  GstBus *bus = NULL;
  GstElement *glfilter = NULL;
  GstElement *fakesink = NULL;
  GstState state;
  GAsyncQueue *queue_input_buf = NULL;
  GAsyncQueue *queue_output_buf = NULL;
  GstGLDisplay *display;
  GstGLContext *sdl_context;
  const gchar *platform;

  /* Initialize SDL for video output */
  if (SDL_Init (SDL_INIT_VIDEO) < 0) {
    fprintf (stderr, "Unable to initialize SDL: %s\n", SDL_GetError ());
    return -1;
  }

  /* Create a 640x480 OpenGL screen */
  if (SDL_SetVideoMode (640, 480, 0, SDL_OPENGL) == NULL) {
    fprintf (stderr, "Unable to create OpenGL screen: %s\n", SDL_GetError ());
    SDL_Quit ();
    return -1;
  }

  /* Set the title bar in environments that support it */
  SDL_WM_SetCaption ("SDL and gst-plugins-gl", NULL);


  /* Loop, drawing and checking events */
  InitGL (640, 480);

  gst_init (&argc, &argv);
  loop = g_main_loop_new (NULL, FALSE);

  /* retrieve and turn off sdl opengl context */
#ifdef WIN32
  sdl_gl_context = wglGetCurrentContext ();
  sdl_dc = wglGetCurrentDC ();
  wglMakeCurrent (0, 0);
  platform = "wgl";
  display = gst_gl_display_new ();
#else
  SDL_VERSION (&info.version);
  SDL_GetWMInfo (&info);
  /* FIXME: This display is different to the one that SDL uses to create the
   * GL context inside SDL_SetVideoMode() above which fails on Intel hardware
   */
  sdl_display = info.info.x11.display;
  sdl_win = info.info.x11.window;
  sdl_gl_context = glXGetCurrentContext ();
  glXMakeCurrent (sdl_display, None, 0);
  platform = "glx";
  display = (GstGLDisplay *) gst_gl_display_x11_new_with_display (sdl_display);
#endif

  sdl_context = gst_gl_context_new_wrapped (display, (guintptr) sdl_gl_context,
      gst_gl_platform_from_string (platform), GST_GL_API_OPENGL);

  pipeline =
      GST_PIPELINE (gst_parse_launch
      ("videotestsrc ! video/x-raw, width=320, height=240, framerate=(fraction)30/1 ! "
          "gleffects effect=5 ! fakesink sync=1", NULL));

  bus = gst_pipeline_get_bus (GST_PIPELINE (pipeline));
  gst_bus_add_signal_watch (bus);
  g_signal_connect (bus, "message::error", G_CALLBACK (end_stream_cb), loop);
  g_signal_connect (bus, "message::warning", G_CALLBACK (end_stream_cb), loop);
  g_signal_connect (bus, "message::eos", G_CALLBACK (end_stream_cb), loop);
  gst_object_unref (bus);

  /* sdl_gl_context is an external OpenGL context with which gst-plugins-gl want to share textures */
  glfilter = gst_bin_get_by_name (GST_BIN (pipeline), "gleffects0");
  g_object_set (G_OBJECT (glfilter), "other-context", sdl_context, NULL);
  gst_object_unref (glfilter);

  /* NULL to PAUSED state pipeline to make sure the gst opengl context is created and
   * shared with the sdl one */
  gst_element_set_state (GST_ELEMENT (pipeline), GST_STATE_PAUSED);
  state = GST_STATE_PAUSED;
  if (gst_element_get_state (GST_ELEMENT (pipeline), &state, NULL,
          GST_CLOCK_TIME_NONE) != GST_STATE_CHANGE_SUCCESS) {
    g_debug ("failed to pause pipeline\n");
    return -1;
  }

  /* turn on back sdl opengl context */
#ifdef WIN32
  wglMakeCurrent (sdl_dc, sdl_gl_context);
#else
  glXMakeCurrent (sdl_display, sdl_win, sdl_gl_context);
#endif

  /* append a gst-gl texture to this queue when you do not need it no more */
  fakesink = gst_bin_get_by_name (GST_BIN (pipeline), "fakesink0");
  g_object_set (G_OBJECT (fakesink), "signal-handoffs", TRUE, NULL);
  g_signal_connect (fakesink, "handoff", G_CALLBACK (on_gst_buffer), NULL);
  queue_input_buf = g_async_queue_new ();
  queue_output_buf = g_async_queue_new ();
  g_object_set_data (G_OBJECT (fakesink), "queue_input_buf", queue_input_buf);
  g_object_set_data (G_OBJECT (fakesink), "queue_output_buf", queue_output_buf);
  g_object_set_data (G_OBJECT (fakesink), "loop", loop);
  gst_object_unref (fakesink);

  gst_element_set_state (GST_ELEMENT (pipeline), GST_STATE_PLAYING);

  g_main_loop_run (loop);

  /* before to deinitialize the gst-gl-opengl context,
   * no shared context (here the sdl one) must be current
   */
#ifdef WIN32
  wglMakeCurrent (0, 0);
#else
  glXMakeCurrent (sdl_display, sdl_win, sdl_gl_context);
#endif

  gst_element_set_state (GST_ELEMENT (pipeline), GST_STATE_NULL);
  gst_object_unref (pipeline);

  /* turn on back sdl opengl context */
#ifdef WIN32
  wglMakeCurrent (sdl_dc, sdl_gl_context);
#else
  glXMakeCurrent (sdl_display, None, 0);
#endif

  SDL_Quit ();

  /* make sure there is no pending gst gl buffer in the communication queues 
   * between sdl and gst-gl
   */
  while (g_async_queue_length (queue_input_buf) > 0) {
    GstBuffer *buf = (GstBuffer *) g_async_queue_pop (queue_input_buf);
    gst_buffer_unref (buf);
  }

  while (g_async_queue_length (queue_output_buf) > 0) {
    GstBuffer *buf = (GstBuffer *) g_async_queue_pop (queue_output_buf);
    gst_buffer_unref (buf);
  }

  return 0;
}