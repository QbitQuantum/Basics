static void vita2d_gfx_update_viewport(vita_video_t* vita)
{
   int x                = 0;
   int y                = 0;
   float device_aspect  = ((float)PSP_FB_WIDTH) / PSP_FB_HEIGHT;
   float width          = PSP_FB_WIDTH;
   float height         = PSP_FB_HEIGHT;
   settings_t *settings = config_get_ptr();

   if (settings->video.scale_integer)
   {
      video_viewport_get_scaled_integer(&vita->vp, PSP_FB_WIDTH,
            PSP_FB_HEIGHT, video_driver_get_aspect_ratio(), vita->keep_aspect);
      width  = vita->vp.width;
      height = vita->vp.height;
   }
   else if (vita->keep_aspect)
   {
      float desired_aspect = video_driver_get_aspect_ratio();
      if (vita->rotation == ORIENTATION_VERTICAL ||
            vita->rotation == ORIENTATION_FLIPPED_ROTATED){
              device_aspect = 1.0 / device_aspect;
              width = PSP_FB_HEIGHT;
              height = PSP_FB_WIDTH;
            }
#if defined(HAVE_MENU)
      if (settings->video.aspect_ratio_idx == ASPECT_RATIO_CUSTOM)
      {
         struct video_viewport *custom = video_viewport_get_custom();

         if (custom)
         {
            x      = custom->x;
            y      = custom->y;
            width  = custom->width;
            height = custom->height;
         }
      }
      else
#endif
      {
         float delta;

         if ((fabsf(device_aspect - desired_aspect) < 0.0001f))
         {
            /* If the aspect ratios of screen and desired aspect
             * ratio are sufficiently equal (floating point stuff),
             * assume they are actually equal.
             */
         }
         else if (device_aspect > desired_aspect)
         {
            delta = (desired_aspect / device_aspect - 1.0f)
               / 2.0f + 0.5f;
            x     = (int)roundf(width * (0.5f - delta));
            width = (unsigned)roundf(2.0f * width * delta);
         }
         else
         {
            delta  = (device_aspect / desired_aspect - 1.0f)
               / 2.0f + 0.5f;
            y      = (int)roundf(height * (0.5f - delta));
            height = (unsigned)roundf(2.0f * height * delta);
         }

         if (vita->rotation == ORIENTATION_VERTICAL ||
               vita->rotation == ORIENTATION_FLIPPED_ROTATED){
                 x = (PSP_FB_WIDTH - width) * 0.5f;
                 y = (PSP_FB_HEIGHT - height) * 0.5f;
               }
      }

      vita->vp.x      = x;
      vita->vp.y      = y;
      vita->vp.width  = width;
      vita->vp.height = height;
   }
   else
   {
      vita->vp.x = vita->vp.y = 0;
      vita->vp.width = width;
      vita->vp.height = height;
   }

   vita->vp.width += vita->vp.width&0x1;
   vita->vp.height += vita->vp.height&0x1;

   vita->should_resize = false;

}