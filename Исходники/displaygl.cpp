void VDVideoDisplayMinidriverOpenGL::SetFilterMode(FilterMode mode) {
	if (mPreferredFilter == mode)
		return;

	mPreferredFilter = mode;

	if (mhwndOGL) {
		if (HDC hdc = GetDC(mhwndOGL)) {
			if (mGL.Begin(hdc)) {
				mTexPattern[0].ReinitFiltering(&mGL, mode);
				mTexPattern[1].ReinitFiltering(&mGL, mode);
				mGL.wglMakeCurrent(NULL, NULL);
			}
		}
	}
}