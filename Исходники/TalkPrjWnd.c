static LRESULT CALLBACK
TalkPrjWndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{     
	switch (Msg)
	{
	case WM_CREATE:
		ClearKeyBuffer();
		PostMessage(hWnd,  WM_SETTIMER, 2000, 0);	
		break;		
		
	case WM_SETTIMER:
		SetTimer(hWnd, TIMER_PRJ, wParam, NULL);
		break;

	case WM_PAINT:
		if (GetFocus() == hWnd)
		{
			if (ST_UK_DELAY ==  g_TalkInfo.unlock.dwUnLockState)
			{
				TalkUlkWndPaint(hWnd, Msg, wParam, lParam);
			}
			else
			{
	//			TalkWndPaint(hWnd, Msg, wParam, lParam);
				TalkPrjWndPaint(hWnd, Msg, wParam, lParam);
			}
		}
		
		break;
		
	case WM_CHAR:
		if (GetFocus() != hWnd) 
		{
			SendMessage(GetFocus(),  WM_CHAR, wParam, 0l);
			return;			
		}
		wParam =  KeyBoardMap(wParam);
		if (wParam == KEY_RETURN)
		{
			if(ST_CO_TALKING == g_TalkInfo.talking.dwTalkState
				|| ST_CO_WAIT_PICKUP == g_TalkInfo.talking.dwTalkState
				|| ST_CI_TALKING == g_TalkInfo.talking.dwTalkState)
			{		
				SendGMHangupCmd2Talking();
			}			
			else if(ST_ORIGINAL == g_TalkInfo.talking.dwTalkState)
			{
				memset(g_KeyInputBuffer, 0, KEY_BUF_LEN);
				g_KeyInputBufferLen = 0;
				PostMessage(hWnd,  WM_CLOSE, 0, 0);
			}

		}
		
		else if ((wParam >= KEY_NUM_0) && (wParam <= KEY_NUM_9)) 
		{						
			ResetTimer(hWnd, TIMER_PRJ, 2000, NULL);
			if (g_KeyInputBufferLen < KEY_BUF_LEN)
			{
				g_KeyInputBuffer[g_KeyInputBufferLen++] = (UCHAR)wParam;
			}
			else
			{
				g_KeyInputBufferLen		=	0;
				g_KeyInputBuffer[g_KeyInputBufferLen++] = (UCHAR)wParam;
			}
		}
		
		PostMessage(hWnd,  WM_PAINT, 0, 0);		
		break;
		
	case WM_TIMER:
		TalkPrjTimerProc(hWnd, Msg, wParam, lParam);
		break;

	case WM_REFRESHPARENT_WND:
		SetFocus(hWnd);
		PostMessage(hWnd,  WM_PAINT, 0, 0);
		break;
		
	case WM_DESTROY:
		KillTimer(hWnd, TIMER_PRJ);
//		PostMessage(GetParent(hWnd),  WM_REFRESHPARENT_WND, 0, 0);
		g_hWNDTalk = NULL;
//		SendMessage(GetFocus(),  WM_REFRESHPARENT_WND, 0, 0);		
		break;
		
	default:
//		if (WM_CLOSE == Msg) 
//		{
//			RemoveOneWnd(hWnd);
//		}
//		return DefWindowProc(hWnd, Msg, wParam, lParam);
		
		DefWindowProc(hWnd, Msg, wParam, lParam);
		
		if (WM_CLOSE == Msg) 
		{
			RemoveOneWnd(hWnd);
		}
	}
	return 0;
}