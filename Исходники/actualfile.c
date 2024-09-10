int ActualFileRead(ACTUALHANDLE handle, int bytes, char *buffer) {

  int retval;

  DWORD bytesread;

#ifdef VERBOSE_WARNING_ACTUALFILE

  DWORD errcode;

#endif /* VERBOSE_WARNING_ACTUALFILE */



  if(handle == NULL)  return(-1);

  if(handle == INVALID_HANDLE_VALUE)  return(-1);

  if(bytes < 1)  return(-1);

  if(buffer == NULL)  return(-1);



#ifdef VERBOSE_FUNCTION_ACTUALFILE

  PrintLog("CDVDiso file: ActualFileRead(%i)", bytes);

#endif /* VERBOSE_FUNCTION_ACTUALFILE */



  retval = ReadFile(handle, buffer, bytes, &bytesread, NULL);

  if(retval == 0) {

#ifdef VERBOSE_WARNING_ACTUALFILE

    errcode = GetLastError();

    PrintLog("CDVDiso file:   Error reading from file");

    PrintError("CDVDiso file", errcode);

#endif /* VERBOSE_WARNING_ACTUALFILE */

    return(-1);

  } // ENDIF- Error? Abort

  if(bytesread < bytes) {

#ifdef VERBOSE_WARNING_ACTUALFILE

    PrintLog("CDVDiso file:   Short Block! Only read %i out of %i bytes", bytesread, bytes);

#endif /* VERBOSE_WARNING_ACTUALFILE */

  } // ENDIF- Error? Abort



  return(bytesread); // Send back how many bytes read

} // END ActualFileRead()