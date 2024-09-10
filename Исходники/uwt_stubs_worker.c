static void
lseek_work_cb(uv_work_t *req)
{
  struct req * r = req->data;
  const int fd = (int)r->buf.len;
  int64_t offset = voids_to_int64_t(&r->c);
#ifdef _WIN32
  const DWORD whence = r->offset;
  HANDLE handle = (HANDLE)(0 + _get_osfhandle(fd));
  if ( handle == INVALID_HANDLE_VALUE ){
    r->offset = UV_EBADF;
    offset = -1;
  }
  else if ( GetFileType(handle) != FILE_TYPE_DISK ){
    /*
      from: https://msdn.microsoft.com/en-us/library/windows/desktop/aa365542(v=vs.85).aspx

      "You cannot use the SetFilePointerEx function with a handle to a
      nonseeking device such as a pipe or a communications device. To
      determine the file type for hFile, use the GetFileType function."

      But it doesn't return an error for whatever reason. So I check
      it manually
    */
    r->offset = UV_ESPIPE;
    offset = -1;
  }
  else {
    LARGE_INTEGER distance_to_move;
    LARGE_INTEGER new_position;
    distance_to_move.QuadPart = offset;
    if ( SetFilePointerEx(handle,distance_to_move,&new_position,whence) ){
      offset = new_position.QuadPart;
    }
    else {
      DWORD er =  GetLastError();
      r->offset = uwt_translate_sys_error(er);
      offset = -1;
    }
  }
#else
  const int whence = r->offset;
  errno = 0;
  offset = lseek(fd,offset,whence);
  r->offset = -errno;
#endif
  int64_t_to_voids(offset,&r->c);
}