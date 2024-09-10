int WINAPI WinMain(	HINSTANCE	hInstance,			// Instance
					HINSTANCE	hPrevInstance,		// Previous Instance
					LPSTR		lpCmdLine,			// Command Line Parameters
					int			nCmdShow)			// Window Show State
{
	MSG		msg;									// Windows Message Structure
	BOOL	done=FALSE;								// Bool Variable To Exit Loop

	// Ask The User Which Screen Mode They Prefer
    if (MessageBox(NULL,"Would You Like To Run In Fullscreen Mode?", "Start FullScreen?",MB_YESNO|MB_ICONQUESTION)==IDNO)
	{
		fullscreen=FALSE;							// Windowed Mode
	}

	// Create Our OpenGL Window
	if (!CreateGLWindow("3*3 MagicCube - 毕梦霄",1024,576,16,fullscreen))
	{
		return 0;									// Quit If Window Was Not Created
	}
	//调用API函数使用双冒号前缀
	::SetTimer(hWnd,1,10,NULL);

	::SetTimer(hWnd,2,200,TimerProc);


	while(!done)									// Loop That Runs While done=FALSE|消息循环程序段
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))	// Is There A Message Waiting?|如果有消息我们处理消息，如果没有消息我们绘制场景
		{
			if (msg.message==WM_QUIT)				// Have We Received A Quit Message?
			{
				done=TRUE;							// If So done=TRUE
			}
			else									// If Not, Deal With Window Messages
			{
				TranslateMessage(&msg);				// Translate The Message
				DispatchMessage(&msg);				// Dispatch The Message
			}
		}
		else										// If There Are No Messages
		{
			// Draw The Scene.  Watch For ESC Key And Quit Messages From DrawGLScene()
			// 此主消息循环负责刷新绘图环境
			if ((active && !DrawGLScene()) || keys[VK_ESCAPE])	// Active?  Was There A Quit Received?
			{
				done=TRUE;							// ESC or DrawGLScene Signalled A Quit
			}
			else									// Not Time To Quit, Update Screen
			{
				SwapBuffers(hDC);					// Swap Buffers (Double Buffering)|等同于glFlush()强制刷新，用于交换双缓冲区从而显示更新
			}

			//WndProc只处理事件本身，即把键盘按下或弹起的消息记录到数据结构中，具体处理其含义是在主程序中进行的
			if (keys[VK_F1])						// Is F1 Being Pressed?
			{
				keys[VK_F1]=FALSE;					// If So Make Key FALSE
				KillGLWindow();						// Kill Our Current Window
				fullscreen=!fullscreen;				// Toggle Fullscreen / Windowed Mode
				// Recreate Our OpenGL Window
				if (!CreateGLWindow("这是个彩蛋。！",640,480,16,fullscreen))//这是个彩蛋。
				{
					return 0;						// Quit If Window Was Not Created
				}
			}

			//按方向键可以把魔方上下左右移动
			if(keys[VK_LEFT])
			{
				keys[VK_LEFT]=FALSE;	

				RX -= 0.05f;						//全局X坐标，Z是景深

			}

			if(keys[VK_RIGHT])
			{
				keys[VK_RIGHT]=FALSE;	
				
				RX += 0.05f;

			}

			if(keys[VK_UP])
			{
				keys[VK_UP]=FALSE;	
				
				RY += 0.05f;

			}

			if(keys[VK_DOWN])
			{
				keys[VK_DOWN]=FALSE;	
				
				RY -= 0.05f;
	
			}
		}
	}

	// Shutdown
	KillGLWindow();									// Kill The Window
	return (msg.wParam);							// Exit The Program
}