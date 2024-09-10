AREXPORT FILE *ArUtil::popen(const char *command, const char *type, 
			     bool closeOnExec)
{
  FILE *file;
#ifndef WIN32
  file = ::popen(command, type);
#else
  file = _popen(command, type);
#endif
  setFileCloseOnExec(file, closeOnExec);
  return file;
}