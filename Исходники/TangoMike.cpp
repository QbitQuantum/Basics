int WINAPI WinMain( 
	HINSTANCE /* hInstance */,
	HINSTANCE /* hPrevInstance */,
	LPSTR /* lpCmdLine */,
	int /* nCmdShow */
	)
{
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	EasyServer::GetInstance();
	//DevConsoleCreate();
	//ShellExecute(NULL, L"open", L"C:\\Users\\Administrator\\Documents\\TangoMike\\Src\\TangoMike\\Release\\TangoMike.exe", NULL, NULL, SW_SHOWNORMAL);

	std::srand(unsigned(std::time(0)));
	// Ignoring the return value because we want to continue running even in the
	// unlikely event that HeapSetInformation fails.
	//HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

	if (SUCCEEDED(CoInitialize(NULL)))
	{
		{

			XMLBackup::GetInstance()->LoadData();
			Application app;
			Relationship::GetInstance()->LoadDataFromXMLBackup();
			if (SUCCEEDED(app.Initialize()))
			{
				app.RunMessageLoop();
			}
		}
		CoUninitialize();
	}
	Relationship::FreeInstance();
	XMLBackup::FreeInstance();
	EasyServer::FreeInstance();
	return 0;
}