void CEventContainer::OnChatStatus(long Handle, IUsers *pUsers, LPCTSTR bsLog)
{
	//MCTRACE(8,"[Event] OnChatStatus");
	TRACE(_T("\r\n[Event] OnChatStatus"));

	HWND hWnd = NULL;
	hWnd = m_NetLibTranslator.NLT_GetWindow(Handle);
	/// ????? Работа с окном ...
	if(IsWindow(hWnd))
	{
		NLT_Container *pContainer = new NLT_Container;
		pContainer->EventType = NLT_EChatStatus;
		pContainer->Handel  = Handle;

		HRESULT hr = pContainer->Marchaling(__uuidof(IUsers),(LPUNKNOWN)pUsers);

		pContainer->String1	= bsLog;	

		if(!pContainer->Send(hWnd))
		{
			delete pContainer;
		}
	}	
}