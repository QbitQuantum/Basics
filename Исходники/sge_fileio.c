bool shepherd_write_pid_file(pid_t pid, dstring *errmsg)
{
   bool ret = true;
   FILE *fp = NULL;

   fp = fopen("pid", "w");
   if (fp != NULL) {
      if (fprintf(fp, pid_t_fmt"\n", pid) < 0) {
         sge_dstring_sprintf(errmsg, MSG_FILE_CANNOT_WRITE_SS, "pid", strerror(errno));
         ret = false;
      } else {
         if (fflush(fp) < 0) {
            sge_dstring_sprintf(errmsg, MSG_FILE_CANNOT_FLUSH_SS, "pid", strerror(errno));
            ret = false;
         }
      }
      FCLOSE(fp);
   } else {
      sge_dstring_sprintf(errmsg, MSG_FILE_NOOPEN_SS, "pid", strerror(errno));
      ret = false;
   }
   return ret;
FCLOSE_ERROR:
   sge_dstring_sprintf(errmsg, MSG_FILE_NOCLOSE_SS, "pid", strerror(errno));
   return false;
}