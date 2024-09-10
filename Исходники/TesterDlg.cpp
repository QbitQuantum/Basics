UINT WINAPI EQUIPTask(LPVOID lpPara)
{
	//CTesterDlg *pTester=(CTesterDlg *)lpPara;
	MSG msg;
	int i=0;
	size_t ConvertedChars=0;
	char TempBuf[1024]="";
	wchar_t RevBuf[1024]= _T("");
	UINT FixNum=0;
	int bufL=0;

	while(TRUE)
	{
		if (!WaitMessage())
		{
			continue;
		}
		while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			switch (msg.message)
			{
			case WM_UPDATE_INFO_EQUIP:
				FixNum=(UINT)msg.lParam-UI_SERVER_PORT_START+1;
				if ((char *)msg.wParam)              // clear the bufferWM_EQUIPMENT_OPEN
				{
					free((char *)msg.wParam);
				}
				//remove start by Talen 2011/07/21
			////////	if(gStationInfo.EquipInfo.EqipXmlFlag)
			////////	{
			////////		gEQIP.CountNumXml(FixNum);
			////////	}
			////////	else
			////////	{
			////////		gEQIP.CountNum(FixNum);
			////////	}
			////////	break;
			////////case WM_EQUIPMENT_OPEN:
			////////	if(!gStationInfo.EquipInfo.EqipXmlFlag)
			////////	{
			////////		gEQIP.InitialEQUIP();					
			////////	}
				//remove end by Talen 2011/07/21
				gEQIP.CountNum(FixNum);
				break;
			case WM_EXIT:
				goto ExitLabel;
				break;
			default:
				;
			}
		}
	}

ExitLabel:
	return 0;
}