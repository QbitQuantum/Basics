int wmain(int argc, wchar_t* argv[])
{
	// 使_putws输出支持中文
	setlocale( LC_ALL, "chs" );

	HANDLE hThread;

	// 演示了在一个独立的线程中使用#import指令智能指针自动化PowerPoint 
	hThread = CreateThread(NULL, 0, AutomatePowerPointByImport, NULL, 0, NULL);
	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hThread);

	_putws(L"");

	// 演示了在一个独立的线程中使用C++和COM API自动化PowerPoint
	hThread = CreateThread(NULL, 0, AutomatePowerPointByCOMAPI, NULL, 0, NULL);
	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hThread);

	return 0;
}