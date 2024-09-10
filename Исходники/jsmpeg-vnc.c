int main(int argc, char* argv[]) {
	if( argc < 2 ) {
		exit_usage(argv[0]);
	}

	int bit_rate = 0,
		fps = 60,
		port = 8080,
		width = 0,
		height = 0;

	// Parse command line options
	for( int i = 1; i < argc-1; i+=2 ) {
		if( strlen(argv[i]) < 2 || i >= argc-2 || argv[i][0] != '-' ) {
			exit_usage(argv[0]);
		}

		switch( argv[i][1] ) {
			case 'b': bit_rate = atoi(argv[i+1]) * 1000; break;
			case 'p': port = atoi(argv[i+1]); break;
			case 's': sscanf(argv[i+1], "%dx%d", &width, &height); break;
			case 'f': fps = atoi(argv[i+1]); break;
			default: exit_usage(argv[0]);
		}
	}

	// Find target window
	char *window_title = argv[argc-1];
	HWND window = NULL;
	if( strcmp(window_title, "desktop") == 0 ) {
		window = GetDesktopWindow();
	}
	else if( strcmp(window_title, "cursor") == 0 ) {
		POINT cursor;
		GetCursorPos(&cursor);
		window = WindowFromPoint(cursor);
	}
	else {
		window = window_with_prefix(window_title);
	}

	if( !window ) {
		printf("No window with title starting with \"%s\"\n", window_title);
		return 0;
	}

	// Start the app
	app_t *app = app_create(window, port, bit_rate, width, height);

	char real_window_title[56];
	GetWindowTextA(window, real_window_title, sizeof(real_window_title));
	printf(
		"Window 0x%08x: \"%s\"\n"
		"Window size: %dx%d, output size: %dx%d, bit rate: %d kb/s\n\n"
		"Server started on: http://%s:%d/\n\n",
		window, real_window_title,
		app->grabber->width, app->grabber->height,
		app->encoder->out_width, app->encoder->out_height,
		app->encoder->context->bit_rate / 1000,
		server_get_host_address(app->server), app->server->port
	);

	app_run(app, fps);

	app_destroy(app);	

	return 0;
}