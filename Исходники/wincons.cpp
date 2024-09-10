void __stdcall DolphinFatalExit(int exitCode, const char* msg)
{
	int result = fprintf(stderr, "%s\n", msg);
	FatalExit(exitCode);
}