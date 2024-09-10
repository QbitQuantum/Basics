void setupPythonEnv(const char* argv0Param)
{
    //Disable user sites as they could conflict with Natron bundled packages.
    //If this is set, Python won’t add the user site-packages directory to sys.path.
    //See https://www.python.org/dev/peps/pep-0370/
    ProcInfo::putenv_wrapper("PYTHONNOUSERSITE", "1");
    ++Py_NoUserSiteDirectory;

    //
    // set up paths, clear those that don't exist or are not valid
    //
    std::string binPath = ProcInfo::applicationDirPath(argv0Param);
    binPath = StrUtils::toNativeSeparators(binPath);
#ifdef __NATRON_WIN32__
    static std::string pythonHome = binPath + "\\.."; // must use static storage
    std::string pyPathZip = pythonHome + "\\lib\\python" NATRON_PY_VERSION_STRING_NO_DOT ".zip";
    std::string pyPath = pythonHome +  "\\lib\\python" NATRON_PY_VERSION_STRING;
    std::string pluginPath = binPath + "\\..\\Plugins";
#else
#  if defined(__NATRON_LINUX__)
    static std::string pythonHome = binPath + "/.."; // must use static storage
#  elif defined(__NATRON_OSX__)
    static std::string pythonHome = binPath+ "/../Frameworks/Python.framework/Versions/" NATRON_PY_VERSION_STRING; // must use static storage
#  else
#    error "unsupported platform"
#  endif
    std::string pyPathZip = pythonHome + "/lib/python" NATRON_PY_VERSION_STRING_NO_DOT ".zip";
    std::string pyPath = pythonHome + "/lib/python" NATRON_PY_VERSION_STRING;
    std::string pluginPath = binPath + "/../Plugins";
#endif
    if ( !fileExists( StrUtils::fromNativeSeparators(pyPathZip) ) ) {
#     if defined(NATRON_CONFIG_SNAPSHOT) || defined(DEBUG)
        printf( "\"%s\" does not exist, not added to PYTHONPATH\n", pyPathZip.c_str() );
#     endif
        pyPathZip.clear();
    }
    if ( !dirExists( StrUtils::fromNativeSeparators(pyPath) ) ) {
#     if defined(NATRON_CONFIG_SNAPSHOT) || defined(DEBUG)
        printf( "\"%s\" does not exist, not added to PYTHONPATH\n", pyPath.c_str() );
#     endif
        pyPath.clear();
    }
    if ( !dirExists( StrUtils::fromNativeSeparators(pluginPath) ) ) {
#     if defined(NATRON_CONFIG_SNAPSHOT) || defined(DEBUG)
        printf( "\"%s\" does not exist, not added to PYTHONPATH\n", pluginPath.c_str() );
#     endif
        pluginPath.clear();
    }
    // PYTHONHOME is really useful if there's a python inside it
    if ( pyPathZip.empty() && pyPath.empty() ) {
#     if defined(NATRON_CONFIG_SNAPSHOT) || defined(DEBUG)
        printf( "dir \"%s\" does not exist or does not contain lib/python*, not setting PYTHONHOME\n", pythonHome.c_str() );
#     endif
        pythonHome.clear();
    }

    /////////////////////////////////////////
    // Py_SetPythonHome
    /////////////////////////////////////////
    //
    // Must be done before Py_Initialize (see doc of Py_Initialize)
    //
    // The argument should point to a zero-terminated character string in static storage whose contents will not change for the duration of the program’s execution

    if ( !pythonHome.empty() ) {
#     if defined(NATRON_CONFIG_SNAPSHOT) || defined(DEBUG)
        printf( "Py_SetPythonHome(\"%s\")\n", pythonHome.c_str() );
#     endif
#     if PY_MAJOR_VERSION >= 3
        // Python 3
        static const std::wstring pythonHomeW = StrUtils::utf8_to_utf16(pythonHome); // must use static storage
        Py_SetPythonHome( const_cast<wchar_t*>( pythonHomeW.c_str() ) );
#     else
        // Python 2
        Py_SetPythonHome( const_cast<char*>( pythonHome.c_str() ) );
#     endif
    }


    /////////////////////////////////////////
    // PYTHONPATH and Py_SetPath
    /////////////////////////////////////////
    //
    // note: to check the python path of a python install, execute:
    // python -c 'import sys,pprint; pprint.pprint( sys.path )'
    //
    // to build the python27.zip, cd to lib/python2.7, and generate the pyo and the zip file using:
    //
    //  python -O -m compileall .
    //  zip -r ../python27.zip *.py* bsddb compiler ctypes curses distutils email encodings hotshot idlelib importlib json logging multiprocessing pydoc_data sqlite3 unittest wsgiref xml
    //
    std::string pythonPath = ProcInfo::getenv_wrapper("PYTHONPATH");
    //Add the Python distribution of Natron to the Python path

    std::vector<std::string> toPrepend;
    if ( !pyPathZip.empty() ) {
        toPrepend.push_back(pyPathZip);
    }
    if ( !pyPath.empty() ) {
        toPrepend.push_back(pyPath);
    }
    if ( !pluginPath.empty() ) {
        toPrepend.push_back(pluginPath);
    }

#if defined(__NATRON_OSX__) && defined DEBUG
    // in debug mode, also prepend the local PySide directory
    // homebrew's pyside directory
    toPrepend.push_back("/usr/local/Cellar/pyside/1.2.2_1/lib/python" NATRON_PY_VERSION_STRING "/site-packages");
    // macport's pyside directory
    toPrepend.push_back("/opt/local/Library/Frameworks/Python.framework/Versions/" NATRON_PY_VERSION_STRING "/lib/python" NATRON_PY_VERSION_STRING "/site-packages");
#endif

    if ( toPrepend.empty() ) {
#     if defined(NATRON_CONFIG_SNAPSHOT) || defined(DEBUG)
        printf("PYTHONPATH not modified\n");
#     endif
    } else {
#     ifdef __NATRON_WIN32__
        const char pathSep = ';';
#     else
        const char pathSep = ':';
#     endif
        std::string toPrependStr = StrUtils::join(toPrepend, pathSep);
        if (pythonPath.empty()) {
            pythonPath = toPrependStr;
        } else {
            pythonPath = toPrependStr + pathSep + pythonPath;
        }
        // qputenv on minw will just call putenv, but we want to keep the utf16 info, so we need to call _wputenv
#     if 0//def __NATRON_WIN32__
        _wputenv_s(L"PYTHONPATH", StrUtils::utf8_to_utf16(pythonPath).c_str());
#     else
        ProcInfo::putenv_wrapper( "PYTHONPATH", pythonPath.c_str() );
        //Py_SetPath( pythonPathString.c_str() ); // does not exist in Python 2
#     endif
#     if PY_MAJOR_VERSION >= 3
        std::wstring pythonPathString = StrUtils::utf8_to_utf16(pythonPath);
        Py_SetPath( pythonPathString.c_str() ); // argument is copied internally, no need to use static storage
#     endif
#     if defined(NATRON_CONFIG_SNAPSHOT) || defined(DEBUG)
        printf( "PYTHONPATH set to %s\n", pythonPath.c_str() );
#     endif
    }

} // setupPythonEnv