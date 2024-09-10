CBUF *cbuf_init(int buffer_size, char *name) {
	if (!buffer_size)
		return 0;
	CBUF *b = calloc(1, sizeof(CBUF));
	if (!b)
		return NULL;
	if (pthread_mutex_init(&b->lock, NULL) != 0) {
		perror("cbuf_new: mutex_init");
		free(b);
		return NULL;
	}
	b->name     = strdup(name);
	b->size     = buffer_size;
	b->pos      = 0;
	b->writepos = 0;
	b->buffer   = calloc(1, buffer_size);
	if (!b->buffer) {
		LOGf("CBUF  [%10s]: Can't allocate buffer size: %d\n", name, buffer_size);
		free(b);
		return NULL;
	}
	return b;
}