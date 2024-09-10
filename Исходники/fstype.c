w_string_t *w_fstype(const char *path)
{
#ifdef __linux__
  struct statfs sfs;
  const char *name = "unknown";

  if (statfs(path, &sfs) == 0) {
    switch (sfs.f_type) {
#ifdef CIFS_MAGIC_NUMBER
      case CIFS_MAGIC_NUMBER:
        name = "cifs";
        break;
#endif
#ifdef NFS_SUPER_MAGIC
      case NFS_SUPER_MAGIC:
        name = "nfs";
        break;
#endif
#ifdef SMB_SUPER_MAGIC
      case SMB_SUPER_MAGIC:
        name = "smb";
        break;
#endif
      default:
        name = "unknown";
    }
  }

  return w_string_new(name);
#elif STATVFS_HAS_FSTYPE_AS_STRING
  struct statvfs sfs;

  if (statvfs(path, &sfs) == 0) {
#ifdef HAVE_STRUCT_STATVFS_F_FSTYPENAME
    return w_string_new(sfs.f_fstypename);
#endif
#ifdef HAVE_STRUCT_STATVFS_F_BASETYPE
    return w_string_new(sfs.f_basetype);
#endif
  }
#elif HAVE_STATFS
  struct statfs sfs;

  if (statfs(path, &sfs) == 0) {
    return w_string_new(sfs.f_fstypename);
  }
#endif
#ifdef _WIN32
  WCHAR *wpath = w_utf8_to_win_unc(path, -1);
  w_string_t *fstype_name = NULL;
  if (wpath) {
    WCHAR fstype[MAX_PATH+1];
    HANDLE h = CreateFileW(wpath, GENERIC_READ,
        FILE_SHARE_DELETE|FILE_SHARE_READ|FILE_SHARE_WRITE,
        NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL);
    if (h) {
      if (GetVolumeInformationByHandleW(h, NULL, 0, 0, 0, 0, fstype,
            MAX_PATH+1)) {
        fstype_name = w_string_new_wchar(fstype, -1);
      }
      CloseHandle(h);
    }
    free(wpath);
  }
  if (fstype_name) {
    return fstype_name;
  }
  return w_string_new("unknown");
#else
  unused_parameter(path);
  return w_string_new("unknown");
#endif
}