static bool process_audio_delay(struct audio_monitor *monitor,
		float **data, uint32_t *frames, uint64_t ts, uint32_t pad)
{
	obs_source_t *s = monitor->source;
	uint64_t last_frame_ts = s->last_frame_ts;
	uint64_t cur_time = os_gettime_ns();
	uint64_t front_ts;
	uint64_t cur_ts;
	int64_t diff;
	uint32_t blocksize = monitor->channels * sizeof(float);

	/* cut off audio if long-since leftover audio in delay buffer */
	if (cur_time - monitor->last_recv_time > 1000000000)
		circlebuf_free(&monitor->delay_buffer);
	monitor->last_recv_time = cur_time;

	ts += monitor->source->sync_offset;

	circlebuf_push_back(&monitor->delay_buffer, &ts, sizeof(ts));
	circlebuf_push_back(&monitor->delay_buffer, frames, sizeof(*frames));
	circlebuf_push_back(&monitor->delay_buffer, *data,
			*frames * blocksize);

	if (!monitor->prev_video_ts) {
		monitor->prev_video_ts = last_frame_ts;

	} else if (monitor->prev_video_ts == last_frame_ts) {
		monitor->time_since_prev += (uint64_t)*frames *
			1000000000ULL / (uint64_t)monitor->sample_rate;
	} else {
		monitor->time_since_prev = 0;
	}

	while (monitor->delay_buffer.size != 0) {
		size_t size;
		bool bad_diff;

		circlebuf_peek_front(&monitor->delay_buffer, &cur_ts,
				sizeof(ts));
		front_ts = cur_ts -
			((uint64_t)pad * 1000000000ULL /
			 (uint64_t)monitor->sample_rate);
		diff = (int64_t)front_ts - (int64_t)last_frame_ts;
		bad_diff = !last_frame_ts ||
		           llabs(diff) > 5000000000 ||
		           monitor->time_since_prev > 100000000ULL;

		/* delay audio if rushing */
		if (!bad_diff && diff > 75000000) {
#ifdef DEBUG_AUDIO
			blog(LOG_INFO, "audio rushing, cutting audio, "
					"diff: %lld, delay buffer size: %lu, "
					"v: %llu: a: %llu",
					diff, (int)monitor->delay_buffer.size,
					last_frame_ts, front_ts);
#endif
			return false;
		}

		circlebuf_pop_front(&monitor->delay_buffer, NULL, sizeof(ts));
		circlebuf_pop_front(&monitor->delay_buffer, frames,
				sizeof(*frames));

		size = *frames * blocksize;
		da_resize(monitor->buf, size);
		circlebuf_pop_front(&monitor->delay_buffer,
				monitor->buf.array, size);

		/* cut audio if dragging */
		if (!bad_diff && diff < -75000000 && monitor->delay_buffer.size > 0) {
#ifdef DEBUG_AUDIO
			blog(LOG_INFO, "audio dragging, cutting audio, "
					"diff: %lld, delay buffer size: %lu, "
					"v: %llu: a: %llu",
					diff, (int)monitor->delay_buffer.size,
					last_frame_ts, front_ts);
#endif
			continue;
		}

		*data = monitor->buf.array;
		return true;
	}

	return false;
}