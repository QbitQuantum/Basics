/**
 * stat a file and return the appropriate object
 * This would better be done on an open file handle
 */
int file_metadata_t::stat(const tstring &fn,
			  file_metadata_t *m,
			  class display &ocb)
{
  struct __stat64 sb;
  if (::TSTAT(fn.c_str(),&sb)) 
  {
    ocb.error_filename(fn,"%s",strerror(errno));
    return -1;
  }
  m->fileid.dev = sb.st_dev;
#ifdef _WIN32
  BY_HANDLE_FILE_INFORMATION fileinfo;
  HANDLE filehandle = CreateFile(fn.c_str(),
				 0,   // desired access
				 FILE_SHARE_READ,
				 NULL,  
				 OPEN_EXISTING,
				 (FILE_FLAG_OPEN_REPARSE_POINT | FILE_FLAG_BACKUP_SEMANTICS),
				 NULL);
  // RBF - Error check CreateFile
  (void)GetFileInformationByHandle(filehandle, &fileinfo);
  CloseHandle(filehandle);
  m->fileid.ino = (((uint64_t)fileinfo.nFileIndexHigh)<<32) | (fileinfo.nFileIndexLow);
#else
  m->fileid.ino = sb.st_ino;
#endif
  m->nlink      = sb.st_nlink;
  m->size       = sb.st_size;
  m->ctime      = sb.st_ctime;
  m->mtime      = sb.st_mtime;
  m->atime      = sb.st_atime;

  return 0;
}