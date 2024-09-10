void llog(int level, char* fmt, ...) {
  static char dl[]="?\?//223344556677{}[]";
  va_list args;
  char s[MAX_STRING_LENGTH];

  va_start(args, fmt);
  vsprintf(s,fmt,args);
  va_end(args);
  if (level<MAX_MORT) log(s);
  else if (level>IMPLEMENTOR) logl(IMPLEMENTOR,"!!",s);
  else logl(level,(char *)(dl+2*(level-LOW_IMMORTAL)),s);
}