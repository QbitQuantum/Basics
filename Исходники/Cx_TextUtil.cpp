bool Cx_TextUtil::ToDBC(std::wstring& text, bool punct)
{
	bool changed = false;
	std::wstring dest('\0', text.size() + 1);

	if (!text.empty() && punct)
	{
		int ret = LCMapStringW(
			MAKELANGID(LANG_CHINESE, SUBLANG_CHINESE_SIMPLIFIED), 
			LCMAP_HALFWIDTH, 
			text.c_str(), text.size(), 
			&dest[0], dest.size() + 1);

		if (ret > 0 && dest != text)
		{
			text = dest;
			changed = true;
		}
	}
	else if (!text.empty())
	{
		LPCWSTR psrc = text.c_str();
		LPWSTR pdest = &dest[0];
		int i = 0, n = 0;

		for (; psrc[i] != 0; i++)
		{
			if (psrc[i] >= 0xA3B0 && psrc[i] <= 0xA3B9)		// £°..£¹
			{
				pdest[i] = WCHAR('0' + psrc[i] - 0xA3B0);
				n++;
			}
			else if (psrc[i] >= 0xA3C1 && psrc[i] <= 0xA3DA)	// £Á..£Ú
			{
				pdest[i] = WCHAR('A' + psrc[i] - 0xA3C1);
				n++;
			}
			else if (psrc[i] >= 0xA3E1 && psrc[i] <= 0xA3FA)	// £á..£ú
			{
				pdest[i] = WCHAR('a' + psrc[i] - 0xA3E1);
				n++;
			}
			else
			{
				pdest[i] = psrc[i];
			}
		}
		pdest[i] = 0;

		if (n > 0)
		{
			text = dest;
			changed = true;
		}
	}

	return changed;
}