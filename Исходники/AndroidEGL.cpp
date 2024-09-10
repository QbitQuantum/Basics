void AndroidEGL::Terminate()
{
	ResetDisplay();
	DestroyContext(PImplData->SharedContext.eglContext);
	PImplData->SharedContext.Reset();
	DestroyContext(PImplData->RenderingContext.eglContext);
	PImplData->RenderingContext.Reset();
	DestroyContext(PImplData->SingleThreadedContext.eglContext);
	PImplData->SingleThreadedContext.Reset();
	DestroySurface();
	TerminateEGL();
}