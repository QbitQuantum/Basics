void SystemClass::CreateConsole()
{
	AllocConsole();  // Create Console Window

	FILE *stream;

	wstring ConsoleName = L"Information Console";

	_wfreopen_s(&stream, L"CONIN$", L"rb", stdin);   // reopen stdin handle as console window input

	_wfreopen_s(&stream, L"CONOUT$", L"wb", stdout);  // reopen stout handle as console window output

	_wfreopen_s(&stream, L"CONOUT$", L"wb", stderr); // reopen stderr handle as console window output

	SetConsoleTitle(ConsoleName.c_str());
	
}