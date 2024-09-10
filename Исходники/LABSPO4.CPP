void getfileinfo(void) {
  OFSTRUCT lpReOpenBuff;
  hfFile = (HANDLE)OpenFile(szFileName, &lpReOpenBuff, NULL);

  if (hfFile == (HANDLE)HFILE_ERROR) {
    err_msg();  // exit if error
    exit(0);
  }

  GetFileInformationByHandle(hfFile, &lpFileInformation);
  FileTimeToLocalFileTime(&lpFileInformation.ftLastWriteTime, &lpLastWriteLocalTime);
  FileTimeToSystemTime(&lpLastWriteLocalTime, &lpLastWriteSystemTime);

  GetFileTime(hfFile, &lpCreationTime, &lpLastAccessTime, &lpLastWriteTime);
  FileTimeToSystemTime(&lpCreationTime, &lpSystemTime);
  lpSystemTime.wYear = 2010;
  SystemTimeToFileTime(&lpSystemTime, &lpCreationTime);
  SetFileTime(hfFile, &lpCreationTime, &lpLastAccessTime, &lpLastWriteTime);


  printf ("\n\nFile size: %d", lpFileInformation.nFileSizeLow);
  printf ("\n---LastWriteTime---");
  printtime(lpLastWriteSystemTime);
  printf ("---FileAttributes---\n");
  printattrib();
  CloseHandle(hfFile);
}