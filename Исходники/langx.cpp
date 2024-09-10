HRESULT STDMETHODCALLTYPE CLanguageX::get_Keywords(BSTR __RPC_FAR *pstrVal)
{
   *pstrVal = T2BSTR( m_cmLang.pszKeywords ? m_cmLang.pszKeywords : "" );
   return S_OK;
}