static void Load(const CSysString &folderPrefix)
{
  NFile::NFind::CEnumerator enumerator(folderPrefix + CSysString(TEXT("*")));
  NFile::NFind::CFileInfo fileInfo;
  while (enumerator.Next(fileInfo))
  {
    if (fileInfo.IsDirectory())
      continue;
    CSysString filePath = folderPrefix + fileInfo.Name;
    {
      NDLL::CLibrary library;
      if (!library.LoadEx(filePath, LOAD_LIBRARY_AS_DATAFILE))
        continue;
    }
    NDLL::CLibrary library;
    if (!library.Load(filePath))
      continue;
    GetMethodPropertyFunc getMethodProperty = (GetMethodPropertyFunc)
        library.GetProcAddress("GetMethodProperty");
    if (getMethodProperty == NULL)
      continue;

    UInt32 numMethods = 1;
    GetNumberOfMethodsFunc getNumberOfMethodsFunc = (GetNumberOfMethodsFunc)
        library.GetProcAddress("GetNumberOfMethods");
    if (getNumberOfMethodsFunc != NULL)
      if (getNumberOfMethodsFunc(&numMethods) != S_OK)
        continue;

    for(UInt32 i = 0; i < numMethods; i++)
    {
      CMethodInfo2 info;
      info.FilePath = filePath;
      
      NWindows::NCOM::CPropVariant propVariant;
      if (getMethodProperty(i, NMethodPropID::kID, &propVariant) != S_OK)
        continue;
      if (propVariant.vt != VT_BSTR)
        continue;
      info.MethodID.IDSize = SysStringByteLen(propVariant.bstrVal);
      memmove(info.MethodID.ID, propVariant.bstrVal, info.MethodID.IDSize);
      propVariant.Clear();
      
      if (getMethodProperty(i, NMethodPropID::kName, &propVariant) != S_OK)
        continue;
      if (propVariant.vt == VT_EMPTY)
      {
      }
      else if (propVariant.vt == VT_BSTR)
        info.Name = propVariant.bstrVal;
      else
        continue;
      propVariant.Clear();
      
      if (getMethodProperty (i, NMethodPropID::kEncoder, &propVariant) != S_OK)
        continue;
      if (propVariant.vt == VT_EMPTY)
        info.EncoderIsAssigned = false;
      else if (propVariant.vt == VT_BSTR)
      {
        info.EncoderIsAssigned = true;
        info.Encoder = *(const GUID *)propVariant.bstrVal;
      }
      else
        continue;
      propVariant.Clear();
      
      if (getMethodProperty (i, NMethodPropID::kDecoder, &propVariant) != S_OK)
        continue;
      if (propVariant.vt == VT_EMPTY)
        info.DecoderIsAssigned = false;
      else if (propVariant.vt == VT_BSTR)
      {
        info.DecoderIsAssigned = true;
        info.Decoder = *(const GUID *)propVariant.bstrVal;
      }
      else
        continue;
      propVariant.Clear();
      
      if (getMethodProperty (i, NMethodPropID::kInStreams, &propVariant) != S_OK)
        continue;
      if (propVariant.vt == VT_EMPTY)
        info.NumInStreams = 1;
      else if (propVariant.vt == VT_UI4)
        info.NumInStreams = propVariant.ulVal;
      else
        continue;
      propVariant.Clear();
      
      if (getMethodProperty (i, NMethodPropID::kOutStreams, &propVariant) != S_OK)
        continue;
      if (propVariant.vt == VT_EMPTY)
        info.NumOutStreams = 1;
      else if (propVariant.vt == VT_UI4)
        info.NumOutStreams = propVariant.ulVal;
      else
        continue;
      propVariant.Clear();
      
      g_Methods.Add(info);
    }
  }
}