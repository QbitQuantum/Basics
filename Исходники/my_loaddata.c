/* {{{ mysql_local_infile_init */
static
int mysql_local_infile_init(void **ptr, const char *filename, void *userdata)
{
  MYSQL_INFILE_INFO *info;
  int CodePage= -1;
#ifdef _WIN32
  MYSQL *mysql= (MYSQL *)userdata;
  wchar_t *w_filename= NULL;
  int Length;
#endif
  DBUG_ENTER("mysql_local_infile_init");

  info = (MYSQL_INFILE_INFO *)my_malloc(sizeof(MYSQL_INFILE_INFO), MYF(MY_ZEROFILL));
  if (!info) {
    DBUG_RETURN(1);
  }

  *ptr = info;

  info->filename = filename;

#ifdef _WIN32
  if (mysql)
    CodePage= madb_get_windows_cp(mysql->charset->csname);
#endif
  if (CodePage == -1)
  {
#ifdef _WIN32
    info->fd= sopen(info->filename, _O_RDONLY | _O_BINARY, _SH_DENYNO , _S_IREAD | _S_IWRITE);
#else
    info->fd = open(info->filename, O_RDONLY | O_BINARY, my_umask);
#endif
    my_errno= errno;
  }
#ifdef _WIN32
  else
  {
    if ((Length= MultiByteToWideChar(CodePage, 0, info->filename, (int)strlen(info->filename), NULL, 0)))
    {
      if (!(w_filename= (wchar_t *)my_malloc((Length + 1) * sizeof(wchar_t), MYF(MY_ZEROFILL))))
      {
        info->error_no= CR_OUT_OF_MEMORY;
        my_snprintf((char *)info->error_msg, sizeof(info->error_msg), 
                     ER(CR_OUT_OF_MEMORY));
        DBUG_RETURN(1);
      }
      Length= MultiByteToWideChar(CodePage, 0, info->filename, (int)strlen(info->filename), w_filename, (int)Length);
    }
    if (Length == 0)
    {
      my_free(w_filename);
      info->error_no= CR_UNKNOWN_ERROR;
      my_snprintf((char *)info->error_msg, sizeof(info->error_msg), 
                  "Character conversion error: %d", GetLastError());
      DBUG_RETURN(1);
    }
    info->fd= _wsopen(w_filename, _O_RDONLY | _O_BINARY, _SH_DENYNO , _S_IREAD | _S_IWRITE);
    my_errno= errno;
    my_free(w_filename);
  }
#endif

  if (info->fd < 0)
  {
    info->error_no = my_errno;
    my_snprintf((char *)info->error_msg, sizeof(info->error_msg), 
                EE(EE_FILENOTFOUND), filename, info->error_no);
    DBUG_RETURN(1);
  }
  DBUG_RETURN(0);
}