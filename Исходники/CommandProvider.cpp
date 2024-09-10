STDMETHODIMP CExplorerCommand::GetToolTip(IShellItemArray* psiItemArray, LPWSTR* ppszInfotip)
{
   CComBSTR bstrMenuText;
   bstrMenuText.LoadString(m_mii.wID);
   if( bstrMenuText.Length() == 0 ) return E_FAIL;
   LPCWSTR pSep = wcschr(bstrMenuText, '\n');
   if( pSep == NULL ) return E_FAIL;
   return ::SHStrDupW(pSep + 1, ppszInfotip);
}