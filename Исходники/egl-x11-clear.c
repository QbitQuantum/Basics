static struct window *window_create(struct display *display, const char *name,
				    unsigned int x, unsigned int y,
				    unsigned int width, unsigned int height)
{
	static const EGLint attribs[] = {
		EGL_RED_SIZE, 1,
		EGL_GREEN_SIZE, 1,
		EGL_BLUE_SIZE, 1,
		EGL_DEPTH_SIZE, 1,
		EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
		EGL_NONE
	};
	static const EGLint attrs[] = {
		EGL_CONTEXT_CLIENT_VERSION, 2,
		EGL_NONE
	};
	XSetWindowAttributes attr;
	struct window *window;
	unsigned long mask;
	XVisualInfo visual;
	EGLint num_configs;
	XVisualInfo *info;
	XSizeHints hints;
	EGLConfig config;
	int num_visuals;
	EGLint version;
	Window root;
	int screen;
	EGLint vid;

	window = calloc(1, sizeof(*window));
	if (!window)
		return NULL;

	window->display = display;

	screen = DefaultScreen(display->x11);
	root = RootWindow(display->x11, screen);

	if (!eglChooseConfig(display->egl, attribs, &config, 1, &num_configs)) {
		free(window);
		return NULL;
	}

	if (!eglGetConfigAttrib(display->egl, config, EGL_NATIVE_VISUAL_ID, &vid)) {
		free(window);
		return NULL;
	}

	visual.visualid = vid;

	info = XGetVisualInfo(display->x11, VisualIDMask, &visual, &num_visuals);
	if (!info) {
		free(window);
		return NULL;
	}

	memset(&attr, 0, sizeof(attr));
	attr.background_pixel = 0;
	attr.border_pixel = 0;
	attr.colormap = XCreateColormap(display->x11, root, info->visual, AllocNone);
	attr.event_mask = StructureNotifyMask | ExposureMask | KeyPressMask;
	mask = CWBackPixel | CWBorderPixel | CWColormap | CWEventMask;

	window->x11 = XCreateWindow(display->x11, root, 0, 0, width, height,
				    0, info->depth, InputOutput, info->visual,
				    mask, &attr);
	if (!window->x11) {
		free(window);
		return NULL;
	}

	memset(&hints, 0, sizeof(hints));
	hints.x = x;
	hints.y = y;
	hints.width = width;
	hints.height = height;
	hints.flags = USSize | USPosition;

	XSetNormalHints(display->x11, window->x11, &hints);
	XSetStandardProperties(display->x11, window->x11, name, name, None,
			       NULL, 0, &hints);

	eglBindAPI(EGL_OPENGL_ES_API);

	window->context = eglCreateContext(display->egl, config,
					   EGL_NO_CONTEXT, attrs);
	if (window->context == EGL_NO_CONTEXT) {
		free(window);
		return NULL;
	}

	eglQueryContext(display->egl, window->context, EGL_CONTEXT_CLIENT_VERSION, &version);
	printf("OpenGL ES: %d\n", version);

	window->surface = eglCreateWindowSurface(display->egl, config,
						 window->x11, NULL);
	if (window->surface == EGL_NO_SURFACE) {
		free(window);
		return NULL;
	}

	XFree(info);

	window->width = width;
	window->height = height;

	return window;
}