bool LogMgr::Initialize()
{
  CreateDirectoryW(L"Log", NULL);
  for(int i = 0; i < LC_Max; i++) {
    ahLog[i] = CreateFileA(aLogName[i], GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_ARCHIVE  , NULL);
  }
    //fopen_s(&afpLog[i], aLogName[i], "wt");
  return true;
}