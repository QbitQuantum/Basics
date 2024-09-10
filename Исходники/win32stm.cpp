void ExtractStreams(Archive &Arc,const wchar *FileName,bool TestMode)
{
  wchar FullName[NM+2];
  if (FileName[0]!=0 && FileName[1]==0)
  {
    wcscpy(FullName,L".\\");
    wcsncpyz(FullName+2,FileName,ASIZE(FullName)-2);
  }
  else
    wcsncpyz(FullName,FileName,ASIZE(FullName));

  byte *Data=&Arc.SubHead.SubData[0];
  size_t DataSize=Arc.SubHead.SubData.Size();

  wchar StreamName[NM];
  GetStreamNameNTFS(Arc,StreamName,ASIZE(StreamName));
  if (*StreamName!=':')
  {
    uiMsg(UIERROR_STREAMBROKEN,Arc.FileName,FileName);
    ErrHandler.SetErrorCode(RARX_CRC);
    return;
  }

  if (TestMode)
  {
    Arc.ReadSubData(NULL,NULL);
    return;
  }

  wcsncatz(FullName,StreamName,ASIZE(FullName));

  FindData fd;
  bool Found=FindFile::FastFind(FileName,&fd);

  if ((fd.FileAttr & FILE_ATTRIBUTE_READONLY)!=0)
    SetFileAttr(FileName,fd.FileAttr & ~FILE_ATTRIBUTE_READONLY);
  File CurFile;
  if (CurFile.WCreate(FullName) && Arc.ReadSubData(NULL,&CurFile))
    CurFile.Close();
  File HostFile;
  if (Found && HostFile.Open(FileName,FMF_OPENSHARED|FMF_UPDATE))
    SetFileTime(HostFile.GetHandle(),&fd.ftCreationTime,&fd.ftLastAccessTime,
                &fd.ftLastWriteTime);

  // Restoring original file attributes. Important if file was read only
  // or did not have "Archive" attribute
  SetFileAttr(FileName,fd.FileAttr);
}