//程序运行  
int CCApplication::run()  
{  
    //设置注册表PVRFrame隐藏  
    PVRFrameEnableControlWindow(false);  
    //主消息循环  
    MSG msg;  
    LARGE_INTEGER nFreq;  
    LARGE_INTEGER nLast;  
    LARGE_INTEGER nNow;  
//WINDOWS高精度定时器的用法，先获取频率  
QueryPerformanceFrequency(&nFreq);  
//获取当前的计数值,即频率x当前时间  
    QueryPerformanceCounter(&nLast);  
	//initInstance函数为虚函数，由派生类AppDelegate进行了重载。此段代码在调用AppDelegate重载的initInstance函数之后调用applicationDidFinishLaunching函数完成一些初始化处理。  
	//注:AppDelegate重载initInstance函数做了什么我们暂且只先认为它如平时我们WINDOWS基本框架程序一样创建了一个Windows窗口。【伏笔1后面会有讲解】。  
    if (! initInstance() || ! applicationDidFinishLaunching())  
    {  
        return 0;  
    }  
//取得当前使用的OPENGL窗口管理实例对象  
CCEGLView& mainWnd = CCEGLView::sharedOpenGLView();  
//将窗口居中显示  
    mainWnd.centerWindow();  
    ShowWindow(mainWnd.getHWnd(), SW_SHOW);  
//非常熟悉!进入WINDOWS消息循环  
    while (1)  
{  
   //如果没有获取到WINDOWS消息  
        if (! PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))  
        {  
            // 取得当前的计数值,即频率x当前时间  
            QueryPerformanceCounter(&nNow);  
            //m_nAnimationInterval.QuadPart的值 为setAnimationInterval函数进行设置的固定值。此处是为了判断时间流逝了多久，是否应该更新显示设备  
            if (nNow.QuadPart - nLast.QuadPart > m_nAnimationInterval.QuadPart)  
            {  
  //如果时间流逝达到了设定的FPS时间差，则更新计数值。  
                nLast.QuadPart = nNow.QuadPart;  
  //这里是设备渲染场景的函数，【伏笔2后面会有讲解】   
                CCDirector::sharedDirector()->mainLoop();  
            }  
            else  
            {  
  //sleep0秒的意义是让CPU做下时间片切换，防止死循环而使系统其它程序得不到响应。  
                Sleep(0);  
            }  
            continue;  
        }  
   //有消息获取到  
        if (WM_QUIT == msg.message)  
        {  
   // 如果获取的消息是退出则退出循环。  
            break;  
        }  
        // 如果没有定义加速键或者处理完加速键信息  
        if (! m_hAccelTable || ! TranslateAccelerator(msg.hwnd, m_hAccelTable, &msg))  
        {  
   //处理Windows消息  
            TranslateMessage(&msg);  
            DispatchMessage(&msg);  
        }  
    }  
    return (int) msg.wParam;  
}  