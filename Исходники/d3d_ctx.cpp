static void gfx_ctx_d3d_update_title(void *data)
{
   char buf[128]        = {0};
   char buffer_fps[128] = {0};
   settings_t *settings = config_get_ptr();

   if (video_monitor_get_fps(buf, sizeof(buf),
            buffer_fps, sizeof(buffer_fps)))
   {
#ifndef _XBOX
      d3d_video_t *d3d     = (d3d_video_t*)data;

      SetWindowText(g_hwnd, buf);
#endif
   }

   if (settings->fps_show)
   {
#ifdef _XBOX
      MEMORYSTATUS stat;
      char mem[128] = {0};

      GlobalMemoryStatus(&stat);
      snprintf(mem, sizeof(mem), "|| MEM: %.2f/%.2fMB",
            stat.dwAvailPhys/(1024.0f*1024.0f), stat.dwTotalPhys/(1024.0f*1024.0f));
      strlcat(buffer_fps, mem, sizeof(buffer_fps));
#endif
      rarch_main_msg_queue_push(buffer_fps, 1, 1, false);
   }
}