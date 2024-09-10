void _myisam_log_command(enum myisam_log_commands command, MI_INFO *info,
			 const uchar *buffert, uint length, int result)
{
  uchar buff[9];
  int error,old_errno;
  ulong pid=(ulong) GETPID();

  old_errno=my_errno;
  buff[0]=(char) command;
  mi_int2store(buff+1,info->dfile);
  mi_int4store(buff+3,pid);
  mi_int2store(buff+7,result);
  mysql_mutex_lock(&THR_LOCK_myisam);
  error=my_lock(myisam_log_file,F_WRLCK,0L,F_TO_EOF,MYF(MY_SEEK_NOT_DONE));
  (void) mysql_file_write(myisam_log_file, buff, sizeof(buff), MYF(0));
  if (buffert)
    (void) mysql_file_write(myisam_log_file, buffert, length, MYF(0));
  if (!error)
    error=my_lock(myisam_log_file,F_UNLCK,0L,F_TO_EOF,MYF(MY_SEEK_NOT_DONE));
  mysql_mutex_unlock(&THR_LOCK_myisam);
  my_errno=old_errno;
}