void CInMin::Setup()
{
	ISpecifyPropertyPages *pSpec = NULL;
	IBaseFilter* pBF = m_VideoCaptureDevice.GetIBaseFilter();
	if( pBF )
	{
		if( pBF->QueryInterface(IID_ISpecifyPropertyPages,(void **)&pSpec) == S_OK )
		{
			if( pSpec )
			{
				CAUUID cauuid;
				pSpec->GetPages(&cauuid);
				OleCreatePropertyFrame(0, 30, 30, NULL, 1, (IUnknown **)&pBF, cauuid.cElems, (GUID *)cauuid.pElems, 0, 0, NULL);
				CoTaskMemFree(cauuid.pElems);
				pSpec->Release();
			}
		}
	}
}