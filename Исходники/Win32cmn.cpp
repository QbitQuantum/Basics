LRESULT	CALLBACK CGameGirlProc(HWND hw, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	//コールバック受付け

	switch(iMsg) {
    case WM_CREATE:
	    DragAcceptFiles(hw, gxTrue);
		break;

	case WM_DROPFILES:
		{
			HDROP hDrop = (HDROP) wParam;
			Sint32 sNum = DragQueryFile(hDrop , 0xffffffff , NULL , NULL );

			gxChar str[512];

			for(Sint32 ii=0;ii<sNum;ii++)
			{
				wchar_t wStr[512];

				DragQueryFile(hDrop , ii , (LPWSTR)wStr , sizeof(wStr) );

				Uint32 uLen = wcslen(wStr);
				WideCharToMultiByte( CP_ACP , 0 ,(LPCWSTR)wStr , uLen+1 , str, uLen*2 ,NULL,NULL);

				//DragQueryFile(hDrop , ii , str , sizeof(str) );

				gxBool DragAndDrop(char* szFileName);
				DragAndDrop( str );
			}
		}
		break;

	case WM_CLOSE:
		DragAcceptFiles(hw, gxFalse);
		CGameGirl::GetInstance()->SetExitWindow();
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_SYSCOMMAND:
		//スクリーンセーバー抑制
		if ( wParam == SC_SCREENSAVE )
	    {
	        return 1;
	    }
		if ( wParam == SC_MONITORPOWER )
	    {
	        return 1;
	    }
	    return (DefWindowProc(hw, iMsg, wParam, lParam));

	case WM_COMMAND:
		InputShortCutCheck( LOWORD(wParam) );
		return 0;

	case WM_SIZE:
		g_pWindows->m_uScreenWidth  = LOWORD(lParam);
		g_pWindows->m_uScreenHeight = HIWORD(lParam);
		::Resume();
		break;

	case WM_QUERYENDSESSION:
		ShutdownBlockReasonCreate( hw ,L"gxLib running" );
		return false;

 	case WM_ENDSESSION:
		CGameGirl::GetInstance()->SetExitWindow();
		ShutdownBlockReasonDestroy( hw );
		break;

	default:
		InputKeyCheck( iMsg , wParam , lParam );
		break;
	}

	return DefWindowProc( hw, iMsg, wParam, lParam);
}