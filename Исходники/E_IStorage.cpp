void E_IStorage::ccom_open_root_storage (WCHAR * pwcsName, DWORD grfMode)

// Opens an existing root storage object in the file system. 
// Points pRootStorage to the opened storage object.
//    Parameters
// - pwcsName points to the pathname of the compound file to create.
// - grfMode specifies the access mode to use when opening the new 
//  storage object. Must be one of the STGM enumeration values.
{
  HRESULT hr;
  hr = StgOpenStorage (pwcsName, NULL, grfMode, 
      NULL, 0, &pStorage);
  if (hr != S_OK)
  {
    pStorage = NULL;
    com_eraise (f.c_format_message (hr), EN_COM);
  }
};