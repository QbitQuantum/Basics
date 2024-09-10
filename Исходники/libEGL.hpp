	LibEGLexports *loadExports()
	{
		if(!libEGL)
		{
			#if defined(_WIN32)
				#if defined(__LP64__)
					const char *libEGL_lib[] = {"libEGL.dll", "lib64EGL_translator.dll"};
				#else
					const char *libEGL_lib[] = {"libEGL.dll", "libEGL_translator.dll"};
				#endif
			#elif defined(__ANDROID__)
				#if defined(__LP64__)
					const char *libEGL_lib[] = {"/vendor/lib64/egl/libEGL_swiftshader.so"};
				#else
					const char *libEGL_lib[] = {"/vendor/lib/egl/libEGL_swiftshader.so"};
				#endif
			#elif defined(__linux__)
				#if defined(__LP64__)
					const char *libEGL_lib[] = {"lib64EGL_translator.so", "libEGL.so.1", "libEGL.so"};
				#else
					const char *libEGL_lib[] = {"libEGL_translator.so", "libEGL.so.1", "libEGL.so"};
				#endif
			#elif defined(__APPLE__)
				#if defined(__LP64__)
					const char *libEGL_lib[] = {"lib64EGL_translator.dylib", "libEGL.so", "libEGL.dylib"};
				#else
					const char *libEGL_lib[] = {"libEGL_translator.dylib", "libEGL.so", "libEGL.dylib"};
				#endif
			#else
				#error "libEGL::loadExports unimplemented for this platform"
			#endif

			libEGL = loadLibrary(libEGL_lib, "libEGL_swiftshader");

			if(libEGL)
			{
				auto libEGL_swiftshader = (LibEGLexports *(*)())getProcAddress(libEGL, "libEGL_swiftshader");
				libEGLexports = libEGL_swiftshader();
			}
		}

		return libEGLexports;
	}