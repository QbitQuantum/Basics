void GlTraceFilterModel::checkExtensions()
{
	const GLubyte *extensionString, *versionString;
	int supportedMajor, supportedMinor;

	QGLWidget w;

	w.makeCurrent();
	extensionString = glGetString(GL_EXTENSIONS);
	versionString = glGetString(GL_VERSION);
	supportedMajor = versionString[0] - '0';
	supportedMinor = versionString[2] - '0';

	QByteArray extensions = QByteArray(
			reinterpret_cast<const char*>(extensionString));

#ifdef GLSLDB_WIN
	PFNWGLGETEXTENSIONSSTRINGARBPROC wglGetExtensionsStringARB = 0;
	wglGetExtensionsStringARB = (PFNWGLGETEXTENSIONSSTRINGARBPROC)wglGetProcAddress("wglGetExtensionsStringARB");
	if(wglGetExtensionsStringARB) {
		extensions.append(' ');
		extensions.append(QByteArray(reinterpret_cast<const char*>(wglGetExtensionsStringARB(wglGetCurrentDC()))));
	}
#elif defined(GLSLDB_LINUX)
	int supportedXMajor, supportedXMinor;
	const char *versionXString;

	versionXString = glXQueryServerString(XOpenDisplay(NULL), 0, GLX_VERSION);

	supportedXMajor = versionXString[0] - '0';
	supportedXMinor = versionXString[2] - '0';

	extensions.append(' ');
	extensions.append(
			QByteArray(
					reinterpret_cast<const char*>(glXQueryServerString(
							XOpenDisplay(NULL), 0, GLX_EXTENSIONS))));

	extensions.append(' ');
	extensions.append(
			QByteArray(
					reinterpret_cast<const char*>(glXGetClientString(
							XOpenDisplay(NULL), GLX_EXTENSIONS))));

	extensions.append(' ');
	extensions.append(
			QByteArray(
					reinterpret_cast<const char*>(glXQueryExtensionsString(
							XOpenDisplay(NULL), 0))));
#elif defined(GLSLDB_OSX)

#warning "FIXME: any OSX specific extensions wee need to add here?"

#endif

	QList<QByteArray> extList = extensions.split(' ');
	for (int i = 0; i < this->rootItem->childCount(); i++) {
		GlTraceFilterItem *item = this->rootItem->child(i);
		if (strstr(item->function->extname, "GL_VERSION_")
				== item->function->extname) {
			int major, minor;
			major = item->function->extname[11] - '0';
			minor = item->function->extname[13] - '0';
			if (major < supportedMajor
					|| (major == supportedMajor && minor <= supportedMinor)) {
				item->isSupported = true;
			} else {
				item->isSupported = false;
			}
		}
#if defined(_WIN32)
		else if (strstr(item->function->extname, "WGL_VERSION_") == item->function->extname) {
			item->isSupported = true;
		}
#elif defined(GLSLDB_LINUX)
		else if (strstr(item->function->extname, "GLX_VERSION_")
				== item->function->extname) {
			int major, minor;
			major = item->function->extname[12] - '0';
			minor = item->function->extname[14] - '0';
			if (major < supportedXMajor
					|| (major == supportedXMajor && minor <= supportedXMinor)) {
				item->isSupported = true;
			} else {
				item->isSupported = false;
			}
		}
#elif defined(GLSLDB_OSX)
#warning "FIXME: any OSX specific extensions wee need to add here?"
#endif
		else {
			item->isSupported = extList.contains(item->function->extname);
		}
	}
}