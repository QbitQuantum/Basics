static void xui_frame(void *data, video_frame_info_t *video_info)
{
   XUIMessage msg;
   XUIMessageRender msgRender;
   D3DXMATRIX matOrigView;
   const char *message   = NULL;
   D3DVIEWPORT9 vp_full  = {0};
   d3d9_video_t *d3d     = (d3d9_video_t*)video_driver_get_ptr(false);

   if (!d3d)
      return;

   xui_frame_count++;

   menu_display_set_viewport(video_info->width, video_info->height);

   app.RunFrame();
   XuiTimersRun();
   XuiRenderBegin( app.GetDC(), D3DCOLOR_ARGB( 255, 0, 0, 0 ) );

   XuiRenderGetViewTransform( app.GetDC(), &matOrigView );

   XuiMessageRender( &msg, &msgRender,
         app.GetDC(), 0xffffffff, XUI_BLEND_NORMAL );
   XuiSendMessage( app.GetRootObj(), &msg );

   XuiRenderSetViewTransform( app.GetDC(), &matOrigView );

#if 0
   /* TODO/FIXME - update this code */
   rarch_ctl(RARCH_CTL_MSG_QUEUE_PULL, &message);

   if (message)
      xui_render_message(message);
   else
   {
      rarch_ctl(RARCH_CTL_MSG_QUEUE_PULL, &message);

      if (message)
         xui_render_message(message);
   }
#endif

   XuiRenderEnd( app.GetDC() );

   menu_display_unset_viewport(video_info->width, video_info->height);
}