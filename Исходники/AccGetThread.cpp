void ThreadProc( void* param )
{
	CoInitialize(NULL);
	thread_id_accget_ = GetCurrentThreadId();

	MSG msg;
	PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE);
	while(GetMessage(&msg, NULL, 0, 0))
	{
		TCHAR buf[256];
		CComPtr<IAccessible> acc;
		if (S_OK == AccessibleObjectFromWindow((HWND)msg.lParam, OBJID_WINDOW, IID_IAccessible, (void**)&acc))
		{
			VARIANT id;
			id.vt = VT_I4;
			id.lVal = 0;
			GetObjectValue(acc, &id, buf, ARRAYSIZE(buf));
			OutputDebugString(TEXT("WinRun Text : "));
			OutputDebugString(buf);
		}
	}
	CoUninitialize();
}