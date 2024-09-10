void CPPTUtil::CheckBuiltInProperties(IDispatch* pX) throw (Workshare::Exception)
{
   if (0 == pX) 
      throw Workshare::Exception(_T("Invalid dispatch pointer passed in"));

   PowerPoint::_PresentationPtr  pPresentation(pX);
   IDispatchPtr spBuiltInProps = pPresentation->BuiltInDocumentProperties;

   _bstr_t bstrName = _T("");
   _bstr_t bstrValue = _T("");
   CStdString sMsg;

   PowerPoint::PpBuiltInProperty ppPropertyIndex[] = {PowerPoint::ppPropertyTitle, 
      PowerPoint::ppPropertySubject, 
      PowerPoint::ppPropertyAuthor, 
      PowerPoint::ppPropertyKeywords, 
      PowerPoint::ppPropertyComments, 
      PowerPoint::ppPropertyCategory, 
      PowerPoint::ppPropertyManager, 
      PowerPoint::ppPropertyCompany, 
      PowerPoint::ppPropertyHyperlinkBase};

   long lCount = sizeof(ppPropertyIndex)/sizeof(PowerPoint::PpBuiltInProperty);
   CStdString sErr;

   for (long lIndex = 0; lIndex < lCount; lIndex++)
   {
      HRESULT hr = CCOMDispatchHelper::GetPropertyItemValues(spBuiltInProps, ppPropertyIndex[lIndex], 
         bstrName, bstrValue);

      if (FAILED(hr))
      {
         sErr.Format(_T("CCOMDispatchHelper::GetPropertyItemValues() failed for property index, %ld - Error Code, %ld"), 
            lIndex, hr);

         throw Workshare::Com::ComException(sErr.c_str(), hr);
      }

      CStdString sTmp = bstrValue;
      sTmp.Trim();

      if(0 != sTmp.length())
      {
         sErr.Format(_T("%s not properly reset: current value is %s"), (LPCTSTR)bstrName, sTmp.c_str());
         throw Workshare::Exception(sErr.c_str());
      }
   }
}