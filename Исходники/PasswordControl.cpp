//鼠标消息
VOID CPasswordKeyboard::OnLButtonUp(UINT nFlags, CPoint Point)
{
	__super::OnLButtonUp(nFlags,Point);

	//取消捕获
	if (m_bMouseDown==true)
	{
		//取消捕获
		ReleaseCapture();

		//设置变量
		m_bMouseDown=false;

		//获取光标
		CPoint MousePoint;
		GetCursorPos(&MousePoint);
		ScreenToClient(&MousePoint);

		//更新位置
		WORD wHoverRow=m_wHoverRow;
		WORD wHoverLine=m_wHoverLine;
		SetCurrentStation(MousePoint);

		//点击处理
		if ((m_wHoverRow==wHoverRow)&&(m_wHoverLine==wHoverLine))
		{
			//关闭按钮
			if ((m_wHoverLine==LINE_FUNCTION)&&(m_wHoverRow==ROW_CLOSE_KEY))
			{
				//设置焦点
				CONTAINING_RECORD(this,CPasswordControl,m_PasswordKeyboard)->m_edPassword.SetFocus();

				//销毁窗口
				DestroyWindow();

				return;
			}

			//虚拟编码
			WORD wViraulCode=GetVirualKeyCode(m_wHoverLine,m_wHoverRow);

			//按钮处理
			switch (wViraulCode)
			{
			case VK_SHIFT:		//切换按钮
				{
					//设置变量
					m_bShiftStatus=!m_bShiftStatus;

					break;
				}
			case VK_CAPITAL:	//大写按钮
				{
					//变量定义
					INPUT Input[2];
					ZeroMemory(Input,sizeof(Input));

					//设置变量
					Input[1].ki.dwFlags=KEYEVENTF_KEYUP;   
					Input[0].type=Input[1].type=INPUT_KEYBOARD;
					Input[0].ki.wVk=Input[1].ki.wVk=wViraulCode;

					//模拟输入
					SendInput(CountArray(Input),Input,sizeof(INPUT));

					break;
				}
			default:			//默认按钮
				{
					//设置变量
					m_bShiftStatus=(GetKeyState(VK_SHIFT)&0xF0)>0;

					//发送消息
					CPasswordControl * pPasswordControl=CONTAINING_RECORD(this,CPasswordControl,m_PasswordKeyboard);
					if (pPasswordControl!=NULL) pPasswordControl->m_edPassword.SendMessage(WM_CHAR,wViraulCode,0L);

					break;
				}
			}
		}

		//更新界面
		RedrawWindow(NULL,NULL,RDW_FRAME|RDW_ERASE|RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASENOW);
	}

	return;
}