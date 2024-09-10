/* unlink
 * The is the ANSI C file 
 * deletion method and is shared by the 'modern' */
int unlink(
	_In_ const char *path) {
	if (path == NULL) {
		_set_errno(EINVAL);
		return EOF;
	}
	return _fval(DeletePath(path, 0));
}