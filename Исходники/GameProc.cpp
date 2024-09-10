void startGame()
{
	//获取游戏窗口句柄
	gameh=::FindWindowA(NULL,g_ChessInfo.caption);
	::GetWindowRect(gameh,&r1); 
 
	//保存当前鼠标指针
	//取得当前鼠标位置
	GetCursorPos(&p);
	
	//设置鼠标指针位置  取开局所在坐标:x=655;y=577 //lparam 0x0241028f
	SetCursorPos(g_ChessInfo.start_xoffset + r1.left, g_ChessInfo.start_yoffset + r1.top);
	
	//模拟鼠标的 单击（鼠标按下/鼠标抬起）
	//MOUSEEVENTF_LEFTDOWN Specifies that the left button is down. 
    //MOUSEEVENTF_LEFTUP 
	//鼠标在当前位置按下
	mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);
	mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
	
	//鼠标在当前位置抬起
	mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);
	
	//还原鼠标位置
	Sleep(200);//过一段时间 再执行后边的代码
    SetCursorPos(p.x,p.y);
}