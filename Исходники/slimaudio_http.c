void slimaudio_http_disconnect(slimaudio_t *audio) {
	pthread_mutex_lock(&audio->http_mutex);

	if (audio->http_state == STREAM_PLAYING)
	{
		DEBUGF("slimaudio_http_disconnect: state=%i\n", audio->http_state);

		audio->http_state = STREAM_STOP;

		/* closing socket and buffer will wake the http thread */
		CLOSESOCKET(audio->streamfd);
		slimaudio_buffer_close(audio->decoder_buffer);

		pthread_cond_broadcast(&audio->http_cond);

		while (audio->http_state == STREAM_STOP)
		{
			pthread_cond_wait(&audio->http_cond, &audio->http_mutex);
		}
	}

	pthread_mutex_unlock(&audio->http_mutex);
}