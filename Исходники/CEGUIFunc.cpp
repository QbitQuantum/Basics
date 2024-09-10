/**
*@brief キーコード(CEGUI::Key)を文字(CEGUI::utf32)に変換
CEGUI公式サイト(http://cegui.org.uk/wiki/DirectInput_to_CEGUI_utf32)のコードを一部変更(MITライセンス)
* @param scanCode キーコード
* @return 文字
*/
CEGUI::utf32 keycodeToUTF32( unsigned int scanCode)
 {

 	CEGUI::utf32 utf = 0;

#ifdef _WIN32
 	BYTE keyboardState[256];
 	unsigned char ucBuffer[3];
 	static WCHAR deadKey = '\0';
 
 	
 	HKL hklKeyboardLayout = GetKeyboardLayout(0);
 	
 	if (GetKeyboardState(keyboardState) == FALSE)
 		return utf;
 
 	
 	UINT virtualKey = MapVirtualKeyEx(scanCode, 3, hklKeyboardLayout);
 	if (virtualKey == 0)
 		return utf;
 

 	int ascii = ToAsciiEx(virtualKey, scanCode, keyboardState, (LPWORD) ucBuffer, 0, hklKeyboardLayout);
 	if(deadKey != '\0' && ascii == 1)
 	{
 		
 		WCHAR wcBuffer[3];
 		WCHAR out[3];
 		wcBuffer[0] = ucBuffer[0];
 		wcBuffer[1] = deadKey;
 		wcBuffer[2] = '\0';
 		if( FoldStringW(MAP_PRECOMPOSED, (LPWSTR) wcBuffer, 3, (LPWSTR) out, 3) )
 			utf = out[0];
 		else
 		{
 			
 			DWORD dw = GetLastError();
 			switch(dw)
 			{
 			case ERROR_INSUFFICIENT_BUFFER:
 			case ERROR_INVALID_FLAGS:
 			case ERROR_INVALID_PARAMETER:
 				break;
 			}
 		}
 		deadKey = '\0';
 	}
 	else if (ascii == 1)
 	{
 		
 		utf = ucBuffer[0];
 		deadKey = '\0';
 	}
 	else
 	{
 		
 		switch(ucBuffer[0])
 		{
 		case 0x5E:
 			deadKey = 0x302;
 			break;
 		case 0x60:
 			deadKey = 0x300;
 			break;
 		case 0xA8:
 			deadKey = 0x308;
 			break;
 		case 0xB4:
 			deadKey = 0x301;
 			break;
 		case 0xB8:
 			deadKey = 0x327;
 			break;
 		default:
 			deadKey = ucBuffer[0];
 		}
 	}
#else
#endif
 	return utf;
 }