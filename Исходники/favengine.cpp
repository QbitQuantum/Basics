PFAVORITELIST CFavoriteEngine::GetAllFavorites(){
  if(FAILED(CoInitialize(NULL)))
    return NULL;
  HRESULT hRet = ::SHGetMalloc(&m_pMalloc);
  if(FAILED(hRet)){
    m_pMalloc->Release();
    return NULL;
  }
  LPITEMIDLIST pidl;
  hRet = ::SHGetSpecialFolderLocation( NULL, CSIDL_FAVORITES, &pidl);
  if(FAILED(hRet)){
    m_pMalloc->Release();
    return NULL;
  }

  IShellFolder *pShellFolder = NULL;
  hRet = ::SHGetDesktopFolder (&pShellFolder);
  if (FAILED (hRet)){
    m_pMalloc->Free (pidl);
    m_pMalloc->Release ();
    return NULL;
  }

  IShellFolder *pFavFolder = NULL;
  hRet = pShellFolder->BindToObject (pidl, NULL, IID_IShellFolder, reinterpret_cast<void **>(&pFavFolder));

  long nItems = 0;
  IEnumIDList* pItems = NULL;
  hRet = pFavFolder->EnumObjects(NULL, SHCONTF_FOLDERS|SHCONTF_NONFOLDERS, &pItems);

  if(m_pFavoListRoot){
    CleanUp();
  }
  m_pFavoListRoot = new FAVORITELIST;
  ZeroMemory(m_pFavoListRoot, sizeof(FAVORITELIST));
  PFAVORITELIST pFavoListCur = GetFavorite( pFavFolder, m_pFavoListRoot, pItems);
  if (NULL != pItems){
    pItems->Release();
  }
  m_pMalloc->Free(pidl);
  m_pMalloc->Release();

  return m_pFavoListRoot;
}