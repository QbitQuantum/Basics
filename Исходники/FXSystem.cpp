// Get current drive prefix "a:", if any
// This is the same method as used in VC++ CRT.
FXString FXSystem::getCurrentDrive(){
#ifdef WIN32
  FXchar buffer[MAXPATHLEN];
  if(GetCurrentDirectoryA(MAXPATHLEN,buffer) && Ascii::isLetter((FXuchar)buffer[0]) && buffer[1]==':') return FXString(buffer,2);
#endif
  return FXString::null;
  }