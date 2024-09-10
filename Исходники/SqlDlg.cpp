int  SqlError(const char *text, const char *error, const char *statement, bool retry) {
	return SqlError(HWND(NULL), text, error, statement, retry);
}