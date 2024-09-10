LRESULT CALLBACK DlgProc(HWND hDlg_MainProc, UINT Message, WPARAM wParam, LPARAM lParam)
{
	static HWND ButtonCheck = NULL;
	static HWND EditControl = NULL;
	static HANDLE handle_Check = NULL;
	static int PS = 0x22;

	char EnterText[30] = { 0 };
	switch (Message)
	{
	case WM_SETCURSOR:
		if ((DWORD)ButtonCheck == wParam)
		{
			
			if (PS == 0x22)
			{
				MoveWindow(ButtonCheck, 10, 10, 80, 35, TRUE);
				PS = 0x15;
			}
			else if (0x15 == PS)
			{
				MoveWindow(ButtonCheck, 20, 230, 80, 35, TRUE);
				PS = 0x18;
			}
			else if (0x18 == PS)
			{
				MoveWindow(ButtonCheck, 350, 230, 80, 35, TRUE);
				PS = 0x22;
			}
		}
		break;

	case WM_COMMAND:
		if (HIWORD(wParam) == 0)
		{
			switch (LOWORD(wParam))
			{
			case IDC_Button1:

				GetWindowTextA(EditControl, EnterText, 30);
				
				//check strlen
				int x = strlen(EnterText);
				if (x != 22)
				{
					MessageBox(0, L"Try Again", L"Fail", 0);
					break;
				}
				//check HCTF{}
				if (FALSE == CheckHCTF(EnterText, EnterText[x-1]))
				{
					MessageBox(0, L"Try Again", L"Fail", 0);
					break;
				}
				//check——encode
				if (FALSE == Main_Check(EnterText))
				{
					MessageBox(0, L"Try Again", L"Fail", 0);
					break;
				}

				//馄饨加解密核心
				for (int i = 0; i < 100; i++)
				{
					
					int xor = rou^chaos;
					if (xor > 0)//去掉2个错误情况
					{
						
						//解密x反作弊flag	亦或比较
						
						if ((EnterText[17] ^ xor) == CHECK_1[0] &&
							(EnterText[18] ^ xor) == CHECK_1[1] &&
							(EnterText[19] ^ xor) == CHECK_1[2] &&
							(EnterText[20] ^ xor) == CHECK_1[3])
						{
							//判断成功进入下一阶段，乱序
							int exchange = 0;
							//0与6换位
							exchange = Code1[0];
							Code1[0] = Code1[6];
							Code1[6] = exchange;
							//3与8换位
							exchange = Code1[3];
							Code1[3] = Code1[8];
							Code1[8] = exchange;
							//2与5换位
							exchange = Code1[2];
							Code1[2] = Code1[5];
							Code1[5] = exchange;
							//11与4换位
							exchange = Code1[11];
							Code1[11] = Code1[4];
							Code1[4] = exchange;
							//循环进行比较

							for (int a = 0; a < 12; a++)
							{
								
								if (Maincjeckaaa[a] != Code1[a])
								{
									MessageBox(0, L"Try Again", L"Fail", 0);
									exit(-1);
								}
							}
							//最后判断xor是否为2
							if (xor != 2)
							{
								
								break;
							}
							MessageBox(0, L"YOU GOT IT", L"OK", 0);
							exit(0);
							break;
						}
					}
					Sleep(20);
				}
				MessageBox(0, L"Try Again", L"Fail", 0);

			}
		}
		break;
	case WM_INITDIALOG:
		ButtonCheck = GetDlgItem(hDlg_MainProc, IDC_Button1);
		EditControl = GetDlgItem(hDlg_MainProc, IDC_EDIT2);
		//thread1
		handle_Check = (HANDLE)_beginthreadex(NULL, 0, Check_ThreadProc, NULL, NULL, NULL);
		if (NULL == handle_Check)
		{
			printf("甜党万岁\n");
		}
		break;
	case WM_CLOSE:
		CloseHandle(handle_Check);
		EndDialog(hDlg_MainProc, 0);
		DestroyWindow(hDlg_MainProc);
		break;
	default:
		break;
	}
	return 0;
}