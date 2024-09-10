HICON* retrieveIconFrom(iconLoader* loader, WPARAM wParam, LPARAM lParam)
{
	/*
	//Maybe we should add some semaphore checks
	DWORD waitFor = WaitForSingleObject( loader->semaphore, 0L );
	*/

	if( loader->thread == NULL)
	{
		if( loader->icon != NULL )
			return &(loader->icon);
		return NULL;
	}

	if( wParam != NULL || lParam != NULL )
	{
		DWORD waitFor = WaitForSingleObject( loader->semaphore, INFINITE );
		if( waitFor == WAIT_OBJECT_0 )
		{
			refreshParam* param = (refreshParam*)malloc(sizeof(refreshParam));
			memset(param, 0, sizeof(refreshParam));
			param->lParam = lParam;
			param->wParam = wParam;

			loader->refreshs->insert( loader->refreshs->end(), param );
		}
		else
		{
			PostMessageW(g_hwndMain, WM_DRAWITEM, lParam, wParam);
		}
	}

	return NULL;
}