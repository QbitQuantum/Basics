value onlyWin32_getFileInformationByHandle_ml(value handle_v)
{
  HANDLE handle = (HANDLE)handle_v;
  BY_HANDLE_FILE_INFORMATION fileInfo;
  CAMLparam0 ();
  CAMLlocal1 (v);
  ULARGE_INTEGER size, index;

  if( !GetFileInformationByHandle(handle, &fileInfo) ){
    DWORD err = GetLastError();
    win32_maperr(err);
    uerror("GetFileInformationByHandle", Nothing);
  }

  size.HighPart = fileInfo.nFileSizeHigh;
  size.LowPart = fileInfo.nFileSizeLow;
  index.HighPart = fileInfo.nFileIndexHigh;
  index.LowPart = fileInfo.nFileIndexLow;

  v = caml_alloc (8, 0);
  Store_field(v,0, Val_int(fileInfo.dwFileAttributes));
  Store_field(v, 1,
              caml_copy_double(FileTime_to_POSIX(fileInfo.ftCreationTime)));
  Store_field(v, 2,
              caml_copy_double(FileTime_to_POSIX(fileInfo.ftLastAccessTime)));
  Store_field(v, 3,
              caml_copy_double(FileTime_to_POSIX(fileInfo.ftLastWriteTime)));
  Store_field(v, 4, Val_int(fileInfo.dwVolumeSerialNumber));
  Store_field(v, 5, caml_copy_int64(size.QuadPart));
  Store_field(v, 6, Val_int(fileInfo.nNumberOfLinks));
  Store_field(v, 7, caml_copy_int64(index.QuadPart));

  CAMLreturn (v);
}