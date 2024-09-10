//*****************************************************************
//	向HIMC发送消息
//	利用此函数直接向输入法所属窗口发送消息
//*****************************************************************
BOOL MyGenerateMessage(HIMC hIMC, UINT msg, WPARAM wParam, LPARAM lParam)
{
	BOOL bRet=FALSE;
    LPINPUTCONTEXT lpIMC= ImmLockIMC(hIMC);
	if(lpIMC == NULL)
		return FALSE;    

    if (IsWindow(lpIMC->hWnd))
    {
		PostMessage(lpIMC->hWnd,msg,wParam,lParam);
		bRet=TRUE;
    }

	ImmUnlockIMC(hIMC); 
	return bRet;
}