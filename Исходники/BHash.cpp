STDMETHODIMP CBHash::get_Name(BSTR *pVal)
{
	if(m_iAlgo < 0)return SetErrorInfo(s_strAlgoError);

	*pVal = ::SysAllocString(s_HashAlgos[m_iAlgo].Name);

	return S_OK;
}