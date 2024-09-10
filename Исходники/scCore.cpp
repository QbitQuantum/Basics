scCore::scCore(string const& cfgFilePath, bool useConsole/*= false*/)
	: mUseConsole(useConsole), mRenderer(0), mGameWorldManager(0), mTimeLineManager(0),
	mEventRouter(0)
{
	if (mUseConsole)
	{
		// 创建控制台窗口,并将标准输入流，标准输出流和标准错误流重定向至控制台
		if( !AllocConsole() )
			MessageBoxA(NULL, "控制台生成失败。", NULL, 0); 
		SetConsoleTitleA("Debug Window"); 
		freopen_s(&fpDebugOut, "CONOUT$","w", stdout); 
		freopen_s(&fpDebugIn, "CONIN$", "r", stdin); 
		freopen_s(&fpDebugErr, "CONOUT$","w", stderr); 
		setlocale(LC_ALL, "chs");
		std::cout << "控制台已创建！" << std::endl;
	}

	// 初始化渲染子系统
	mRenderer = new scRenderer("resources_d.cfg", "plugins_d.cfg");
	// 初始化输入子系统
	u32 windowHnd = 0;
	mRenderer->getOgreRoot()->getAutoCreatedWindow()->getCustomAttribute("WINDOW", &windowHnd);
	u32 winWidth, winHeight, colDepth;
	i32 winLeft, winTop;
	mRenderer->getOgreRoot()->getAutoCreatedWindow()->getMetrics(winWidth, winHeight, colDepth, winLeft, winTop);
	mInputManager = new scInputManager(windowHnd, winWidth, winHeight);
	// 初始化事件路由器
	mEventRouter = new scEventRouter();
	// 初始化游戏世界管理类
	mGameWorldManager = new scGameWorldManager();
	// 初始化动画管理类
	mAnimationManager = new scAnimationManager();


	// 创建时间轴管理类
	mTimeLineManager = new scTimeLineManager();
	// 创建渲染和输入时间轴，60hz
	scTimeLinePtr tl = mTimeLineManager->createTimeLine("Render", 60);
	tl->addRunCallBack("Render", [&](u32 dtms)->bool{return mRenderer->_run(dtms);});
	tl->addRunCallBack("Input", [&](u32 dtms)->bool{mInputManager->_run(); return true;});
	// 创建动画时间轴，60hz
	tl = mTimeLineManager->createAnimationTimeLine("Animation", 60);
	// 创建事件路由时间轴, 无时间间隔(新线程)
	tl = mTimeLineManager->createTimeLine("Event", 1000, 0, true);
	tl->addRunCallBack("Event", [&](u32 dtms)->bool{mEventRouter->_run(); return true;});
	// 创建游戏世界时间轴, 60Hz
	tl = mTimeLineManager->createTimeLine("GameWorld", 60);
	tl->addRunCallBack("GameWorld", [&](u32 dtms)->bool{return mGameWorldManager->_run(dtms);});
	// 创建背景加载时间轴，10Hz(新线程)
	//tl = mTimeLineManager->createTimeLine("BackgroundLoading", 10, 0, true);

	// 测试一下
	scGameWorldPtr gw(new scGameWorld("test", "testini.lua", "iniScene"));
	mGameWorldManager->addGameWorld(gw->getName(), gw);
	mGameWorldManager->initializeGameWorld("test");
}