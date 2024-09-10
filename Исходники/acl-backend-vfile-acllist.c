static int acl_backend_vfile_acllist_read(struct acl_backend_vfile *backend)
{
	struct acl_backend_vfile_acllist acllist;
	struct istream *input;
	struct stat st;
	const char *path, *line, *p;
	int fd, ret = 0;

	backend->acllist_last_check = ioloop_time;

	if (!acl_list_get_path(backend, &path)) {
		/* we're never going to build acllist for this namespace. */
		acllist_clear(backend, 0);
		return 0;
	}

	if (backend->acllist_mtime != 0) {
		/* see if the file's mtime has changed */
		if (stat(path, &st) < 0) {
			if (errno == ENOENT)
				backend->acllist_mtime = 0;
			else
				i_error("stat(%s) failed: %m", path);
			return -1;
		}
		if (st.st_mtime == backend->acllist_mtime)
			return 0;
	}

	fd = open(path, O_RDONLY);
	if (fd == -1) {
		if (errno == ENOENT) {
			backend->acllist_mtime = 0;
			return -1;
		}
		i_error("open(%s) failed: %m", path);
		return -1;
	}
	if (fstat(fd, &st) < 0) {
		i_error("fstat(%s) failed: %m", path);
		i_close_fd(&fd);
		return -1;
	}
	backend->acllist_mtime = st.st_mtime;
	acllist_clear(backend, st.st_size);

	input = i_stream_create_fd(fd, (size_t)-1, FALSE);
	while ((line = i_stream_read_next_line(input)) != NULL) {
		acllist.mtime = 0;
		for (p = line; *p >= '0' && *p <= '9'; p++)
			acllist.mtime = acllist.mtime * 10 + (*p - '0');

		if (p == line || *p != ' ' || p[1] == '\0') {
			i_error("Broken acllist file: %s", path);
			if (unlink(path) < 0 && errno != ENOENT)
				i_error("unlink(%s) failed: %m", path);
			i_close_fd(&fd);
			return -1;
		}
		acllist.name = p_strdup(backend->acllist_pool, p + 1);
		array_append(&backend->acllist, &acllist, 1);
	}
	if (input->stream_errno != 0)
		ret = -1;
	i_stream_destroy(&input);

	if (close(fd) < 0)
		i_error("close(%s) failed: %m", path);
	return ret;
}