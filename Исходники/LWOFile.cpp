bool LWOFile::LoadFromFile(const char *strFile)
{
  // try to open file
  HANDLE hFile=CreateFileA(strFile, GENERIC_READ, FILE_SHARE_READ, NULL,
                          OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
  if(hFile==INVALID_HANDLE_VALUE)
  {
    AddError("Could not open file: " + std::string(strFile));
    return false;
  }

  // get file size
  LARGE_INTEGER LI_Size;
  if(!GetFileSizeEx(hFile,&LI_Size))
  {
    AddError("Could not get file size!");
    return false;
  }
  unsigned int iFileSize=(unsigned int)LI_Size.QuadPart;

  // allocate memory to hold the file
  char *pData=new char[iFileSize];

  // read file to memory
  DWORD iBytesRead=0;
  if(!ReadFile(hFile,pData,iFileSize,&iBytesRead,NULL) || iBytesRead!=iFileSize)
  {
    AddError("Reading file failed!");
    delete[] pData;
    CloseHandle(hFile);
    return false;
  }

  // load
  if(!LoadFromMemory(pData, iFileSize)) return false;

  delete[] pData;
  CloseHandle(hFile);
  return true;
}