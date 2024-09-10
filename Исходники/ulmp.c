void LMP_init(LMP_t *l, char *filename, char *mode)
{
  struct stat buf;
  struct tm   *ft;

  if ((l->filename = strdup(filename))==NULL) syserror(errno,"strdup");
  if ((l->file=fopen(l->filename, mode))==NULL) syserror(errno,l->filename);
  if (SETVBUF(l->file,NULL,_IOFBF,BUFSIZ>MYBUFSIZE?BUFSIZ:MYBUFSIZE)!=0) syserror(errno,"setvbuf");
  if (stat(l->filename,&buf)==-1) syserror(errno,l->filename);
  l->filesize=buf.st_size;
  ft=localtime(&buf.st_mtime);
  l->year=ft->tm_year;
}