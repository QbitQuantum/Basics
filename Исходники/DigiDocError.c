//--------------------------------------------------
// Checks DigiDoc library internal errors
//--------------------------------------------------
EXP_OPTION int checkDigiDocErrors()
{
  char *errorClass[] = {"NO_ERRORS", "TECHNICAL", "USER", "LIBRARY"};
  int err = ERR_OK;
  while(hasUnreadErrors()) {
    ErrorInfo* pErr = getErrorInfo();
    char* pErrStr = getErrorString(pErr->code);
    printf("Error: %d - %s; file: %s line: %d; failed condition: %s, error class : %s\n",
	   pErr->code, pErrStr, pErr->fileName, pErr->line, pErr->assertion, errorClass[getErrorClass(pErr->code)]);
    err = pErr->code;
  }
  clearErrors();
  return err;
}