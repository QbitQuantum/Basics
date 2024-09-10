int mqueue_close(mqueue_t * self, char *path)
{
	assert(self != NULL);

	if (path != NULL) {
		char *endp = NULL;
		(void)strtol(path + 1, &endp, 10);

		if (strncmp(endp, "->", 2) == 0) {
			if (self->in != (mqd_t) - 1)
				mq_close(self->in), self->in = (mqd_t) - 1;
		} else if (strncmp(endp, "<-", 2) == 0) {
			if (self->out != (mqd_t) - 1)
				mq_close(self->out), self->out = (mqd_t) - 1;
		} else {
			UNEXPECTED("'%s' invalid service", path);
			return -1;
		}
	}

	return 0;
}