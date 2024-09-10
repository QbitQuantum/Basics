WCHAR CTextService::_GetCh(BYTE vk, BYTE vkoff)
{
	BYTE keystate[256];
	WCHAR ubuff;
	WCHAR u = L'\0';

	GetKeyboardState(keystate);

	switch(inputmode)
	{
	case im_hiragana:
	case im_katakana:
	case im_katakana_ank:
		keystate[VK_CAPITAL] = 0;
		if(abbrevmode || purgedicmode)
		{
			keystate[VK_KANA] = 0;
		}
		if(vkoff != 0)
		{
			keystate[vkoff] = 0;
		}
		break;
	case im_jlatin:
	case im_ascii:
		keystate[VK_KANA] = 0;
		break;
	default:
		break;
	}

	int retu = ToUnicode(vk, 0, keystate, &ubuff, 1, 0);
	if(retu == 1)
	{
		u = ubuff;
	}

	return u;
}