int DestroySharedMem()
{
	return (!UnmapViewOfFile(sdCmdLine)) || (!CloseHandle(hsmCmdLine));
}