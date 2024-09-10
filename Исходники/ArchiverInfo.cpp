void ReadArchiverInfoList(CObjectVector<CArchiverInfo> &archivers)
{
  archivers.Clear();
  
  #ifdef EXCLUDE_COM
  
  #ifdef FORMAT_7Z
  {
    CArchiverInfo item;
    item.UpdateEnabled = true;
    item.Name = L"7z";
    item.Extensions.Add(CArchiverExtInfo(L"7z"));
    #ifndef _SFX
    const unsigned char kSig[] = {'7' , 'z', 0xBC, 0xAF, 0x27, 0x1C};
    SetBuffer(item.StartSignature, kSig, 6);
    #endif
    archivers.Add(item);
  }
  #endif

  #ifdef FORMAT_BZIP2
  {
    CArchiverInfo item;
    item.UpdateEnabled = true;
    item.KeepName = true;
    item.Name = L"BZip2";
    item.Extensions.Add(CArchiverExtInfo(L"bz2"));
    item.Extensions.Add(CArchiverExtInfo(L"tbz2", L".tar"));
    #ifndef _SFX
    const unsigned char sig[] = {'B' , 'Z', 'h' };
    SetBuffer(item.StartSignature, sig, 3);
    #endif
    archivers.Add(item);
  }
  #endif

  #ifdef FORMAT_GZIP
  {
    CArchiverInfo item;
    item.UpdateEnabled = true;
    item.Name = L"GZip";
    item.Extensions.Add(CArchiverExtInfo(L"gz"));
    item.Extensions.Add(CArchiverExtInfo(L"tgz", L".tar"));
    #ifndef _SFX
    const unsigned char sig[] = { 0x1F, 0x8B };
    SetBuffer(item.StartSignature, sig, 2);
    #endif
    archivers.Add(item);
  }
  #endif

  #ifdef FORMAT_SPLIT
  {
    CArchiverInfo item;
    item.UpdateEnabled = false;
    item.KeepName = true;
    item.Name = L"Split";
    item.Extensions.Add(CArchiverExtInfo(L"001"));
    archivers.Add(item);
  }
  #endif

  #ifdef FORMAT_TAR
  {
    CArchiverInfo item;
    item.UpdateEnabled = true;
    item.Name = L"Tar";
    item.Extensions.Add(CArchiverExtInfo(L"tar"));
    archivers.Add(item);
  }
  #endif

  #ifdef FORMAT_ZIP
  {
    CArchiverInfo item;
    item.UpdateEnabled = true;
    item.Name = L"Zip";
    item.Extensions.Add(CArchiverExtInfo(L"zip"));
    #ifndef _SFX
    const unsigned char sig[] = { 0x50, 0x4B, 0x03, 0x04 };
    SetBuffer(item.StartSignature, sig, 4);
    #endif
    archivers.Add(item);
  }
  #endif

  #ifdef FORMAT_CPIO
  {
    CArchiverInfo item;
    item.Name = L"Cpio";
    item.Extensions.Add(CArchiverExtInfo(L"cpio"));
    archivers.Add(item);
  }
  #endif

  #ifdef FORMAT_RPM
  {
    CArchiverInfo item;
    item.Name = L"Rpm";
    item.Extensions.Add(CArchiverExtInfo(L"rpm", L".cpio.gz"));
    archivers.Add(item);
  }
  #endif

  #ifdef FORMAT_ARJ
  {
    CArchiverInfo item;
    item.Name = L"Arj";
    item.Extensions.Add(CArchiverExtInfo(L"arj"));
    #ifndef _SFX
    const unsigned char sig[] = { 0x60, 0xEA };
    SetBuffer(item.StartSignature, sig, 2);
    #endif
    archivers.Add(item);
  }
  #endif

  #ifdef FORMAT_Z
  {
    CArchiverInfo item;
    item.Name = L"Z";
    item.Extensions.Add(CArchiverExtInfo(L"Z"));
    #ifndef _SFX
    const unsigned char sig[] = { 0x1F, 0x9D };
    SetBuffer(item.StartSignature, sig, 2);
    #endif
    archivers.Add(item);
  }
  #endif
  
  #else

  UString folderPath = GetBaseFolderPrefixFromRegistry() + 
      (UString)kFormatFolderName + (UString)WSTRING_PATH_SEPARATOR;
  NFind::CEnumeratorW enumerator(folderPath + L"*");
  NFind::CFileInfoW fileInfo;
  while (enumerator.Next(fileInfo))
  {
    if (fileInfo.IsDirectory())
      continue;
    UString filePath = folderPath + fileInfo.Name;
    {
      NDLL::CLibrary library;
      if (!library.LoadEx(filePath, LOAD_LIBRARY_AS_DATAFILE))
        continue;
    }

    NDLL::CLibrary library;
    if (!library.Load(filePath))
      continue;
    GetHandlerPropertyFunc getHandlerProperty = (GetHandlerPropertyFunc)
        library.GetProcAddress("GetHandlerProperty");
    if (getHandlerProperty == NULL)
      continue;

    CArchiverInfo item;
    item.FilePath = filePath;
    
    NWindows::NCOM::CPropVariant prop;
    if (getHandlerProperty(NArchive::kName, &prop) != S_OK)
      continue;
    if (prop.vt != VT_BSTR)
      continue;
    item.Name = prop.bstrVal;
    prop.Clear();

    if (getHandlerProperty(NArchive::kClassID, &prop) != S_OK)
      continue;
    if (prop.vt != VT_BSTR)
      continue;
    item.ClassID = *(const GUID *)prop.bstrVal;
    prop.Clear();

    if (getHandlerProperty(NArchive::kExtension, &prop) != S_OK)
      continue;
    if (prop.vt != VT_BSTR)
      continue;

    UString ext  = prop.bstrVal;
    UString addExt;

    prop.Clear();

    if (getHandlerProperty(NArchive::kAddExtension, &prop) != S_OK)
      continue;
    if (prop.vt == VT_BSTR)
    {
      addExt = prop.bstrVal;
    }
    else if (prop.vt != VT_EMPTY)
      continue;
    prop.Clear();

    UStringVector exts, addExts;
    SplitString(ext, exts);
    SplitString(addExt, addExts);

    prop.Clear();
    for (int i = 0; i < exts.Size(); i++)
    {
      CArchiverExtInfo extInfo;
      extInfo.Ext = exts[i];
      if (addExts.Size() > 0)
        extInfo.AddExt = addExts[i];
      if (extInfo.AddExt == L"*")
        extInfo.AddExt.Empty();
      item.Extensions.Add(extInfo);
    }

    if (getHandlerProperty(NArchive::kUpdate, &prop) == S_OK)
      if (prop.vt == VT_BOOL)
        item.UpdateEnabled = VARIANT_BOOLToBool(prop.boolVal);
    prop.Clear();

    if (item.UpdateEnabled)
    {
      if (getHandlerProperty(NArchive::kKeepName, &prop) == S_OK)
        if (prop.vt == VT_BOOL)
          item.KeepName = VARIANT_BOOLToBool(prop.boolVal);
      prop.Clear();
    }

    if (getHandlerProperty(NArchive::kStartSignature, &prop) == S_OK)
    {
      if (prop.vt == VT_BSTR)
      {
        UINT len = ::SysStringByteLen(prop.bstrVal);
        item.StartSignature.SetCapacity(len);
        memmove(item.StartSignature, prop.bstrVal, len);
      }
    }
    prop.Clear();

    if (getHandlerProperty(NArchive::kAssociate, &prop) == S_OK)
      if (prop.vt == VT_BOOL)
        item.Associate = VARIANT_BOOLToBool(prop.boolVal);
    prop.Clear();


    archivers.Add(item);
  }

  #endif
}