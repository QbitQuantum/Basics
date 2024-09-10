	INT_PTR UpDown::Create(HWND buddy,HWND parent,int nUpper,int nLower,int nPos)
	{
		if(parent==0)
			parent = GetParent(buddy);
		if(parent==0) return 0;
		DWORD style = GetWindowLong(buddy,GWL_STYLE);
		style |= ES_NUMBER;
		SetWindowLong(buddy,GWL_STYLE,style);
		_Handle = CreateUpDownControl(WS_VISIBLE|WS_CHILD|UDS_SETBUDDYINT|UDS_ALIGNRIGHT|UDS_ARROWKEYS,0,0,0,0,parent,Param->Identity,GetInstance(),buddy,nUpper,nLower,nPos);
		if(_Handle==0){
			Warning(L"UpDown.Create");
			return 0;
		}
		OnCreate.Call(this);
		_QuondamProc = ::SetWindowLongPtr(_Handle,GWLP_WNDPROC,(LONG)(LONG_PTR)_WndPointer.Procedure());
		return (INT_PTR)_Handle;
	}