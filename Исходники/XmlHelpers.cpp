HRESULT CXmlHelper::Initialize(IXMLDOMElement *lpRootElem)
{
  TNktComPtr<IXMLDOMElement> cCurrElem, cNextElem;
  CNktComBStr cElemAttrIdBStr, cNameBstr;
  HRESULT hRes;
  SIZE_T i;
  LONG k;

  nktMemSet(aFundTypesIndexes, 0, sizeof(aFundTypesIndexes));
  hRes = GetFirstChildElement(lpRootElem, &cCurrElem);
  if (FAILED(hRes))
    return hRes;
  while (cCurrElem != NULL)
  {
    cElemAttrIdBStr.Reset();
    hRes = GetAttributeValue(cCurrElem, L"id", &cElemAttrIdBStr);
    if (FAILED(hRes))
    {
init_on_error:
      Reset();
      return hRes;
    }
    if (cElemAttrIdBStr[0] != 0)
    {
      //add this element
      if (nIdElemMapEntriesCount >= nIdElemMapEntriesSize)
      {
        ID_ELEM_MAP_ENTRY *lpNew;

        lpNew = (ID_ELEM_MAP_ENTRY*)nktMemMalloc((nIdElemMapEntriesSize+10240)*sizeof(ID_ELEM_MAP_ENTRY));
        if (lpNew == NULL) {
          hRes = E_OUTOFMEMORY;
          goto init_on_error;
        }
        nIdElemMapEntriesSize += 10240;
        if (lpIdElemMapEntries != NULL)
        {
          nktMemCopy(lpNew, lpIdElemMapEntries, nIdElemMapEntriesCount*sizeof(ID_ELEM_MAP_ENTRY));
          nktMemFree(lpIdElemMapEntries);
        }
        lpIdElemMapEntries = lpNew;
      }
      wcsncpy_s(lpIdElemMapEntries[nIdElemMapEntriesCount].szIdW, cElemAttrIdBStr, 16);
      lpIdElemMapEntries[nIdElemMapEntriesCount].szIdW[15] = 0;
      k = GetDbObjectClass(cCurrElem, 1);
      if (k == -1)
      {
        hRes = E_OUTOFMEMORY;
        goto init_on_error;
      }
      if (k == NKT_DBOBJCLASS_Fundamental)
      {
        cNameBstr.Reset();
        hRes = GetAttributeValue(cCurrElem, L"name", &cNameBstr);
        if (FAILED(hRes))
          goto init_on_error;
        if (_wcsicmp((LPWSTR)cNameBstr, L"signed char") == 0)
          k = NKT_DBFUNDTYPE_SignedByte;
        else if (_wcsicmp((LPWSTR)cNameBstr, L"char") == 0)
          k = NKT_DBFUNDTYPE_AnsiChar;
        else if (_wcsicmp((LPWSTR)cNameBstr, L"unsigned char") == 0)
          k = NKT_DBFUNDTYPE_UnsignedByte;
        else if (_wcsicmp((LPWSTR)cNameBstr, L"short int") == 0)
          k = NKT_DBFUNDTYPE_SignedWord;
        else if (_wcsicmp((LPWSTR)cNameBstr, L"short unsigned int") == 0)
          k = NKT_DBFUNDTYPE_UnsignedWord;
        else if (_wcsicmp((LPWSTR)cNameBstr, L"int") == 0 ||
                 _wcsicmp((LPWSTR)cNameBstr, L"long int") == 0 ||
                 _wcsicmp((LPWSTR)cNameBstr, L"bool") == 0)
          k = NKT_DBFUNDTYPE_SignedDoubleWord;
        else if (_wcsicmp((LPWSTR)cNameBstr, L"unsigned int") == 0 ||
                 _wcsicmp((LPWSTR)cNameBstr, L"long unsigned int") == 0)
          k = NKT_DBFUNDTYPE_UnsignedDoubleWord;
        else if (_wcsicmp((LPWSTR)cNameBstr, L"long long int") == 0)
          k = NKT_DBFUNDTYPE_SignedQuadWord;
        else if (_wcsicmp((LPWSTR)cNameBstr, L"long long unsigned int") == 0)
          k = NKT_DBFUNDTYPE_UnsignedQuadWord;
        else if (_wcsicmp((LPWSTR)cNameBstr, L"float") == 0)
          k = NKT_DBFUNDTYPE_Float;
        else if (_wcsicmp((LPWSTR)cNameBstr, L"double") == 0)
          k = NKT_DBFUNDTYPE_Double;
        else if (_wcsicmp((LPWSTR)cNameBstr, L"long double") == 0)
          k = NKT_DBFUNDTYPE_LongDouble;
        else if (_wcsicmp((LPWSTR)cNameBstr, L"wchar_t") == 0)
          k = NKT_DBFUNDTYPE_WideChar;
        else if (_wcsicmp((LPWSTR)cNameBstr, L"void") == 0)
          k = NKT_DBFUNDTYPE_Void;
        else {
          hRes = E_FAIL;
          goto init_on_error;
        }
        aFundTypesIndexes[k-NKT_DBFUNDTYPE_MIN] = 1;
      }
      else
        k = 0;
      lpIdElemMapEntries[nIdElemMapEntriesCount].nFundamentalType = (ULONG)k;
      lpIdElemMapEntries[nIdElemMapEntriesCount].lpElem = cCurrElem;
      lpIdElemMapEntries[nIdElemMapEntriesCount].lpElem->AddRef();
      nIdElemMapEntriesCount++;
    }
    //get next element
    hRes = GetNextElement(cCurrElem, &cNextElem);
    if (FAILED(hRes))
      goto init_on_error;
    cCurrElem.Attach(cNextElem.Detach());
  }
  //fast fundamental quick check
  for (k=0; k<X_ARRAYLEN(aFundTypesIndexes); k++) {
    if (aFundTypesIndexes[k] == 0) {
      hRes = E_FAIL;
      goto init_on_error;
    }
  }
  //sort elements by id
  qsort_s(lpIdElemMapEntries, nIdElemMapEntriesCount, sizeof(ID_ELEM_MAP_ENTRY), IdElemMapEntry_Compare,
          NULL);
  //find each fundamental
  nktMemSet(aFundTypesIndexes, 0, sizeof(aFundTypesIndexes));
  for (i=0; i<nIdElemMapEntriesCount; i++)
  {
    if (lpIdElemMapEntries[i].nFundamentalType != 0)
      aFundTypesIndexes[lpIdElemMapEntries[i].nFundamentalType - NKT_DBFUNDTYPE_MIN] = i;
  }
  //fast fundamental quick check (should not happen)
  for (k=0; k<X_ARRAYLEN(aFundTypesIndexes); k++) {
    if (aFundTypesIndexes[k] == 0) {
      hRes = E_FAIL;
      goto init_on_error;
    }
  }
  return S_OK;
}