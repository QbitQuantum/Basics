XLWordBreaker::XLWordBreaker()
{
	HRESULT hr;

	CLSID clsidWordBreaker;
	hr = CLSIDFromString(L"NLG.Japanese Wordbreaker",&clsidWordBreaker);
	if (FAILED(hr))
	{
		_com_issue_error(hr);
	}
//	hr = this->WordBreaker.CoCreateInstance(__uuidof(CLSID_IWordBreaker_WinXP));
	hr = this->WordBreaker.CoCreateInstance(clsidWordBreaker);
	if (FAILED(hr))
	{
		_com_issue_error(hr);
	}

	//初期化
	BOOL pfLicense = TRUE;
	hr = WordBreaker->Init(true, 2000, &pfLicense);
	if (FAILED(hr))
	{
		_com_issue_error(hr);
	}
}