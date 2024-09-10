int main(void) {
	wchar_t buf[1024];
	_invalid_parameter_handler oldHandler, newHandler;
	newHandler = invalidParameterHandler;
	oldHandler = _set_invalid_parameter_handler(newHandler);
	// Disable the message box for assertions when linked with debug CRT library.
	_CrtSetReportMode(_CRT_ASSERT, 0);

	if (_setmode(_fileno(stdin), _O_U8TEXT) == -1) {
		perror("Cannot set stdin to UTF-8");
		exit(1);
	}
	if (_setmode(_fileno(stdout), _O_U16TEXT) == -1) {
		perror("Cannot set stdout to Unicode");
		exit(1);
	}
	while (_getws(buf)) {
		if (wcschr(buf, L'\xfffd')) {
			fprintf(stderr, "Error: Input stream not in UTF-8\n");
			exit(1);
		}
		_putws(buf);
	}
}