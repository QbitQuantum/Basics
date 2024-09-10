Webbrowser::Webbrowser(void):
	_refNum(0),
	//_rcWebWnd(0),
	_bInPlaced(false),
	_bExternalPlace(false),
	_bCalledCanInPlace(false),
	_bWebWndInited(false),
	_pOleObj(NULL), 
	_pInPlaceObj(NULL), 
	_pStorage(NULL), 
	_pWB2(NULL), 
	_pHtmlDoc2(NULL), 
	_pHtmlDoc3(NULL), 
	_pHtmlWnd2(NULL), 
	_pHtmlEvent(NULL)
{
	::memset( (PVOID)&_rcWebWnd,0,sizeof(_rcWebWnd));
	HRTEST_SE( OleInitialize(0),L"Failed in Initialize Ole");
	HRTEST_SE( StgCreateDocfile(0,STGM_READWRITE | STGM_SHARE_EXCLUSIVE | STGM_DIRECT | STGM_CREATE,0,&_pStorage),L"ERROR:StgCreateDocfile");
	HRTEST_SE( OleCreate(CLSID_WebBrowser,IID_IOleObject,OLERENDER_DRAW,0,this,_pStorage,(void**)&_pOleObj),L"Create Ole Failed");
	HRTEST_SE( _pOleObj->QueryInterface(IID_IOleInPlaceObject,(LPVOID*)&_pInPlaceObj),L"Create OleInPlaceObject Failed");
	GetWebBrowser2();
	OleUninitialize();
RETURN:

	return;
}