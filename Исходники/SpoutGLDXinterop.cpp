// Utilities
//
// GLDXcompatible
//
bool spoutGLDXinterop::GLDXcompatible()
{
	//
	// ======= Hardware compatibility test =======
	//
	// Call LoadGLextensions for an initial hardware compatibilty check and
	// also load Glew for the Nvidia OpenGL/Directx interop extensions.
	// This will fail straight away for non Nvidia hardware but it needs
	// an additional check. It is possible that the extensions load OK, 
	// but that initialization will still fail. This occurs when wglDXOpenDeviceNV
	// fails. This has been noted on dual graphics machines with the NVIDIA Optimus driver.
	// "GLDXcompatible" tests for this by initializing directx and calling wglDXOpenDeviceNV
	// If OK and the debug flag has not been set all the parameters are available
	// Otherwise it is limited to memory share
	//
	HDC hdc = wglGetCurrentDC(); // OpenGl device context is needed
	if(!hdc) {
		// MessageBoxA(NULL, "Spout compatibility test\nCannot get GL device context", "OpenSpout", MB_OK);
		return false;
	}
	HWND hWnd = WindowFromDC(hdc); // can be null though
	if(!bExtensionsLoaded) bExtensionsLoaded = LoadGLextensions();
	if(bExtensionsLoaded) {
		// all OK and not debug memoryshare
		// try to set up directx and open the GL/DX interop
		if(OpenDirectX(hWnd, bUseDX9)) {
			// if it passes here all is well
			return true;
		}
	} // end hardware compatibility test
	return false;

} // end GLDXcompatible