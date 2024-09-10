		u16 CKeyboard::_TranslateChar(WPARAM wParam, LPARAM lParam, u32 uiFlags)
		{
			u32 uiScanCode = MapVirtualKeyA( wParam, 2 );
			ch16 wchCode[] = { 0, 0 };
			i32 iResult = ToUnicodeEx( wParam, uiScanCode, m_abyKeyboardState, wchCode, sizeof( ch16 ), uiFlags, m_WinHKL );
			//iResult = ToUnicodeEx( wParam, uiScanCode, m_abyKeyboardState, wchCode, sizeof( ch16 ), uiFlags, m_WinHKL );
			if( iResult <= 0 )
			{
				//Set to default if there is no translation
				wchCode[ 0 ] = (ch16)wParam;
			}
			wchCode[ 1 ] = 0;
			return wchCode[ 0 ];
		}