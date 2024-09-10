/* initialize controller */
struct nvstusb_context *
nvstusb_init(char const * fw) 
{
  /* initialize usb */
  if (!nvstusb_usb_init()) return 0;

  /* open device */
  struct nvstusb_usb_device *dev = nvstusb_usb_open_device(fw? fw : "nvstusb.fw");
  if (0 == dev) return 0;

  /* allocate context */
  struct nvstusb_context *ctx = malloc(sizeof(*ctx));
  if (0 == ctx) {
    fprintf(stderr, "nvstusb: Could not allocate %d bytes for nvstusb_context...\n", (int)sizeof(*ctx));
    nvstusb_usb_close_device(dev);
    nvstusb_usb_deinit();
    return 0;
  }
  ctx->rate = 0.0;
  ctx->eye = 0;
  ctx->device = dev;
  ctx->vblank_method = 0;
  ctx->toggled3D = 0;
  ctx->invert_eyes = 0;
  ctx->b_thread_running = 0;


  /* Vblank init */
  /* NVIDIA VBlank syncing environment variable defined, signal it and disable
   * any attempt to application side method */
  if (getenv ("__GL_SYNC_TO_VBLANK"))
  {
    fprintf (stderr, "__GL_SYNC_TO_VBLANK defined in environment\n");
    ctx->vblank_method = 2;
    goto out_err;
  }

  /* Swap interval */
  glXSwapIntervalSGI = (PFNGLXSWAPINTERVALSGIPROC)glXGetProcAddress("glXSwapIntervalSGI");

  if (NULL != glXSwapIntervalSGI) {
    fprintf(stderr, "nvstusb: forcing vsync\n");
    ctx->vblank_method = 3;
  }

  /* Sync Video */
  glXGetVideoSyncSGI = (PFNGLXGETVIDEOSYNCSGIPROC)glXGetProcAddress("glXGetVideoSyncSGI");
  glXWaitVideoSyncSGI = (PFNGLXWAITVIDEOSYNCSGIPROC)glXGetProcAddress("glXWaitVideoSyncSGI");
  if (NULL == glXWaitVideoSyncSGI) {
    glXGetVideoSyncSGI = 0;
  } else {
    ctx->vblank_method = 1;
  }

  if (NULL != glXGetVideoSyncSGI ) {
    fprintf(stderr, "nvstusb: GLX_SGI_video_sync supported!\n");
  }

  fprintf(stderr, "nvstusb:selected vblank method: %d\n", ctx->vblank_method);
out_err:
  return ctx;
}