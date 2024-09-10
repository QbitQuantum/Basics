void PlatformGLInfo::swapBuffers()
{
	wglSwapLayerBuffers( hdc_, WGL_SWAP_MAIN_PLANE );
}