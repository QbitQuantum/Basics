		TEXT("雏龙"),TEXT("幼龙"),TEXT("鸭嘴龙"),TEXT("双棘龙"),
		TEXT("迅龙"),TEXT("雷龙"),TEXT("甲龙"),TEXT("角龙"),
		TEXT("剑龙"),TEXT("黄金龙"),TEXT("霸王龙"),TEXT("北海冥龙"),
		TEXT("南海狂龙"),TEXT("西海魔龙"),TEXT("东海神龙"),TEXT("中华圣龙"),
	};
	for (int i=0;i<CountArray(lScoreInfo_2);i++)
	{
		if (score<lScoreInfo_2[i]) return pszOrderName_2[i];
	}
	return pszOrderName_2[17];
}

float CLogic::AssertUserPer(LONG score)
{
	LONG lScoreInfo_2[18]=
	{
		0L,50L,100L,200L,500L,800L,1200L,2000L,3000L,5000L,8000L,12000L,15000L,18000L,25000L,40000L,60000L,
	};
	for (int i=0;i<CountArray(lScoreInfo_2);i++)
	{
		if (score<lScoreInfo_2[i]&&i!=0) 
			return (float)(100.0*(score-lScoreInfo_2[i-1])/(lScoreInfo_2[i]-lScoreInfo_2[i-1]));
		else
		if (score<lScoreInfo_2[i]&&score<0&&i==0)
			return 0.0;
	}
	return 100.0;
}

void CLogic::OpenUrl(CString url)
{
	HRESULT hr;
	IWebBrowserApp* pWBApp = NULL; // Derived from IWebBrowser
	BSTR bstrURL = NULL, bstrHeaders = NULL;
	VARIANT vFlags = {0},
		vTargetFrameName = {0},
		vPostData = {0},
		vHeaders = {0};

	if (FAILED(hr = CoInitialize(NULL)))
	{
		return;
	}

	if (FAILED(hr = CoCreateInstance(CLSID_InternetExplorer,
		NULL,
		CLSCTX_SERVER,
		IID_IWebBrowserApp,
		(LPVOID*)&pWBApp)))
	{
		if (bstrURL) SysFreeString(bstrURL);
		if (bstrHeaders) SysFreeString(bstrHeaders);
		VariantClear(&vPostData);
		if (pWBApp) pWBApp->Release();
		CoUninitialize();
		return;
	}

	bstrURL = url.AllocSysString();
	if (!bstrURL)
	{
		if (bstrURL) SysFreeString(bstrURL);
		if (bstrHeaders) SysFreeString(bstrHeaders);
		VariantClear(&vPostData);
		if (pWBApp) pWBApp->Release();
		CoUninitialize();