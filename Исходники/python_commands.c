/*!
 * @brief Prepare the session for use, including all the resources that are embedded.
 */
VOID python_prepare_session()
{
	Py_IgnoreEnvironmentFlag = 1;
	Py_NoSiteFlag = 1;
	Py_Initialize();
	PyEval_InitThreads();

	PyObject* stdoutModule = Py_InitModule("meterpreter_stdout", meterpreter_stdout_hooks);

	if (stdoutModule != NULL && PySys_SetObject("stdout", stdoutModule) == 0)
	{
		dprintf("[PYTHON] Successfully set the stdout hook");
	}
	else
	{
		dprintf("[PYTHON] Failed to set the stdout hook");
	}

	PyObject* stderrModule = Py_InitModule("meterpreter_stderr", meterpreter_stderr_hooks);
	if (stderrModule != NULL && PySys_SetObject("stderr", stderrModule) == 0)
	{
		dprintf("[PYTHON] Successfully set the stderr hook");
	}
	else
	{
		dprintf("[PYTHON] Failed to set the stderr hook");
	}

	// with the output handlers sorted, we load the stuff from the compressed resource
	// which should give us all the stuff we need to be useful.
	initerrno();
	initnt();
	init_socket();
	init_functools();
	
	// have we loaded the core pointer already?
	if (coreLibPointer == NULL)
	{
		MEMORY_BASIC_INFORMATION mbi;
		if (!VirtualQuery((LPVOID)python_prepare_session, &mbi, sizeof(mbi)))
		{
			dprintf("[PYTHON] VirtualQuery failed: %d", GetLastError());
			return;
		}

		HMODULE mod = (HMODULE)mbi.AllocationBase;
		dprintf("[PYTHON] Module handle: %p", (LPVOID)mod);

		HRSRC res = FindResource(mod, MAKEINTRESOURCEA(IDR_PYTHON_CORE), "BINARY");
		if (res == NULL)
		{
			dprintf("[PYTHON] Unable to find resource: %d", GetLastError());
			return;
		}

		HGLOBAL file = LoadResource(mod, res);

		if (file == NULL)
		{
			dprintf("[PYTHON] Unable to load core library resource: %d", GetLastError());
			return;
		}

		// store these pointers for when we reset the session, saves us from
		// doing all of this nonsense again.
		coreLibPointer = (LPBYTE)LockResource(file);
		coreLibSize = *(LPDWORD)coreLibPointer;
		coreLibPointer += sizeof(DWORD);
	}

	dprintf("[PYTHON] coreLibPointer: %p, coreLibSize: %d", coreLibPointer, coreLibSize);

	if (coreLibPointer != NULL)
	{
		// Create a byte array with everything in it
		PyObject* libString = PyString_FromStringAndSize(coreLibPointer, coreLibSize);
		dprintf("[PYTHON] libString is %p", libString);

		// import zlib
		PyObject* zlibModStr = PyString_FromString("zlib");
		dprintf("[PYTHON] zlibModStr: %p", zlibModStr);
		PyObject* zlibMod = PyImport_Import(zlibModStr);
		dprintf("[PYTHON] zlibMod: %p", zlibMod);
		// get a reference to the decompress function
		PyObject* zlibDecompress = PyObject_GetAttrString(zlibMod, "decompress");
		dprintf("[PYTHON] zlibDecompress: %p", zlibDecompress);
		// prepare arguments for invocation
		PyObject* zlibDecompressArgs = PyTuple_Pack(1, libString);
		dprintf("[PYTHON] zlibDecompressArgs: %p", zlibDecompressArgs);
		// call zlib.decompress(libString)
		PyObject* zlibDecompressResult = PyObject_CallObject(zlibDecompress, zlibDecompressArgs);
		dprintf("[PYTHON] zlibDecompressResult: %p", zlibDecompressResult);
		//dprintf("[PYTHON] zlibDecompressResult type: %s", zlibDecompressResult->ob_type->tp_name);

		PCHAR byteArray = NULL;
		Py_ssize_t byteArrayLength = 0;
		PyString_AsStringAndSize(zlibDecompressResult, &byteArray, &byteArrayLength);
		dprintf("[PYTHON] bytes: %p %u", byteArray, byteArrayLength);

		PyObject* modData = PyMarshal_ReadObjectFromString(byteArray, byteArrayLength);
		dprintf("[PYTHON] modData: %p", modData);

		PyObject* mainMod = PyImport_AddModule("__main__");
		PyObject* mainDict = PyModule_GetDict(mainMod);
		PyModule_AddObject(mainMod, "met_lib_data", modData);
		// TODO: double-check that we don't need to remove existing finders which might
		// hit the file system
#ifdef DEBUGTRACE
		PyRun_SimpleString("eval(met_lib_data[0]);met_init(True)");
#else
		PyRun_SimpleString("eval(met_lib_data[0]);met_init(False)");
#endif

		// TODO: figure out which reference counts need to be reduce to avoid leaking.
	}

	// now load the baked-in modules
	PyErr_Clear();
	for (InitFunc* f = &init_funcs[0]; f->func != NULL; f += 1)
	{
		dprintf("[PYTHON] Running %s", f->name);
		f->func();
		if (PyErr_Occurred())
		{
#ifdef DEBUGTRACE
			PyErr_Print();
#endif
			dprintf("[PYTHON] %s errored", f->name);
			PyErr_Clear();
		}
	}

	initialize_std_handlers();
	binding_init();
}