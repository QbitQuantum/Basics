STDMETHODIMP CID3Field::get_Binary(BSTR *pVal)
{
	// TODO: Add your implementation code here
	if (pVal == NULL)
		return E_POINTER;
	try
	{
		*pVal = NULL;
		const uchar *pData = m_Field->GetRawBinary();
		if (pData == NULL)
			return E_FAIL;
		ID3_Frame *pFrame = ((CID3Frame*)m_FrameParent)->GetID3Frame();		
		if (pFrame->GetID() == ID3FID_PICTURE)
		{
			*pVal = _bstr_t((LPCTSTR)pData).copy();			
		}
		else
		{
			*pVal = SysAllocStringByteLen((const char *)pData,m_Field->Size());
		}
	}
	catch (...)
	{
		return Error(IDS_UNEXPECTED_ERROR, IID_IID3ComField, E_UNEXPECTED);
	}
	return S_OK;
}