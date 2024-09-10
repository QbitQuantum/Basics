void AndroidEGLGraphicsContext::Shutdown() {
	gl->ClearCurrent();
	gl->Shutdown();
	delete gl;
	ANativeWindow_release(wnd_);
}