bool FileCreate(RAROptions *Cmd,File *NewFile,char *Name,wchar *NameW,
                OVERWRITE_MODE Mode,bool *UserReject,int64 FileSize,
                uint FileTime,bool WriteOnly)
{
  if (UserReject!=NULL)
    *UserReject=false;
#if defined(_WIN_ALL) && !defined(_WIN_CE)
  bool ShortNameChanged=false;
#endif
  while (FileExist(Name,NameW))
  {
#if defined(_WIN_ALL) && !defined(_WIN_CE)
    if (!ShortNameChanged)
    {
      // Avoid the infinite loop if UpdateExistingShortName returns
      // the same name.
      ShortNameChanged=true;

      // Maybe our long name matches the short name of existing file.
      // Let's check if we can change the short name.
      wchar WideName[NM];
      GetWideName(Name,NameW,WideName,ASIZE(WideName));
      if (UpdateExistingShortName(WideName))
      {
        if (Name!=NULL && *Name!=0)
          WideToChar(WideName,Name);
        if (NameW!=NULL && *NameW!=0)
          wcscpy(NameW,WideName);
        continue;
      }
    }
    // Allow short name check again. It is necessary, because rename and
    // autorename below can change the name, so we need to check it again.
    ShortNameChanged=false;
#endif
    if (Mode==OVERWRITE_NONE)
    {
      if (UserReject!=NULL)
        *UserReject=true;
      return(false);
    }

    // Must be before Cmd->AllYes check or -y switch would override -or.
    if (Mode==OVERWRITE_AUTORENAME)
    {
      if (!GetAutoRenamedName(Name,NameW))
        Mode=OVERWRITE_DEFAULT;
      continue;
    }

#ifdef SILENT
    Mode=OVERWRITE_ALL;
#endif

    // This check must be after OVERWRITE_AUTORENAME processing or -y switch
    // would override -or.
    if (Cmd->AllYes || Mode==OVERWRITE_ALL)
      break;

    if (Mode==OVERWRITE_DEFAULT || Mode==OVERWRITE_FORCE_ASK)
    {
      char NewName[NM];
      wchar NewNameW[NM];
      *NewNameW=0;
      eprintf(St(MFileExists),Name);
      int Choice=Ask(St(MYesNoAllRenQ));
      if (Choice==1)
        break;
      if (Choice==2)
      {
        if (UserReject!=NULL)
          *UserReject=true;
        return(false);
      }
      if (Choice==3)
      {
        Cmd->Overwrite=OVERWRITE_ALL;
        break;
      }
      if (Choice==4)
      {
        if (UserReject!=NULL)
          *UserReject=true;
        Cmd->Overwrite=OVERWRITE_NONE;
        return(false);
      }
      if (Choice==5)
      {
#ifndef GUI
        mprintf(St(MAskNewName));

#ifdef  _WIN_ALL
        File SrcFile;
        SrcFile.SetHandleType(FILE_HANDLESTD);
        int Size=SrcFile.Read(NewName,sizeof(NewName)-1);
        NewName[Size]=0;
        OemToCharA(NewName,NewName);
#else
        if (fgets(NewName,sizeof(NewName),stdin)==NULL)
        {
          // Process fgets failure as if user answered 'No'.
          if (UserReject!=NULL)
            *UserReject=true;
          return(false);
        }
#endif
        RemoveLF(NewName);
#endif
        if (PointToName(NewName)==NewName)
          strcpy(PointToName(Name),NewName);
        else
          strcpy(Name,NewName);

        if (NameW!=NULL)
        {
          if (PointToName(NewNameW)==NewNameW)
            wcscpy(PointToName(NameW),NewNameW);
          else
            wcscpy(NameW,NewNameW);
        }
        continue;
      }
      if (Choice==6)
        ErrHandler.Exit(RARX_USERBREAK);
    }
  }
  uint FileMode=WriteOnly ? FMF_WRITE|FMF_SHAREREAD:FMF_UPDATE|FMF_SHAREREAD;
  if (NewFile!=NULL && NewFile->Create(Name,NameW,FileMode))
    return(true);
  PrepareToDelete(Name,NameW);
  CreatePath(Name,NameW,true);
  return(NewFile!=NULL ? NewFile->Create(Name,NameW,FileMode):DelFile(Name,NameW));
}