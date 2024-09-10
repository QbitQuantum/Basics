BOOL CMainApp::InitInstance()
{
	if(!CheckSingleInstance())
	{
		return FALSE;
	}

	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	//虚函数调用捕获
	_set_purecall_handler(PurecallHandler);

	module_manager.PushEvent(MakeEvent<MODULE_ID_CORE>()(Hall::EVENT_VALUE_HALL_CREATEANDSHOW,MODULE_ID_HALL));

	//module_manager.PushEvent(MakeEvent<MODULE_ID_ROOM>()(Room::EVENT_VALUE_TEST,MODULE_ID_ROOM));

    //模块管理单元启动
	module_manager.Construct();

	module_manager.run();

	module_manager.Destruct();

	return FALSE;
}