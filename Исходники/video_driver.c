void init_video(void)
{
   unsigned max_dim, scale, width, height;
   video_viewport_t *custom_vp      = NULL;
   const input_driver_t *tmp        = NULL;
   const struct retro_game_geometry *geom = NULL;
   video_info_t video               = {0};
   static uint16_t dummy_pixels[32] = {0};
   driver_t *driver                 = driver_get_ptr();
   settings_t *settings             = config_get_ptr();
   rarch_system_info_t *system      = rarch_system_info_get_ptr();
   struct retro_system_av_info *av_info =
      video_viewport_get_system_av_info();

   init_video_filter(video_state.pix_fmt);
   event_command(EVENT_CMD_SHADER_DIR_INIT);

   if (av_info)
      geom      = (const struct retro_game_geometry*)&av_info->geometry;
   max_dim   = max(geom->max_width, geom->max_height);
   scale     = next_pow2(max_dim) / RARCH_SCALE_BASE;
   scale     = max(scale, 1);

   if (video_state.filter.filter)
      scale = video_state.filter.scale;

   /* Update core-dependent aspect ratio values. */
   video_viewport_set_square_pixel(geom->base_width, geom->base_height);
   video_viewport_set_core();
   video_viewport_set_config();

   /* Update CUSTOM viewport. */
   custom_vp = video_viewport_get_custom();

   if (settings->video.aspect_ratio_idx == ASPECT_RATIO_CUSTOM)
   {
      float default_aspect = aspectratio_lut[ASPECT_RATIO_CORE].value;
      aspectratio_lut[ASPECT_RATIO_CUSTOM].value =
         (custom_vp->width && custom_vp->height) ?
         (float)custom_vp->width / custom_vp->height : default_aspect;
   }

   video_driver_set_aspect_ratio_value(
      aspectratio_lut[settings->video.aspect_ratio_idx].value);

   if (settings->video.fullscreen)
   {
      width  = settings->video.fullscreen_x;
      height = settings->video.fullscreen_y;
   }
   else
   {
      if (settings->video.force_aspect)
      {
         /* Do rounding here to simplify integer scale correctness. */
         unsigned base_width =
            roundf(geom->base_height * video_driver_get_aspect_ratio());
         width  = roundf(base_width * settings->video.scale);
      }
      else
         width  = roundf(geom->base_width   * settings->video.scale);
      height = roundf(geom->base_height * settings->video.scale);
   }

   if (width && height)
      RARCH_LOG("Video @ %ux%u\n", width, height);
   else
      RARCH_LOG("Video @ fullscreen\n");

   driver->display_type  = RARCH_DISPLAY_NONE;
   driver->video_display = 0;
   driver->video_window  = 0;

   if (!init_video_pixel_converter(RARCH_SCALE_BASE * scale))
   {
      RARCH_ERR("Failed to initialize pixel converter.\n");
      rarch_fail(1, "init_video()");
   }

   video.width        = width;
   video.height       = height;
   video.fullscreen   = settings->video.fullscreen;
   video.vsync        = settings->video.vsync && !system->force_nonblock;
   video.force_aspect = settings->video.force_aspect;
#ifdef GEKKO
   video.viwidth      = settings->video.viwidth;
   video.vfilter      = settings->video.vfilter;
#endif
   video.smooth       = settings->video.smooth;
   video.input_scale  = scale;
   video.rgb32        = video_state.filter.filter ?
      video_state.filter.out_rgb32 :
      (video_state.pix_fmt == RETRO_PIXEL_FORMAT_XRGB8888);

   tmp = (const input_driver_t*)driver->input;
   /* Need to grab the "real" video driver interface on a reinit. */
   find_video_driver();

#ifdef HAVE_THREADS
   if (settings->video.threaded && !video_state.hw_render_callback.context_type)
   {
      /* Can't do hardware rendering with threaded driver currently. */
      RARCH_LOG("Starting threaded video driver ...\n");

      if (!rarch_threaded_video_init(&driver->video, &driver->video_data,
               &driver->input, &driver->input_data,
               driver->video, &video))
      {
         RARCH_ERR("Cannot open threaded video driver ... Exiting ...\n");
         rarch_fail(1, "init_video()");
      }
   }
   else
#endif
      driver->video_data = driver->video->init(&video, &driver->input,
            &driver->input_data);

   if (!driver->video_data)
   {
      RARCH_ERR("Cannot open video driver ... Exiting ...\n");
      rarch_fail(1, "init_video()");
   }

   driver->video_poke = NULL;
   if (driver->video->poke_interface)
      driver->video->poke_interface(driver->video_data, &driver->video_poke);

   if (driver->video->viewport_info && (!custom_vp->width ||
            !custom_vp->height))
   {
      /* Force custom viewport to have sane parameters. */
      custom_vp->width = width;
      custom_vp->height = height;
      video_driver_viewport_info(custom_vp);
   }

   video_driver_set_rotation(
            (settings->video.rotation + system->rotation) % 4);

   video_driver_suppress_screensaver(settings->ui.suspend_screensaver_enable);

   if (!driver->input)
      init_video_input(tmp);

   event_command(EVENT_CMD_OVERLAY_DEINIT);
   event_command(EVENT_CMD_OVERLAY_INIT);

   video_driver_cached_frame_set(&dummy_pixels, 4, 4, 8);

#if defined(PSP)
   video_driver_set_texture_frame(&dummy_pixels, false, 1, 1, 1.0f);
#endif
}