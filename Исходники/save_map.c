static char set_date_time(char *filename, unsigned long date, unsigned long time)
  {
#if 0
  HANDLE h=CreateFile(filename,0,0,NULL,OPEN_EXISTING,0,NULL);
  FILETIME WriteTime;
  char err=0;
  if (h==NULL) return 1;
  WriteTime.dwHighDateTime=date;
  WriteTime.dwLowDateTime=time;
  err=SetFileTime(h,NULL,NULL,&WriteTime)==1;
  CloseHandle(h);
  return err;
#endif
  return 0;
  }