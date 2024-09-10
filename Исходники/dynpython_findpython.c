// Given the path to our python executable, load the binary and check
// the processor architecture. If it's an x64 binary and our current
// executable isn't, we'll return 0.
static int is_valid(char* python)
{
	char sPythonDir[MAX_PATH+1] = {0};
	int result = 1;
	LOADED_IMAGE oImg;
	ZeroMemory(&oImg, sizeof(oImg));
	if(!get_parent_dir(python, sPythonDir, MAX_PATH)) {
		debug("Could not get parent folder of %s..", python);
		return 0;
	}
	if(!MapAndLoad(PYTHON_EXE, sPythonDir, &oImg, 0, 1)) {
		debug("Could not MapAndLoad %s. Used folder: %s", PYTHON_EXE, sPythonDir);
		return 0;
	}
	switch(oImg.FileHeader->FileHeader.Machine)
	{
		case IMAGE_FILE_MACHINE_IA64:
#ifdef _M_IA64
			result = 1;
#else
			result = 0;
			Platform_Mismatch("IA64");
#endif
			break;
		// AMD64
		case IMAGE_FILE_MACHINE_AMD64:
#ifdef _M_X64
			result = 1;
#else
			result = 0;
			Platform_Mismatch("X64");
#endif
			break;
		// X86 (32-bit)
		case IMAGE_FILE_MACHINE_I386:
#ifdef _M_IX86
			result = 1;
#else
			result = 0;
			Platform_Mismatch("X86");
#endif
			break;
		// IA64
		default:
			result = 0;
			Platform_Mismatch("Invalid");
			break;
	}
	// This shouldn't happen, but you never know.
	if(!UnMapAndLoad(&oImg)) {
		debug("Could not unmap the python image.");
		return 0;
	}
	return result;
}