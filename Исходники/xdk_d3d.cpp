static void d3d_free(void *data)
{
   d3d_video_t *d3d = (d3d_video_t*)data;
   d3d_deinitialize(d3d);
#ifdef _XBOX
   if (d3d->ctx_driver && d3d->ctx_driver->destroy)
      d3d->ctx_driver->destroy(d3d);
   d3d->ctx_driver = NULL;
#endif
   if (d3d->dev)
      d3d->dev->Release();
   if (d3d->g_pD3D)
      d3d->g_pD3D->Release();

#ifdef HAVE_MONITOR
   Monitor::last_hm = MonitorFromWindow(d3d->hWnd, MONITOR_DEFAULTTONEAREST);
   DestroyWindow(d3d->hWnd);
#endif

   if (d3d)
      delete d3d;

#ifndef _XBOX
   UnregisterClass("RetroArch", GetModuleHandle(NULL));
#endif
}