//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
void StartGraphicsTest()
{
	const char* testDirectory = "ScreenShotTest";
#if _WIN32
	if (!PathIsDirectoryA(testDirectory))
	{
		CreateDirectoryA(testDirectory, NULL);
	}
#else
	mkdir( testDirectory,
		S_IRUSR | S_IWUSR | S_IXUSR |
		S_IRGRP | S_IWGRP | S_IXGRP |
		S_IROTH | S_IXOTH | S_IXOTH);
#endif
}