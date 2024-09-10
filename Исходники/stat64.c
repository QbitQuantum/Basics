int stat64(const char *path, struct stat64 *statp) {
	return _stat64(path, statp, 0);
}