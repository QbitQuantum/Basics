	bool getCodepageDescription(int codepage, String& sDescription)
	{
		wchar_t szDescription[256];
		HRESULT hr = m_pmlang->GetCodePageDescription(codepage, GetSystemDefaultLangID(), szDescription, sizeof(szDescription)/sizeof(wchar_t));
		if (FAILED(hr))
			return false;

		sDescription = ucr::toTString(szDescription);
		return true;
	}