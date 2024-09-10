bool GSDeviceDX::LoadD3DCompiler()
{
	// Windows 8.1 and later come with the latest d3dcompiler_47.dll, but
	// Windows 7 devs might also have the dll available for use (which will
	// have to be placed in the application directory)
	s_d3d_compiler_dll = LoadLibraryEx(D3DCOMPILER_DLL, nullptr, LOAD_LIBRARY_SEARCH_APPLICATION_DIR | LOAD_LIBRARY_SEARCH_SYSTEM32);

	// Windows Vista and 7 can use the older version. If the previous LoadLibrary
	// call fails on Windows 8.1 and later, then the user's system is likely
	// broken.
	if (s_d3d_compiler_dll)
	{
		s_old_d3d_compiler_dll = false;
	}
	else
	{
		if (!IsWindows8Point1OrGreater())
			// Use LoadLibrary instead of LoadLibraryEx, some Windows 7 systems
			// have issues with it.
			s_d3d_compiler_dll = LoadLibrary("D3DCompiler_43.dll");

		if (s_d3d_compiler_dll == nullptr)
			return false;

		s_old_d3d_compiler_dll = true;
	}

	s_pD3DCompile = reinterpret_cast<decltype(&D3DCompile)>(GetProcAddress(s_d3d_compiler_dll, "D3DCompile"));
	if (s_pD3DCompile)
		return true;

	FreeLibrary(s_d3d_compiler_dll);
	s_d3d_compiler_dll = nullptr;
	return false;
}