  BINLINE int64_t BFile::size() const {

#ifdef _MSC_VER
	  wstring n = getFullName();
	  struct _stat64 stat_buf;
	  int rc = _wstat64(n.c_str(), &stat_buf);
#else
	  string n = getFullNameUtf8();
	  struct stat stat_buf;
	  int rc = stat(n.c_str(), &stat_buf);
#endif

    return rc == 0 ? stat_buf.st_size : -1;
  }