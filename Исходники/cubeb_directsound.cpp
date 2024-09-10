/*static*/ int
directsound_init(cubeb ** context, char const * context_name)
{
  cubeb * ctx;

  *context = NULL;

  ctx = (cubeb *) calloc(1, sizeof(*ctx));

  ctx->ops = &directsound_ops;

  /* register a hidden window for DirectSound's SetCooperativeLevel */
  WNDCLASSEX wc;
  wc.cbSize        = sizeof(WNDCLASSEX);
  wc.style         = 0;
  wc.lpfnWndProc   = hidden_window_callback;
  wc.cbClsExtra    = 0;
  wc.cbWndExtra    = 0;
  wc.hInstance     = NULL;
  wc.hIcon         = NULL;
  wc.hCursor       = NULL;
  wc.hbrBackground = (HBRUSH) COLOR_WINDOW + 1;
  wc.lpszMenuName  = NULL;
  wc.lpszClassName = hidden_window_class_name;
  wc.hIconSm       = NULL;

  /* ignore the result as registration failure will show up when the
     window is created and this way there is no need for global
     tracking of whether the window class has been registered */
  RegisterClassEx(&wc);

  ctx->hidden_window = CreateWindowEx(WS_EX_NOACTIVATE | WS_EX_NOPARENTNOTIFY,
				      hidden_window_class_name, NULL, WS_DISABLED,
				      0, 0, 0, 0, HWND_MESSAGE, NULL, NULL, NULL);
  if (!ctx->hidden_window) {
    directsound_destroy(ctx);
    return CUBEB_ERROR;
  }

  if (FAILED(DirectSoundCreate(NULL, &ctx->dsound, NULL))) {
    directsound_destroy(ctx);
    return CUBEB_ERROR;
  }
  assert(ctx->dsound);

  if (FAILED(ctx->dsound->SetCooperativeLevel(ctx->hidden_window, DSSCL_PRIORITY))) {
    directsound_destroy(ctx);
    return CUBEB_ERROR;
  }

  InitializeCriticalSection(&ctx->lock);

  ctx->streams_event = CreateEvent(NULL, FALSE, FALSE, NULL);
  if (!ctx->streams_event) {
    directsound_destroy(ctx);
    return CUBEB_ERROR;
  }

  uintptr_t thread = _beginthreadex(NULL, 64 * 1024,
				    cubeb_buffer_refill_thread, ctx, 0, NULL);
  if (!thread) {
    directsound_destroy(ctx);
    return CUBEB_ERROR;
  }
  ctx->refill_thread = reinterpret_cast<HANDLE>(thread);

  SetThreadPriority(thread, THREAD_PRIORITY_TIME_CRITICAL);

  *context = ctx;

  return CUBEB_OK;
}