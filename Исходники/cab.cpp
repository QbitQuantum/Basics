int WINAPI _export GetArcItem(struct PluginPanelItem *Item,struct ArcItemInfo *Info)
{
  struct CFFILE FileHeader;

  DWORD ReadSize;
  char *EndPos;
  FILETIME lft;

  if (FilesNumber-- == 0)
    return GETARC_EOF;
  if (!ReadFile(ArcHandle,&FileHeader,sizeof(FileHeader),&ReadSize,NULL)
      || ReadSize < 18)
    return GETARC_READERROR;

  EndPos = (char *)FileHeader.szName;
  while (EndPos - (char*)&FileHeader < (int)sizeof(FileHeader) && *EndPos)
    EndPos++;
  if (EndPos - (char*)&FileHeader >= (int)sizeof(FileHeader))
    return GETARC_BROKEN;

  SetFilePointer( ArcHandle, (LONG)((EndPos-(char*)&FileHeader+1) - ReadSize), NULL, FILE_CURRENT );

  EndPos = (char *)FileHeader.szName;
  while (*EndPos)
  {
    if (*EndPos == '/')
      *EndPos = '\\';
    EndPos++;
  }

  EndPos = (char *)FileHeader.szName;
  if (EndPos[ 0 ] == '\\' && EndPos[ 1 ] != '\\')
    EndPos++;

  CharToOem( EndPos, Item->FindData.cFileName );

  #define _A_ENCRYPTED 8
  Item->FindData.dwFileAttributes = FileHeader.attribs & (FILE_ATTRIBUTE_READONLY|FILE_ATTRIBUTE_SYSTEM|FILE_ATTRIBUTE_HIDDEN|FILE_ATTRIBUTE_ARCHIVE|FILE_ATTRIBUTE_DIRECTORY);
  Info->Encrypted = FileHeader.attribs & _A_ENCRYPTED;
  Item->PackSize=0;
  Item->FindData.nFileSizeLow=FileHeader.cbFile;
  DosDateTimeToFileTime(FileHeader.date,FileHeader.time,&lft);
  LocalFileTimeToFileTime(&lft,&Item->FindData.ftLastWriteTime);
  Info->UnpVer=UnpVer;
  return(GETARC_SUCCESS);
}