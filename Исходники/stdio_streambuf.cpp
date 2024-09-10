streamsize stdio_istreambuf::showmanyc() {
  if (feof(_M_file))
    return -1;
  else {
    int fd = _FILE_fd(_M_file);
#ifdef _STLP_WCE
   (fd); // prevent warning about unused variable
// not sure if i can mix win32 io mode with ftell but time will show
// cannot use WIN32_IO implementation since missing stat
    streamsize tmp = FTELL(_M_file);
    FSEEK(_M_file, 0, SEEK_END);
    streamoff size= FTELL(_M_file)-tmp;
    FSEEK(_M_file, tmp, SEEK_SET);
#elif defined (_STLP_USE_WIN32_IO)
    // in this case, __file_size works with Win32 fh , not libc one
    streamoff size;
    struct stat buf;
    if(FSTAT(fd, &buf) == 0 && ( _S_IFREG & buf.st_mode ) )
      size = ( buf.st_size > 0  ? buf.st_size : 0);
    else
      size = 0;
#else
    streamoff size = __file_size(fd);
#endif
    // fbp : we can use ftell as this flavour always use stdio.
    streamsize pos = FTELL(_M_file);
    return pos >= 0 && size > pos ? size - pos : 0;
  }
}