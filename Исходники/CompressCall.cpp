HRESULT CompressFiles(
    const UString &curDir,
    const UString &archiveName,
    const UString &archiveType,
    const UStringVector &names,
    // const UString &outFolder,
    bool email,
    bool showDialog,
    bool waitFinish)
{
  /*
  UString curDir;
  if (names.Size() > 0)
  {
    NFile::NDirectory::GetOnlyDirPrefix(names[0], curDir);
  }
  */
  UString params;
  params = Get7zGuiPath();
  params += L" a";
  params += kMapSwitch;
  // params += _fileNames[0];
  
  UInt32 extraSize = 2;
  UInt32 dataSize = 0;
  for (int i = 0; i < names.Size(); i++)
    dataSize += (names[i].Length() + 1) * sizeof(wchar_t);
  UInt32 totalSize = extraSize + dataSize;
  
  UString mappingName;
  
  CFileMapping fileMapping;
  CRandom random;
  random.Init(GetTickCount());
  for (;;)
  {
    int number = random.Generate();
    wchar_t temp[32];
    ConvertUInt64ToString(UInt32(number), temp);
    mappingName = L"7zCompressMapping";
    mappingName += temp;
    if (!fileMapping.Create(INVALID_HANDLE_VALUE, NULL,
      PAGE_READWRITE, totalSize, GetSystemString(mappingName)))
    {
      // MyMessageBox(IDS_ERROR, 0x02000605);
      return E_FAIL;
    }
    if (::GetLastError() != ERROR_ALREADY_EXISTS)
      break;
    fileMapping.Close();
  }
  
  NSynchronization::CManualResetEvent event;
  UString eventName;
  RINOK(CreateTempEvent(L"7zCompressMappingEndEvent", event, eventName));

  params += mappingName;
  params += L":";
  wchar_t string[10];
  ConvertUInt64ToString(totalSize, string);
  params += string;
  
  params += L":";
  params += eventName;

  if (!archiveType.IsEmpty())
  {
    params += kArchiveTypeSwitch;
    params += archiveType;
  }

  if (email)
    params += kEmailSwitch;

  if (showDialog)
    params += kShowDialogSwitch;

  AddLagePagesSwitch(params);

  params += kStopSwitchParsing;
  params += L" ";
  
  params += GetQuotedString(archiveName);
  
  LPVOID data = fileMapping.MapViewOfFile(FILE_MAP_WRITE, 0, totalSize);
  if (data == NULL)
  {
    // MyMessageBox(IDS_ERROR, 0x02000605);
    return E_FAIL;
  }
  try
  {
    wchar_t *curData = (wchar_t *)data;
    *curData = 0;
    curData++;
    for (int i = 0; i < names.Size(); i++)
    {
      const UString &unicodeString = names[i];
      memcpy(curData, (const wchar_t *)unicodeString ,
        unicodeString .Length() * sizeof(wchar_t));
      curData += unicodeString.Length();
      *curData++ = L'\0';
    }
    // MessageBox(0, params, 0, 0);
    RINOK(MyCreateProcess(params,
      (curDir.IsEmpty()? 0: (LPCWSTR)curDir),
      waitFinish, &event));
  }
  catch(...)
  {
    UnmapViewOfFile(data);
    throw;
  }
  UnmapViewOfFile(data);
  

  /*
  CThreadCompressMain *compressor = new CThreadCompressMain();;
  compressor->FileNames = _fileNames;
  CThread thread;
  if (!thread.Create(CThreadCompressMain::MyThreadFunction, compressor))
  throw 271824;
  */
  return S_OK;
}