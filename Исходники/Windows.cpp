sBool sSystemOpenFileDialog(const sChar *label,const sChar *extensions,sInt flags,const sStringDesc &buffer)
{
  sChar oldpath[2048];
  OPENFILENAMEW ofn;
  sInt result=0;

  // determine default extension (=first in list)
  sString<256> defaultExt;
  defaultExt = extensions;
  sInt pipePos;
  if((pipePos = sFindFirstChar(defaultExt,'|')) != -1)
    defaultExt[pipePos] = 0;

  sChar ext[2048];
  sClear(ext);
  sChar *extp = ext;
  sInt filterindex = 0;

  if((flags & 3) == sSOF_LOAD && sFindChar(extensions,'|')>=0) // opening, more than one extension specified?
  {
    filterindex = 1;
    static const sChar allSupported[] = L"All supported extensions";
    sCopyMem(extp,allSupported,sizeof(allSupported));
    extp += sCOUNTOF(allSupported);

    // add all supported extensions
    const sChar *curExt = extensions;
    sBool first = sTRUE;

    for(;;)
    {
      while(*curExt=='|') curExt++;
      if(!*curExt) break;

      if(!first)
        *extp++ = ';';

      *extp++ = '*';
      *extp++ = '.';
      while(*curExt!='|' && *curExt)
        *extp++ = *curExt++;

      first = sFALSE;
    }

    *extp++ = 0;
  }

  for(;;)
  {
    while(*extensions=='|') extensions++;
    if(!*extensions) break;
    const sChar *ext1 = extensions;
    while(*ext1!='|' && *ext1)
      *extp++ = *ext1++;
    *extp++ = 0;
    *extp++ = '*';
    *extp++ = '.';
    while(*extensions!='|' && *extensions)
      *extp++ = *extensions++;
    *extp++ = 0;
  }

  static const sChar allFiles[] = L"All files (*.*)\0*.*\0";
  sCopyMem(extp,allFiles,sizeof(allFiles));
  extp += sCOUNTOF(allFiles);

  sSetMem(&ofn,0,sizeof(ofn));
  ofn.lStructSize = sizeof(ofn);
  ofn.hwndOwner = sHWND;
  ofn.lpstrFile = buffer.Buffer;
  ofn.nMaxFile = buffer.Size;
  ofn.lpstrFilter = ext;
  ofn.nFilterIndex = filterindex;
  ofn.lpstrTitle = label;
  ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

  if(0)     // this stuff does not work in windows any more. thanks to microsoft being so very intuitive
  {
    sString<sMAXPATH> initialdir;
    sGetCurrentDir(initialdir);
    initialdir.AddPath(buffer.Buffer);
    sChar *lastslash = 0;
    for(sInt i=0;initialdir[i];i++)
      if(initialdir[i]=='/' || initialdir[i]=='\\')
        lastslash = &initialdir[i];
    if(lastslash)
      *lastslash = 0;
    if(buffer.Buffer[0]!=0)
      ofn.lpstrInitialDir = initialdir;
  }

  if(!defaultExt.IsEmpty())
    ofn.lpstrDefExt = defaultExt;

  for(sInt i=0;buffer.Buffer[i];i++) if(buffer.Buffer[i]=='/') buffer.Buffer[i]='\\';
  sInt len = sGetStringLen(buffer.Buffer);
  if(len>0 && buffer.Buffer[len-1]=='\\') buffer.Buffer[len-1]=0;

  GetCurrentDirectoryW(sCOUNTOF(oldpath),oldpath);
  sWin32::ModalDialogActive = sTRUE;

  switch(flags & 3)
  {
  case sSOF_LOAD:
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_EXPLORER;
    if (flags&sSOF_MULTISELECT) ofn.Flags|=OFN_ALLOWMULTISELECT;
    result = GetOpenFileNameW(&ofn);
    break;
  case sSOF_SAVE:
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT | OFN_EXPLORER;
    result = GetSaveFileNameW(&ofn);
    break;
  case sSOF_DIR:
    { CoInitializeEx(0L,COINIT_APARTMENTTHREADED);
      BROWSEINFO bi;
      memset(&bi, 0, sizeof(bi));
      bi.ulFlags   = BIF_USENEWUI;
      bi.hwndOwner = GetDesktopWindow();
      bi.lpszTitle = label;

      SetActiveWindow(GetDesktopWindow());
      UpdateWindow(GetDesktopWindow());

      LPITEMIDLIST pIDL;
      pIDL = SHBrowseForFolderW(&bi);
      if(pIDL!=0L)
      { // Create a buffer to store the path, then 
        // get the path.
        sChar buffer2[_MAX_PATH] = L"\0";
        if(SHGetPathFromIDList(pIDL, buffer2) != 0)
        {
          // Set the string value.
          sCopyString(buffer,buffer2);
          result = true;
        }
        // free the item id list
        CoTaskMemFree(pIDL);
      }
    }
    break;
  default:
    result = 0;
    break;
  }

  sWin32::ModalDialogActive = sFALSE;
  SetCurrentDirectoryW(oldpath);

  for(sInt i=0;buffer.Buffer[i];i++)
    if(buffer.Buffer[i]=='\\') buffer.Buffer[i]='/';

  return result;
}