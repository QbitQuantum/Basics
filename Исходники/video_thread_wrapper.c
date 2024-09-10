static bool thread_frame(void *data, const void *frame_,
      unsigned width, unsigned height, uint64_t frame_count,
      unsigned pitch, const char *msg)
{
   unsigned copy_stride;
   const uint8_t *src  = NULL;
   uint8_t *dst        = NULL;
   thread_video_t *thr = (thread_video_t*)data;

   /* If called from within read_viewport, we're actually in the 
    * driver thread, so just render directly. */
   if (thr->frame.within_thread)
   {
      thread_update_driver_state(thr);

      if (thr->driver && thr->driver->frame)
         return thr->driver->frame(thr->driver_data, frame_,
               width, height, frame_count, pitch, msg);
      return false;
   }

   RARCH_PERFORMANCE_INIT(thr_frame);
   RARCH_PERFORMANCE_START(thr_frame);

   copy_stride = width * (thr->info.rgb32 
         ? sizeof(uint32_t) : sizeof(uint16_t));

   src = (const uint8_t*)frame_;
   dst = thr->frame.buffer;

   slock_lock(thr->lock);

   if (!thr->nonblock)
   {
      settings_t *settings = config_get_ptr();

      retro_time_t target_frame_time = (retro_time_t)
         roundf(1000000 / settings->video.refresh_rate);
      retro_time_t target = thr->last_time + target_frame_time;

      /* Ideally, use absolute time, but that is only a good idea on POSIX. */
      while (thr->frame.updated)
      {
         retro_time_t current = rarch_get_time_usec();
         retro_time_t delta = target - current;

         if (delta <= 0)
            break;

         if (!scond_wait_timeout(thr->cond_cmd, thr->lock, delta))
            break;
      }
   }

   /* Drop frame if updated flag is still set, as thread is 
    * still working on last frame. */
   if (!thr->frame.updated)
   {
      if (src)
      {
         unsigned h;
         for (h = 0; h < height; h++, src += pitch, dst += copy_stride)
            memcpy(dst, src, copy_stride);
      }

      thr->frame.updated = true;
      thr->frame.width  = width;
      thr->frame.height = height;
      thr->frame.count  = frame_count;
      thr->frame.pitch  = copy_stride;

      if (msg)
         strlcpy(thr->frame.msg, msg, sizeof(thr->frame.msg));
      else
         *thr->frame.msg = '\0';

      scond_signal(thr->cond_thread);

#if defined(HAVE_MENU)
      if (thr->texture.enable)
      {
         while (thr->frame.updated)
            scond_wait(thr->cond_cmd, thr->lock);
      }
#endif
      thr->hit_count++;
   }
   else
      thr->miss_count++;

   slock_unlock(thr->lock);

   RARCH_PERFORMANCE_STOP(thr_frame);

   thr->last_time = rarch_get_time_usec();
   return true;
}