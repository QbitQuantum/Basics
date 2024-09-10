IFX_LocaleMgr* FX_LocaleMgr_Create(const FX_WCHAR* pszLocalPath,
                                   FX_WORD wDefaultLCID) {
  void* pPathHandle = FX_OpenFolder(pszLocalPath);
  if (!pPathHandle) {
    return NULL;
  }
  CFX_LocaleMgr* pLocaleMgr = new CFX_LocaleMgr(wDefaultLCID);
  CFX_WideString wsFileName;
  FX_BOOL bFolder = FALSE;
  while (FX_GetNextFile(pPathHandle, wsFileName, bFolder)) {
    if (!bFolder) {
      if (wsFileName.GetLength() < 4) {
        continue;
      }
      CFX_WideString wsExt = wsFileName.Right(4);
      wsExt.MakeLower();
      if (wsExt != L".xml") {
        continue;
      }
      CFX_WideString wsFullPath(pszLocalPath);
      wsFullPath += L"\\" + wsFileName;
      IFX_FileRead* pRead = FX_CreateFileRead(wsFullPath);
      if (!pRead) {
        continue;
      }
      CXML_Element* pXmlLocale = CXML_Element::Parse(pRead);
      pRead->Release();
      CFX_ByteString bssp = pXmlLocale->GetNamespace();
      if (bssp == "http://www.foxitsoftware.com/localization") {
        CFX_WideString wsLCID = pXmlLocale->GetAttrValue("", "lcid");
        wchar_t* pEnd = NULL;
        FX_DWORD dwLCID = wcstol(wsLCID, &pEnd, 16);
        if (pLocaleMgr->m_lcid2xml.GetValueAt((void*)(uintptr_t)dwLCID)) {
          delete pXmlLocale;
        } else {
          pLocaleMgr->m_lcid2xml.SetAt((void*)(uintptr_t)dwLCID, pXmlLocale);
        }
      } else {
        delete pXmlLocale;
      }
    }
  }
  FX_CloseFolder(pPathHandle);
  return pLocaleMgr;
}