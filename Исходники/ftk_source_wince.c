static Ret ftk_source_wince_dispatch(FtkSource* thiz)
{
	MSG msg;

	while(PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}

	Sleep(20);

	return RET_OK;
}