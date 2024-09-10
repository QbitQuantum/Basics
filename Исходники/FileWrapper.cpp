int FileWrapper::scanf(const char *format, ...)
{
 va_list ap;
 int ret;

 clearerr(fp);

 va_start(ap, format);

 ret = vfscanf(fp, format, ap);

 va_end(ap);

 if(ferror(fp))
 {
  ErrnoHolder ene(errno);

  throw(MDFN_Error(ene.Errno(), _("Error reading from opened file \"%s\": %s"), path_save.c_str(), ene.StrError()));
 }

 //if(ret < 0 || ret == EOF)
 // throw(MDFN_Error(0, _("%s error on format string \"%s\""), "trio_vfscanf()", format));

 return(ret);
}