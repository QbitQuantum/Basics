SdlLibrary::SdlLibrary(ApplicationSettings const &settings)
	: requested_(settings)
{
	SDL_ClearError();
	CheckSdlRun(SDL_Init(SDL_INIT_VIDEO) == 0);
	CheckSdlRun(SDL_GL_SetAttribute(SDL_GL_RED_SIZE, requested_.red) == 0);
	CheckSdlRun(SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, requested_.green) == 0);
	CheckSdlRun(SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, requested_.blue) == 0);
	CheckSdlRun(SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, requested_.alpha) == 0);
	int db = requested_.doubleBuffered ? 1 : 0;
	CheckSdlRun(SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, db) == 0);
	CheckSdlRun(SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, requested_.major) == 0);
	CheckSdlRun(SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, requested_.minor) == 0);
	window_ = SDL_CreateWindow(requested_.title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
							   requested_.width, requested_.height, requested_.fullScreen ? SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN : SDL_WINDOW_OPENGL);
	CheckSdlRun(window_ != NULL);
	context_ = SDL_GL_CreateContext(window_);
	CheckSdlRun(context_ != NULL);
	int vs = requested_.verticalSync ? 1 : 0;
	CheckSdlRun(SDL_GL_SetSwapInterval(vs) == 0);
	actual_ = requested_;
	int x;
	CheckSdlRun(SDL_GL_GetAttribute(SDL_GL_RED_SIZE, &x) == 0); actual_.red = IntToUint(x);
	CheckSdlRun(SDL_GL_GetAttribute(SDL_GL_GREEN_SIZE, &x) == 0);  actual_.green = IntToUint(x);
	CheckSdlRun(SDL_GL_GetAttribute(SDL_GL_BLUE_SIZE, &x) == 0); actual_.blue = IntToUint(x);
	CheckSdlRun(SDL_GL_GetAttribute(SDL_GL_ALPHA_SIZE, &x) == 0); actual_.alpha = IntToUint(x);
	CheckSdlRun(SDL_GL_GetAttribute(SDL_GL_DOUBLEBUFFER, &x) == 0); actual_.doubleBuffered = (x == 1);
	CheckSdlRun(SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &x) == 0); actual_.major = IntToUint(x);
	CheckSdlRun(SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &x) == 0); actual_.minor = IntToUint(x);
}