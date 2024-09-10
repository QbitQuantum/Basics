void video_refresh_timer(void *userdata) {

  VideoState *is = (VideoState *)userdata;
  VideoPicture *vp;
  double actual_delay, delay, sync_threshold, ref_clock, diff;

  if(is->video_st) {
    if(is->pictq_size == 0) {
      schedule_refresh(is, 1);
    } else {
      vp = &is->pictq[is->pictq_rindex];

      is->video_current_pts = vp->pts;
      is->video_current_pts_time = av_gettime();

      delay = vp->pts - is->frame_last_pts; /* the pts from last time */
      if(delay <= 0 || delay >= 1.0) {
	/* if incorrect delay, use previous one */
	delay = is->frame_last_delay;
      }
      /* save for next time */
      is->frame_last_delay = delay;
      is->frame_last_pts = vp->pts;

      /* update delay to sync to audio if not master source */
      if(is->av_sync_type != AV_SYNC_VIDEO_MASTER) {
	ref_clock = get_master_clock(is);
	diff = vp->pts - ref_clock;

	/* Skip or repeat the frame. Take delay into account
	   FFPlay still doesn't "know if this is the best guess." */
	sync_threshold = (delay > AV_SYNC_THRESHOLD) ? delay : AV_SYNC_THRESHOLD;
	if(fabs(diff) < AV_NOSYNC_THRESHOLD) {
	  if(diff <= -sync_threshold) {
	    delay = 0;
	  } else if(diff >= sync_threshold) {
	    delay = 2 * delay;
	  }
	}
      }

      is->frame_timer += delay;
      /* computer the REAL delay */
      actual_delay = is->frame_timer - (av_gettime() / 1000000.0);
      if(actual_delay < 0.010) {
	/* Really it should skip the picture instead */
	actual_delay = 0.010;
      }
      schedule_refresh(is, (int)(actual_delay * 1000 + 0.5));

      /* show the picture! */
      video_display(is);

      /* update queue for next picture! */
      if(++is->pictq_rindex == VIDEO_PICTURE_QUEUE_SIZE) {
	is->pictq_rindex = 0;
      }
      pthread_mutex_lock(is->pictq_mutex);
      is->pictq_size--;
      pthread_cond_signal(is->pictq_cond);
      pthread_mutex_unlock(is->pictq_mutex);
    }
  } else {
    schedule_refresh(is, 100);
  }
}