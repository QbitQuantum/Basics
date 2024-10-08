int __cdecl
fstat(int _Desc,struct stat *_Stat)
{
  struct _stat64 st;
  int ret=_fstat64(_Desc,&st);
  if (ret == -1) {
    memset(_Stat,0,sizeof(struct stat));
    return -1;
  }
  /* struct stat and struct _stat64i32
     are the same for this case. */
  _Stat->st_dev=st.st_dev;
  _Stat->st_ino=st.st_ino;
  _Stat->st_mode=st.st_mode;
  _Stat->st_nlink=st.st_nlink;
  _Stat->st_uid=st.st_uid;
  _Stat->st_gid=st.st_gid;
  _Stat->st_rdev=st.st_rdev;
  _Stat->st_size=(_off_t) st.st_size;
  _Stat->st_atime=st.st_atime;
  _Stat->st_mtime=st.st_mtime;
  _Stat->st_ctime=st.st_ctime;
  return ret;
}