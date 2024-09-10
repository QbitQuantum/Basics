int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpszCmdParam,
	int nCmdShow)
{
#ifdef DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(157);

	AllocConsole();
	FILE* console;
	freopen_s(&console, "CONOUT$", "wt", stdout);
#endif

	CGameManager *GameManager = CGameManager::GetInstance();
	GameManager->initialize(600, 600);
	GameManager->changeScene(new CStartScene());
	GameManager->run();

#ifdef DEBUG
	FreeConsole();
#endif

	return 0;
}