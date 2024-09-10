fz_stream *
fz_open_file_w(fz_context *ctx, const wchar_t *name)
{
	int fd = _wopen(name, O_BINARY | O_RDONLY, 0);
	if (fd == -1)
		fz_throw(ctx, FZ_ERROR_GENERIC, "cannot open file %ls", name);
	return fz_open_fd(ctx, fd);
}