static int AssertFailedFunc(char *sz)
{
	MessageBox(GetActiveWindow(), sz, "Assert failure", MB_OK);
	int Set_Your_Breakpoint_Here = 1;
	return 1;
}