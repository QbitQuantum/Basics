/*
 * Open the given com port and reset the attached cm17a
 */
int Cm17aStart(int comPortNumber)
{
  char comPortString[80] ;

  sprintf(comPortString, "\\\\.\\COM%d", comPortNumber) ;

  thePort = CreateFile(comPortString, GENERIC_READ | GENERIC_WRITE,
      0, NULL, OPEN_EXISTING, FILE_FLAG_WRITE_THROUGH, NULL) ;

  if (thePort != INVALID_HANDLE_VALUE)
  {
    /* Reset the device */
    EscapeCommFunction(thePort, CLRDTR) ;
    EscapeCommFunction(thePort, CLRRTS) ;
    Sleep(DELAY) ;
    EscapeCommFunction(thePort, SETDTR) ;
    EscapeCommFunction(thePort, SETRTS) ;
    Sleep(DELAY) ;

    return 1 ;
  }
  else
    return 0 ;
}