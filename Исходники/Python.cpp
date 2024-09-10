bool CPython::init()
{
	//
	// Initialize the python environment
	//
	std::wstring path; int iRslt = 0; DWORD nrslt = 0;
	std::vector<wchar> vetbuf; wchar buffer[MAX_PATH+1] = {0};

	// First of all, get the python path from options .
	for (; GetOption(text("Python Path"), path); ) {
		nrslt = ::GetFullPathName (	// ...
			path.c_str(), _countof(buffer), buffer, nullptr
		);
		if (nrslt == 0) { path.clear(); break; }
		if (nrslt < _countof(buffer)) { path = buffer; break; }
		vetbuf.resize(nrslt+1);		// Allocate buffer ...
		nrslt = ::GetFullPathName (	// ...
			path.c_str(), vetbuf.size(), vetbuf.data(), nullptr
		);
		if (!nrslt || nrslt >= vetbuf.size()) path.clear();
		else path.assign(vetbuf.begin(), vetbuf.end()); break;
	}

	// Use the directory of the exe file if we fail to get python 
	// path from options.
	for (std::size_t pos = 0; path.length() <= 0; ) {
		nrslt = GetModuleFileName (	// Try the first time .......
			nullptr, buffer, _countof(buffer)
		);
		if (nrslt == 0) { path.clear(); break; }
		if (nrslt < _countof(buffer)) { path = buffer; 
			pos = path.find_last_not_of(text("\\/"));
			pos = path.find_last_of(text("\\/"),pos);
			path.replace( pos, -1, text("\\python"));
			break;
		}
		vetbuf.resize(nrslt*2);		// Allocate buffer ..........
		nrslt = GetModuleFileName (	// Try the second time ......
			nullptr, vetbuf.data(), vetbuf.size()
		);
		if (nrslt != 0 && nrslt <= vetbuf.size()) {
			path.assign(vetbuf.begin(), vetbuf.end());
			pos = path.find_last_not_of(text("\\/"));
			pos = path.find_last_of(text("\\/"),pos);
			path.replace( pos, -1, text("\\python"));
		} else path.clear(); break;
	}

	// Use current directory if we still can't get the python path .
	for (; path.length() <= 0; ) {
		nrslt = ::GetCurrentDirectory(_countof(buffer), buffer);
		if (nrslt == 0) { path.clear(); break; }
		if (nrslt < _countof(buffer)) { 
			path = buffer; path += text("\\python");
		}
		vetbuf.resize(nrslt+1);		// Allocate buffer ...
		nrslt = ::GetCurrentDirectory(vetbuf.size(),vetbuf.data());
		if (nrslt != 0 && nrslt <= vetbuf.size()) {
			path.assign(vetbuf.begin(), vetbuf.end());
			path.append(text("\\python"));
		} else path.clear(); break;
	}

	// We return false if we still can't get the python path ...
	if(path.length()<=0) return false; path.push_back(text('\\')); 

	// Now, We overwrite the environment variable PYTHONHOME..
	// It's not a necessuary operation ..
	::SetEnvironmentVariable(text("PYTHONHOME"), path.c_str());

	// Locate the python kernel file "pythonxx.dll" ..
	WIN32_FIND_DATA fData = {0}; HANDLE hFile = nullptr; 
	hFile = FindFirstFile((path+text("*.dll")).c_str(), &fData); 
	if (hFile != INVALID_HANDLE_VALUE) {
		do {
			if (fData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) 
				continue;		// We skip all directory .
			_wcslwr_s(fData.cFileName, _countof(fData.cFileName));
			if (wcsstr(fData.cFileName, text("python"))) break;
			else fData.cFileName[0] = text('\0');
		} while (FindNextFile(hFile, &fData));
		FindClose(hFile);		// Finish finding ..
	} else fData.cFileName[0] = text('\0');

	///
	// Now, initialize all python interface dynamically.
	// The reason we query python interface dynamically is to 
	// make sure our plugin can work without python ..
	///
	m_pyModule = ::GetModuleHandle(fData.cFileName);
	if (m_pyModule == nullptr) {
		m_pyModule = ::LoadLibrary((path+fData.cFileName).c_str());
		if (m_pyModule == nullptr) {
			m_pyModule = ::GetModuleHandle(text("python27.dll"));
			if (m_pyModule == nullptr) {
				m_pyModule = ::LoadLibrary(text("python27.dll"));
				if (m_pyModule == nullptr) return false;
			}
		}
	}

	if ( (Py_Finalize = reinterpret_cast<py_finalize>(
		::GetProcAddress(m_pyModule, "Py_Finalize")
	)) == nullptr ) return false;
	if ( (Py_Initialize = reinterpret_cast<py_initialize>(
		::GetProcAddress(m_pyModule, "Py_Initialize")
	)) == nullptr ) return false;
	if ( (Py_SetPythonHome = reinterpret_cast<py_setpythonhome>(
		::GetProcAddress(m_pyModule, "Py_SetPythonHome")
	)) == nullptr ) return false;
	if ( (Py_SetProgramName = reinterpret_cast<py_setprogramname>(
		::GetProcAddress(m_pyModule, "Py_SetProgramName")
	)) == nullptr ) return false;

	if ( (PyFile_AsFile = reinterpret_cast<pyfile_asfile>(
		::GetProcAddress(m_pyModule, "PyFile_AsFile")
	)) == nullptr ) return false;
	if ( (PyFile_FromFile = reinterpret_cast<pyfile_fromfile>(
		::GetProcAddress(m_pyModule, "PyFile_FromFile")
	)) == nullptr ) return false;
	if ( (PyFile_FromString = reinterpret_cast<pyfile_fromstring>(
		::GetProcAddress(m_pyModule, "PyFile_FromString")
	)) == nullptr ) return false;

	if ( (PyEval_InitThreads = reinterpret_cast<pyeval_initthreads>(
		::GetProcAddress(m_pyModule, "PyEval_InitThreads")
	)) == nullptr ) return false;

	if ( (PySys_SetArgv = reinterpret_cast<pysys_setargv>(
		::GetProcAddress(m_pyModule, "PySys_SetArgv")
	)) == nullptr ) return false;
	if ( (PySys_GetObject = reinterpret_cast<pysys_getobject>(
		::GetProcAddress(m_pyModule, "PySys_GetObject")
	)) == nullptr ) return false;
	if ( (PySys_SetObject = reinterpret_cast<pysys_setobject>(
		::GetProcAddress(m_pyModule, "PySys_SetObject")
	)) == nullptr ) return false;
	
	if ( (PyObject_SetAttrString = reinterpret_cast<pyobject_setattrstring>(
		::GetProcAddress(m_pyModule, "PyObject_SetAttrString")
	)) == nullptr ) return false;

	if ( (PyImport_ImportModule = reinterpret_cast<pyimport_importmodule>(
		::GetProcAddress(m_pyModule, "PyImport_ImportModule")
	)) == nullptr ) return false;
	if ( (PyImport_AddModule = reinterpret_cast<pyimport_addmodule>(
		::GetProcAddress(m_pyModule, "PyImport_AddModule")
	)) == nullptr ) return false;

	if ( (PyRun_SimpleString = reinterpret_cast<pyrun_simplestring>(
		::GetProcAddress(m_pyModule, "PyRun_SimpleString")
	)) == nullptr ) return false;
	if ( (PyRun_SimpleStringFlags = reinterpret_cast<pyrun_simplestringflags>(
		::GetProcAddress(m_pyModule, "PyRun_SimpleStringFlags")
	)) == nullptr ) return false;
	if ( (PyRun_SimpleFile = reinterpret_cast<pyrun_simplefile>(
		::GetProcAddress(m_pyModule, "PyRun_SimpleFile")
	)) == nullptr ) return false;
	/*if ( (PyRun_SimpleFileFlags = reinterpret_cast<pyrun_simplefileflags>(
		::GetProcAddress(m_pyModule, "PyRun_SimpleFileFlags")
	)) == nullptr ) return false;*/
	if ( (PyRun_SimpleFileEx = reinterpret_cast<pyrun_simplefileex>(
		::GetProcAddress(m_pyModule, "PyRun_SimpleFileEx")
	)) == nullptr ) return false;
	if ( (PyRun_SimpleFileExFlags = reinterpret_cast<pyrun_simplefileexflags>(
		::GetProcAddress(m_pyModule, "PyRun_SimpleFileExFlags")
	)) == nullptr ) return false;

	// Initialize the python environment, prepare the hooks
	//if (Py_SetPythonHome) Py_SetPythonHome(cvt.to_bytes(path).c_str());
	//if (Py_SetProgramName) Py_SetProgramName(cvt.to_bytes(buffer).c_str());
	if (Py_Initialize) Py_Initialize();
	if (PyEval_InitThreads) PyEval_InitThreads();
	// ...

	///
	// Now, initialize all MSVCR90 interface dynamically.
	///
	ACTCTX ctx = {sizeof(ACTCTX), 0}; ULONG_PTR actToken = 0;
	ctx.dwFlags = ACTCTX_FLAG_RESOURCE_NAME_VALID|ACTCTX_FLAG_HMODULE_VALID;
	ctx.hModule = m_pyModule; ctx.lpResourceName = MAKEINTRESOURCE(2);
	HANDLE hCtx = CreateActCtx(&ctx);
	if(hCtx != INVALID_HANDLE_VALUE) {
		if ( ActivateActCtx(hCtx, &actToken) ) {
			m_vcModule = ::GetModuleHandle(text("MSVCR90.dll"));
			if (m_vcModule == NULL) {
				m_vcModule = ::LoadLibrary(text("MSVCR90.dll"));
				if (m_vcModule == NULL) return false;
			}
			if ( (open_osfhandle = reinterpret_cast<__open_osfhandle>(
				::GetProcAddress(m_vcModule, "_open_osfhandle")
			)) == nullptr ) return false;
			if ( (setvbuf = reinterpret_cast<__setvbuf>(
				::GetProcAddress(m_vcModule, "setvbuf")
			)) == nullptr ) return false;
			if ( (fdopen = reinterpret_cast<__fdopen>(
				::GetProcAddress(m_vcModule, "_fdopen")
			)) == nullptr ) return false;
			if ( (fclose = reinterpret_cast<__fclose>(
				::GetProcAddress(m_vcModule, "fclose")
			)) == nullptr ) return false;
			// Deactive active context after finished ..
			DeactivateActCtx(0, actToken);
		}
		// Now close context ...
		ReleaseActCtx(hCtx); 
	}

	return true;	// All done, return true ...
}