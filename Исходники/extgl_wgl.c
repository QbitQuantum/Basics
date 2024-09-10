/** returns true if the extension is available */
static bool WGLQueryExtension(WGLExtensions *extensions, const char *name) {
	const GLubyte *extension_string;

	if (!extensions->WGL_ARB_extensions_string)
		if (!extensions->WGL_EXT_extensions_string)
			return false;
		else
			extension_string = (GLubyte*)extensions->wglGetExtensionsStringEXT();
	else
		extension_string = (GLubyte*)extensions->wglGetExtensionsStringARB(wglGetCurrentDC());
	return extgl_QueryExtension(extension_string, name);
}