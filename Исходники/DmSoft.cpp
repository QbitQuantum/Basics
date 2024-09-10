DmSoft::DmSoft(){
	WinExec("regsvr32 /s dm.dll", SW_HIDE);
	//?注册
	CoInitialize(NULL);
	CLSID clsid;
	//?利用“根名称.类名”获取CLSID，&就是把指针给函数，也就是传址
	HRESULT hr = CLSIDFromProgID(OLESTR("dm.dmsoft"), &clsid);
	dmSoft.CreateDispatch(clsid);
}