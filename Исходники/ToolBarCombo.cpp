STDMETHODIMP CToolBarCombo::DragEnter(LPDATAOBJECT pDataObj , DWORD grfKeyState, POINTL pt, LPDWORD pdwEffect){     
  m_pIDataObject=NULL;
  ATL::CString sText;

  FORMATETC formatDetails;     
  STGMEDIUM stmg;     

  // Let's get the text from the "clipboard"
  formatDetails.cfFormat = CF_TEXT;
  formatDetails.dwAspect = DVASPECT_CONTENT;
  formatDetails.lindex = -1;
  formatDetails.ptd = NULL;
  formatDetails.tymed = TYMED_HGLOBAL;

  if (SUCCEEDED(pDataObj->GetData(&formatDetails, &stmg)))
  {
    sText = (LPSTR)GlobalLock(stmg.hGlobal);
    GlobalUnlock(stmg.hGlobal);

    if (stmg.hGlobal != NULL) 
      ReleaseStgMedium(&stmg);             
  }

  *pdwEffect=DROPEFFECT_COPY;

  m_pIDataObject=pDataObj;     
  m_pIDataObject->AddRef();      

  return NOERROR;     
}       