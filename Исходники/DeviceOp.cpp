UINT WINAPI SRQRevCallbackThread(LPVOID lpPara)
{

	MSG msg;
	unsigned char RevBuf[MA_DATA_LEN];
	UINT DataLen=0;
	CDeviceOp *pDOP=(CDeviceOp *)lpPara;

	while (1)
	{
		if (!WaitMessage()) 
		{
			return 1;
		}	
		memset(RevBuf,0,sizeof(RevBuf));
		while (PeekMessage(&msg, NULL,  0, 0, PM_REMOVE)) 
		{			
			if (WM_QUIT==msg.message)
			{
				goto Exit;
			}

			memcpy_s(RevBuf, sizeof(RevBuf),(unsigned char *)msg.wParam,msg.lParam);	
			pDOP->DevSRQOnRev(RevBuf,msg.lParam);		

			if ((unsigned char *)msg.wParam)
			{
				free((unsigned char *)msg.wParam);
			}
		}	  	
	}
Exit:
	return 1;
}