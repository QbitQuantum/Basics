internal long fill_ring_buf(struct audio_ring_buffer *audio_ring_buf,
			    struct game_memory *mem,
			    struct audio_buffer *audio_buf)
{
	unsigned int bytes_per_sample_all_chans,
	    bytes_to_write, region_1_bytes, region_2_bytes, sample_count, i,
	    buf_pos, starting_buf_pos, left_sample_value, right_sample_value;
	unsigned long sample_pos;

	if (!audio_buf->samples) {
		debug(0, "no audio_buf->samples\n");
		return -1;
	}

	bytes_per_sample_all_chans =
	    HANDMAIDEN_AUDIO_BYTES_PER_SAMPLE * HANDMAIDEN_AUDIO_CHANNELS;

	if ((audio_ring_buf->write_cursor - audio_ring_buf->play_cursor) >=
	    audio_ring_buf->buf_len) {
		debug(1, "fill: no room to write more sound data\n");
		return 0;
	}

	if (((audio_ring_buf->write_cursor % audio_ring_buf->buf_len) >
	     (audio_ring_buf->play_cursor % audio_ring_buf->buf_len))
	    || (audio_ring_buf->write_cursor == audio_ring_buf->play_cursor)) {
		bytes_to_write =
		    audio_ring_buf->buf_len - (audio_ring_buf->write_cursor -
					       audio_ring_buf->play_cursor);
	} else {
		bytes_to_write =
		    (audio_ring_buf->play_cursor % audio_ring_buf->buf_len) -
		    (audio_ring_buf->write_cursor % audio_ring_buf->buf_len);
	}

	if (bytes_to_write > audio_buf->buf_len) {
		debug(0, "bytes_to_write > audio_buf->buf_len (%u > %u)\n",
		      bytes_to_write, audio_buf->buf_len);
		bytes_to_write = audio_buf->buf_len;
	}

	debug(2, "bytes_to_write: %u\n", bytes_to_write);

	audio_buf->stream_pos =
	    (audio_ring_buf->write_cursor / bytes_per_sample_all_chans);
	audio_buf->num_samples = bytes_to_write / bytes_per_sample_all_chans;

	update_audio_buf(mem, audio_buf);

	if ((audio_ring_buf->play_cursor % audio_ring_buf->buf_len) >=
	    (audio_ring_buf->write_cursor % audio_ring_buf->buf_len)) {
		region_1_bytes = bytes_to_write;
		region_2_bytes = 0;
		if ((audio_ring_buf->play_cursor !=
		     audio_ring_buf->write_cursor)
		    && (region_1_bytes >
			((audio_ring_buf->play_cursor %
			  audio_ring_buf->buf_len) -
			 (audio_ring_buf->write_cursor %
			  audio_ring_buf->buf_len)))) {
			debug(0, "region 1 over-writing play_cursor\n");
			return -1;
		}
	} else {
		region_1_bytes =
		    min(bytes_to_write,
			(audio_ring_buf->buf_len -
			 ((audio_ring_buf->play_cursor %
			   audio_ring_buf->buf_len))));
		region_2_bytes = bytes_to_write - region_1_bytes;
		if (region_2_bytes >
		    ((audio_ring_buf->play_cursor % audio_ring_buf->buf_len))) {
			debug(0, "region 2 over-writing play_cursor\n");
			return -1;
		}
	}

	debug(1,
	      "fill: (in)  play_cursor: %u (%u) write_cursor: %u (%u) bytes to write: %u\n",
	      audio_ring_buf->play_cursor % audio_ring_buf->buf_len,
	      audio_ring_buf->play_cursor,
	      audio_ring_buf->write_cursor % audio_ring_buf->buf_len,
	      audio_ring_buf->write_cursor, bytes_to_write);

	debug(1, "fill: region_1_bytes: %u region_2_bytes: %u\n",
	      region_1_bytes, region_2_bytes);

	if (audio_ring_buf->write_cursor % HANDMAIDEN_AUDIO_BYTES_PER_SAMPLE) {
		debug(0, "fill: unexpected audio position\n");
	}

	buf_pos = audio_ring_buf->write_cursor % audio_ring_buf->buf_len;
	starting_buf_pos = buf_pos;
	sample_count = region_1_bytes / bytes_per_sample_all_chans;
	for (i = 0; i < sample_count; i++) {
		sample_pos = (i * 2);
		left_sample_value = *(audio_buf->samples + sample_pos);
		right_sample_value = *(audio_buf->samples + sample_pos + 1);

		*(int *)(((unsigned char *)audio_ring_buf->buf) + buf_pos) =
		    left_sample_value;
		buf_pos += HANDMAIDEN_AUDIO_BYTES_PER_SAMPLE;
		*(int *)(((unsigned char *)audio_ring_buf->buf) + buf_pos) =
		    right_sample_value;
		buf_pos += HANDMAIDEN_AUDIO_BYTES_PER_SAMPLE;
	}
	debug(1, "fill: region 1 wrote %u bytes (%u samples)\n",
	      (buf_pos - starting_buf_pos), sample_count);
	audio_ring_buf->write_cursor += (buf_pos - starting_buf_pos);
	debug(1, "fill: write cursor moved to %u (%u)\n",
	      audio_ring_buf->write_cursor,
	      audio_ring_buf->write_cursor % audio_ring_buf->buf_len);

	sample_count = region_2_bytes / bytes_per_sample_all_chans;
	buf_pos = 0;
	starting_buf_pos = buf_pos;
	for (i = 0; i < sample_count; i++) {
		sample_pos = (i * 2);
		left_sample_value = *(audio_buf->samples + sample_pos);
		right_sample_value = *(audio_buf->samples + sample_pos + 1);

		*(int *)(((unsigned char *)audio_ring_buf->buf) + buf_pos) =
		    left_sample_value;
		buf_pos += HANDMAIDEN_AUDIO_BYTES_PER_SAMPLE;
		*(int *)(((unsigned char *)audio_ring_buf->buf) + buf_pos) =
		    right_sample_value;
		buf_pos += HANDMAIDEN_AUDIO_BYTES_PER_SAMPLE;
	}
	debug(1, "fill: region 2 wrote %u bytes (%u samples)\n",
	      (buf_pos - starting_buf_pos), sample_count);
	audio_ring_buf->write_cursor += (buf_pos - starting_buf_pos);
	debug(1, "fill: write cursor moved to %u (%u)\n",
	      audio_ring_buf->write_cursor,
	      audio_ring_buf->write_cursor % audio_ring_buf->buf_len);
	debug(1,
	      "fill: (out) play_cursor: %u (%u) write_cursor: %u (%u) bytes avail: %u\n",
	      audio_ring_buf->play_cursor % audio_ring_buf->buf_len,
	      audio_ring_buf->play_cursor,
	      audio_ring_buf->write_cursor % audio_ring_buf->buf_len,
	      audio_ring_buf->write_cursor,
	      audio_ring_buf->write_cursor - audio_ring_buf->play_cursor);

	if ((audio_ring_buf->write_cursor - audio_ring_buf->play_cursor) >
	    audio_ring_buf->buf_len) {
		debug(0,
		      "write_cursor: %u, play_cursor: %u diff: %d, bufsize: %u\n",
		      audio_ring_buf->write_cursor, audio_ring_buf->play_cursor,
		      (audio_ring_buf->write_cursor -
		       audio_ring_buf->play_cursor), audio_ring_buf->buf_len);
		return -1;
	}
	debug(1, "fill: done.\n");
	return (long)(region_1_bytes + region_2_bytes);
}