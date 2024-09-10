char* formatThroughput(float numBytes /* <=== Bytes/second */, u_char htmlFormat,
		       char* outStr, int outStrLen) {
  float numBits;
  int divider = 1000;   /* As SNMP does instead of using 1024 ntop divides for 1000 */
  char *separator;

  if(htmlFormat)
    separator = myGlobals.separator;
  else
    separator = " ";
  
  if(numBytes < 0) numBytes = 0; /* Sanity check */
  numBits = numBytes*8;

  if (numBits < divider) {
    safe_snprintf(__FILE__, __LINE__, outStr, outStrLen, "%.1f%sbit/s", numBits, separator); 
  } else if (numBits < (divider*divider)) {
    safe_snprintf(__FILE__, __LINE__, outStr, outStrLen, "%.1f%sKbit/s", ((float)(numBits)/divider), separator); 
  } else {
    safe_snprintf(__FILE__, __LINE__, outStr, outStrLen, "%.1f%sMbit/s", ((float)(numBits)/1048576), separator); 
  }

#ifdef DEBUG
  traceEvent(CONST_TRACE_INFO, "%.2f = %s", numBytes, outStr);
#endif

  return(outStr);
}