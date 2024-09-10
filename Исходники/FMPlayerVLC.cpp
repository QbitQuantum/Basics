HRESULT FMediaPlayerVLC_Ex::AddPlaylistItem(const tchar* pFileName, IMediaOptions* pOptions)
{
	
	if (!m_pPlaylist)
		return E_FAIL; 
	
	USES_CONVERSION;
	long pos = 0; 
	LPSAFEARRAY pSA = SafeArrayCreateVector(VT_VARIANT, 0, 1); 


	if (pOptions->m_Vout == "")
	{
		//If GetWindowsVersion() == WindowsVista => "direct3d" 
		//else "directx";
		pOptions->m_Vout = "direct3d";
	}

	FString StrVout; 
	StrVout.Format(":vout=%s;", pOptions->m_Vout); 

	FString Options = StrVout;
	
	m_bHasSubs = TRUE; 
	if (pOptions->m_SubPath.GetLength() > 0)
	{
		Options.Append(";:sub-file: ");
		Options.Append(pOptions->m_SubPath);
	}

	Options.Append(";:sub-autodetect-file;:sub-autodetect-fuzzy:3;");
	if (pOptions->rtOffset > 0)
	{
		FString StartTime; 
		StartTime.Format(";:start-time:%d;", pOptions->rtOffset / 1000); 
		Options.Append(StartTime);
	}

	_variant_t var(_bstr_t(T2OLE(Options))); 
	SafeArrayPutElement(pSA, &pos, (void FAR *)&var); 
	_variant_t v; 
	v.parray = pSA; 
	v.vt = VT_ARRAY;
	
	CComVariant vtName = L"LTV_Video";
	BSTR bStrName = SysAllocString(T2OLE(pFileName)); 
	long lId = 0; 
	m_pPlaylist->get_itemCount(&lId); 
	return m_pPlaylist->add(bStrName, vtName, v, &lId); 
}