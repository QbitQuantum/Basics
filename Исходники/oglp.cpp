bool Init (GetProcAddressCallback callback)
{
    std::vector <std::string> needed_extensions = {
            "GL_ARB_separate_shader_objects",
            "GL_ARB_sampler_objects",
            "GL_ARB_direct_state_access"
    };
    std::stringstream version;
    int major, minor;

#ifdef _WIN32
	internal::_opengl32dllhandle = LoadLibrary ("OPENGL32.DLL");
	internal::_usergetprocaddress = callback;
	InitPrototypes (internal::_getprocaddress);
#else
    InitPrototypes (callback);
#endif
    if (!GetString || GetString == (PFNGLGETSTRINGPROC) oglp::Unsupported) {
#ifdef OGLP_THROW_EXCEPTIONS
		throw std::runtime_error ("No entry point for glGetString found.");
#else
        return false;
#endif
    }

    version << GetString (GL_VERSION);
    CheckError ();
    version >> major;
    version.ignore (1);
    version >> minor;

    if (major < 3) {
#ifdef OGLP_THROW_EXCEPTIONS
		throw std::runtime_error ("OpenGL version 3.0 or higher is required.");
#else
        return false;
#endif
    }
    for (std::string &extension : needed_extensions) {
        if (!IsExtensionSupported (extension)) {
#ifdef OGLP_THROW_EXCEPTIONS
			throw std::runtime_error (extension + " is required.");
#else
            return false;
#endif
        }
    }
    return true;
}