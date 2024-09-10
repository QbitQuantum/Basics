int MFDisplay_CreateDisplay(int width, int height, int bpp, int rate, bool vsync, bool triplebuffer, bool wide, bool progressive)
{
	MFCALLSTACK;

	FujiModule *pModule = (FujiModule*)pp::Module::Get();
	pNaClGLContext = new OpenGLContext(pModule->GetInstance());

	pNaClGLContext->MakeContextCurrent();

	gDisplay.fullscreenWidth = gDisplay.width = width;
	gDisplay.fullscreenHeight = gDisplay.height = height;
	gDisplay.refreshRate = rate;
	gDisplay.colourDepth = 32;
	gDisplay.windowed = true;
	gDisplay.wide = false;
	gDisplay.progressive = true;

	MFRenderer_CreateDisplay();

	initialised = true;

	return 0;
}