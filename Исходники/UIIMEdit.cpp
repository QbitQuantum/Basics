BOOL UIIMEdit::GetPicPosAndPathbyOrder(IN UInt32 nOrder, OUT UInt32& nPos, OUT CString& path)
{
	IRichEditOle* pRichEditOle = m_pRichEditOle;
	PTR_FALSE(pRichEditOle);

	REOBJECT reobj = { 0 };
	reobj.cbStruct = sizeof(REOBJECT);
	HRESULT hr = pRichEditOle->GetObject(nOrder, &reobj, REO_GETOBJ_POLEOBJ);
	if (SUCCEEDED(hr) && reobj.poleobj)
	{
		GifSmiley::IGifSmileyCtrl* lpAnimator = 0;
		hr = reobj.poleobj->QueryInterface(GifSmiley::IID_IGifSmileyCtrl, (void**)&lpAnimator);
		if (SUCCEEDED(hr) && lpAnimator)
		{
			CComBSTR  fileName;
			hr = lpAnimator->FileName(&fileName);
			if (SUCCEEDED(hr) && 0 != fileName.Length())
			{
				nPos = reobj.cp;
				path = CString(fileName.m_str);
			}
			lpAnimator->FreeImage();
			lpAnimator->Release();
		}
		reobj.poleobj->Release();
		return TRUE;
	}
	return FALSE;
}