int MmapFile::open(const char* fileName) {
  int filedes = ::open(fileName, O_RDONLY);
  if (filedes < 0) {
    REprintf("Cannot open file");
    // exit(1);
    return -1;
  }
  this->fileSize = ::getFileSize(fileName);
  if (data) {
    this->close();
  }
#ifndef _WIN32
  this->data = mmap(0, this->fileSize, PROT_READ, MAP_SHARED, filedes, 0);
  if (this->data == MAP_FAILED) {
    REprintf("mmap() failed!");
    // exit(1);
    return -1;
  }
#else
  // see:
  // http://courses.washington.edu/hypertxt/cwb/cl/windows-mmap.c
  // https://docs.microsoft.com/en-us/windows/desktop/api/winbase/nf-winbase-createfilemappinga
  this->handle = CreateFileMapping(
      (HANDLE)_get_osfhandle(filedes),
      NULL,  //  the file mapping object gets a default security descriptor
      PAGE_READONLY,  // can also be PAGE_WRITECOPY,
      0,  // dwMaximumSizeHigh are 0 (zero), the maximum size of the file
          // mapping object is equal to the current size of the file that hFile
          // identifies
      0,  // dwMaximumSizeLow (see above)
      NULL);  // lpName = NULL, the file mapping object is created without a
              // name.
  if (handle == NULL) {
    return -1;
  }
  this->data = MapViewOfFileEx(handle, FILE_MAP_READ,
                               0,  // dwFileOffsetHigh: The high-order DWORD of
                                   // the file offset where the view is to begin
                               0,  // dwFileOffsetLow: see above
                               this->fileSize,  // dwNumberOfBytesToMap
                               NULL);  // lpBaseAddress: A pointer to the memory
                                       // address in the calling process address
                                       // space where mapping begins.

#endif
  return 0;
}