STDMETHODIMP MailPropertyMap::get_Item(BSTR index, BSTR* pVal)
{   
   try
   {
      if(0 == index)
         throw Workshare::ArgumentNullException(_T("index"), _T("The property index may not be null."));

      if(0 == pVal)
         throw Workshare::ArgumentNullException(_T("pVal"), _T("The return buffer for the property value must be valid."));

      _bstr_t indexName(index);
      _wcslwr(indexName);

      *pVal = SysAllocString(m_map[indexName.GetBSTR()].c_str());
      return S_OK;
   }
   catch(Workshare::Exception const& e)
   {
      return AtlReportError(__uuidof(this), e.Message, __uuidof(IMailPropertyMap), e.ErrorCode);
   }
   catch(...)
   {
      return AtlReportError(__uuidof(this), L"Unexpected Error", __uuidof(IMailPropertyMap), ProcessUnhandledException());      
   }
}