AREXPORT int ArArgumentBuilder::getArgLongLongInt(size_t whichArg,
						  bool *ok) const
{
  bool isSuccess = false;
  long long ret = 0;
    
  const char *str = getArg(whichArg);

  // If the specified arg was successfully obtained...
  if (str != NULL) {
  
    int base = 10;
    // see if its a hex number
    if (strlen(str) > 2 && str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
    {
      str = &str[2];
      base = 16;
    }

    char *endPtr = NULL;
#ifndef _MSC_VER
    ret = strtoll(str, &endPtr, base);
#else
    ret = _strtoi64(str, &endPtr, base);
#endif
 
    if (endPtr[0] == '\0' && endPtr != str) {
      isSuccess = true;
    }
  } // end if valid arg

  if (ok != NULL) {
    *ok = isSuccess;
  }
  
  if (isSuccess) 
    return ret;
  else 
    return 0;

} // end method getArgInt