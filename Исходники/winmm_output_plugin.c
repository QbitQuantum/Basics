static size_t
winmm_output_play(struct audio_output *ao, const void *chunk, size_t size, GError **error_r)
{
	struct winmm_output *wo = (struct winmm_output *)ao;

	/* get the next buffer from the ring and prepare it */
	struct winmm_buffer *buffer = &wo->buffers[wo->next_buffer];
	if (!winmm_drain_buffer(wo, buffer, error_r) ||
	    !winmm_set_buffer(wo, buffer, chunk, size, error_r))
		return 0;

	/* enqueue the buffer */
	MMRESULT result = waveOutWrite(wo->handle, &buffer->hdr,
				       sizeof(buffer->hdr));
	if (result != MMSYSERR_NOERROR) {
		waveOutUnprepareHeader(wo->handle, &buffer->hdr,
				       sizeof(buffer->hdr));
		g_set_error(error_r, winmm_output_quark(), result,
			    "waveOutWrite() failed");
		return 0;
	}

	/* mark our buffer as "used" */
	wo->next_buffer = (wo->next_buffer + 1) %
		G_N_ELEMENTS(wo->buffers);

	return size;
}