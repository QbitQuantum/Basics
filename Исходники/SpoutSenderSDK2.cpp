DWORD SpoutSenderSDK2::DeInitGL()
{
	// OpenGL context required
	if(wglGetCurrentContext()) {
		if(bInitialized) sender.ReleaseSender();
	}
	bInitialized = false;

	return FF_SUCCESS;
}