	void MyGUIRenderClick::injectKeyPress(MyGUI::KeyCode _key, MyGUI::Char _text)
	{
		if (!mGUI)
			return;

		/*if (_key == MyGUI::KeyCode::Escape)
		{
			mExit = true;
			return;
		}	*/	

		HKL hKL = ::GetKeyboardLayout(0); // 获取当前线程所使用的键盘布局

		if( hKL && ::ImmIsIME(hKL) ) 
		{// 显示输入的汉字
			HIMC hIMC = ::ImmGetContext( hWnd );

			// Get the size of the result string.
			DWORD dwSize = ::ImmGetCompositionStringW(hIMC, GCS_RESULTSTR, NULL, 0);

			if (dwSize > 0)
			{
				wchar_t* lwszStr = new wchar_t[dwSize + 1];
				memset(lwszStr, 0, (dwSize + 1));

				// Get the result strings that is generated by IME into lpstr.
				ImmGetCompositionStringW(hIMC, GCS_RESULTSTR, lwszStr, dwSize);				

				m_pMainWindow->setCaption(lwszStr);
				delete[] lwszStr;
			}		


			::ImmReleaseContext( hWnd, hIMC );
		}
		if (hKL && ::ImmIsIME(hKL))
		{// 显示可选择的汉字
			HIMC hIMC;
			hIMC = ImmGetContext(hWnd); 
			DWORD dwCount = 0, dwSize = 0;
			dwSize = ImmGetCandidateListCount(hIMC, &dwCount);
			if (dwCount > 0)
			{
				std::wstring wstrCaption;
				char* pBuf   =   new   char[dwSize + 1];   
				LPCANDIDATELIST pList   =   (LPCANDIDATELIST)pBuf;   

				for   (int i=0;   i<dwCount;   i++)   
				{   
					::ImmGetCandidateList(hIMC,   i,   pList,dwSize);   
					for   (int j=0;   j<pList->dwPageSize;   j++)   
					{
						char* pStr   =   (char*)(pBuf+pList->dwOffset[pList->dwPageStart+j]);
						wchar_t wszStr[MAX_PATH + 1] = {0,};
						MultiByteToWideChar(CP_ACP,0,pStr,-1, wszStr , MAX_PATH);
						wstrCaption = wstrCaption + wszStr + L" ";
					}
				}

				delete[]   pBuf;   

				m_pEdit->setCaption(wstrCaption);
			}
			
			::ImmReleaseContext(hWnd,hIMC);     

			

			return ;  
		}
		else
		{
			mGUI->injectKeyPress(_key, _text);
		}
	}