int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd )
{
	SystemClass* System;

	// 创建System类
	System = new SystemClass;

	if (!System)
	{
		return 0;
	}

	// 初始化System类,主循环
	if (System->Initialze())
	{
		System->Run();
	}

	// 删除System类
	System->Shutdown();
	delete System;
	System = NULL;

	return 0;

}