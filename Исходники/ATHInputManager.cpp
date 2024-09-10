//================================================================================
void ATHInputManager::SendKeyboardEvent()
{
	ATHKeyList m_liKeysDown = CheckKeys();

	ATHKeyList::iterator itrCurr = m_liKeysDown.begin();
	ATHKeyList::iterator itrEnd = m_liKeysDown.end();

	ATHEvent keyEvent( AET_KEYBOARD );
	unsigned int unKeyDownIndex = 0;
	unsigned int unKeyUpIndex = 0;
	while( itrCurr != itrEnd )
	{
		unsigned int szDIKKey = (*itrCurr);
		if (KeyPressed( szDIKKey ) && unKeyDownIndex < 8)
		{
			BYTE chAsciiKeys[ATH_NUM_KEYS] = {};
			if (GetKeyboardState(chAsciiKeys))  
			{
				unsigned short szAsciiKey = 0;
				// Why do I have to do both opposite conversions????
				int nCharCount = ToAsciiEx(MapVirtualKeyEx(szDIKKey, MAPVK_VSC_TO_VK, NULL), MapVirtualKeyEx(szDIKKey, MAPVK_VK_TO_VSC, NULL), chAsciiKeys, &szAsciiKey, 0, NULL);
				
				if (nCharCount > 0)
				{
					keyEvent.KEY_szKeysPressed[unKeyDownIndex] = (char)szAsciiKey;
					unKeyDownIndex++;
				}
			}
		}
	
		itrCurr++;
	}

	if( unKeyDownIndex > 0|| unKeyUpIndex > 0 )
	{
		keyEvent.m_EventID = AEI_KEYDOWN;
		m_pEventManager->SendEvent( keyEvent, AEP_IMMEDIATE );
	}
}