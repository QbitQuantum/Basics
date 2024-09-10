int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR    lpCmdLine,
                     int       nCmdShow)
{
	int exitcode = 0;
	//Allocate a console window
	//so that messages can be redirected to stdout
	if (!AllocConsole())
	{
		ErrorExit(TEXT("AllocConsole"));
	}

	FILE* pf_out;
	freopen_s(&pf_out, "CONOUT$", "w", stdout);

	PrintUsage();

	//Create the application instance
	OGLApplication* myapp = OGLApplication::CreateApplication(hInstance);

	exitcode = myapp->Run();

	myapp->DestroyApplication();

	fclose(pf_out);

	//Free the console window
	if (!FreeConsole())
	{
		ErrorExit(TEXT("FreeConsole"));
	}

	return exitcode;
}