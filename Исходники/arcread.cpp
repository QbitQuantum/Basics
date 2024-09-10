int PluginClass::GetFindData(PluginPanelItem **pPanelItem,int *pItemsNumber,int OpMode)
{
  HANDLE ArcFindHandle;
  WIN32_FIND_DATA NewArcFindData;
  ArcFindHandle=FindFirstFile(ArcName,&NewArcFindData);
  FindClose(ArcFindHandle);

  if (ArcFindHandle==INVALID_HANDLE_VALUE)
    return FALSE;

  if (CompareFileTime(&NewArcFindData.ftLastWriteTime,&ArcFindData.ftLastWriteTime)!=0 ||
      NewArcFindData.nFileSizeLow!=ArcFindData.nFileSizeLow || ArcData==NULL)
  {
    BOOL ReadArcOK=FALSE;
    DWORD size = (DWORD)Info.AdvControl(Info.ModuleNumber,ACTL_GETPLUGINMAXREADDATA,(void *)0);
    HANDLE h=CreateFile(ArcName, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
    if (h!=INVALID_HANDLE_VALUE)
    {
      unsigned char *Data=new unsigned char[size];
      DWORD read;
      int ret = ReadFile(h, Data, size, &read, 0);
      CloseHandle(h);
      if (Data && ret)
      {
        DWORD SFXSize;
        if (ArcPlugin->IsArchive(ArcPluginNumber, ArcName, Data, read, &SFXSize))
        {
          ReadArcOK=ReadArchive(ArcName);
        }
      }
      delete[] Data;
    }
    if (!ReadArcOK) return FALSE;
  }
  int CurDirLength=lstrlen(CurDir);
  *pPanelItem=NULL;
  *pItemsNumber=0;
  int AlocatedItemsNumber=0;
  for (int I=0;I<ArcDataCount;I++)
  {
    char Name[NM];
    PluginPanelItem CurItem=ArcData[I];
    BOOL Append=FALSE;
    lstrcpy(Name,CurItem.FindData.cFileName);

    if (Name[0]=='\\')
      Append=TRUE;

    if (Name[0]=='.' && (Name[1]=='\\' || (Name[1]=='.' && Name[2]=='\\')))
      Append=TRUE;

    if (!Append && lstrlen(Name)>CurDirLength && FSF.LStrnicmp(Name,CurDir,CurDirLength)==0 && (CurDirLength==0 || Name[CurDirLength]=='\\'))
    {
      char *StartName,*EndName;
      StartName=Name+CurDirLength+(CurDirLength!=0);

      if ((EndName=strchr(StartName,'\\'))!=NULL)
      {
        *EndName=0;
        CurItem.FindData.dwFileAttributes=FILE_ATTRIBUTE_DIRECTORY;
        CurItem.FindData.nFileSizeLow=CurItem.PackSize=0;
      }

      lstrcpy(CurItem.FindData.cFileName,StartName);
      Append=TRUE;

      if (CurItem.FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
      {
        for (int J=0; J < *pItemsNumber; J++)
          if ((*pPanelItem)[J].FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            if (FSF.LStricmp(CurItem.FindData.cFileName,(*pPanelItem)[J].FindData.cFileName)==0)
            {
              Append=FALSE;
              (*pPanelItem)[J].FindData.dwFileAttributes |= CurItem.FindData.dwFileAttributes;
            }
      }
    }

    if (Append)
    {
      PluginPanelItem *NewPanelItem=*pPanelItem;
      if (*pItemsNumber>=AlocatedItemsNumber)
      {
        AlocatedItemsNumber=AlocatedItemsNumber+256+AlocatedItemsNumber/4;
        NewPanelItem=(PluginPanelItem *)realloc(*pPanelItem,AlocatedItemsNumber*sizeof(PluginPanelItem));

        if (NewPanelItem==NULL)
          break;

        *pPanelItem=NewPanelItem;
      }
      NewPanelItem[*pItemsNumber]=CurItem;
      (*pItemsNumber)++;
    }
  }
  if (*pItemsNumber>0)
    *pPanelItem=(PluginPanelItem *)realloc(*pPanelItem,*pItemsNumber*sizeof(PluginPanelItem));
  return TRUE;
}