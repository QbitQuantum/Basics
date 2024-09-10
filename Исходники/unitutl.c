//--------------------------------------------------
// displays program name and final error code
// list any other errors
//--------------------------------------------------
void listStatus(const char* prog, int err)
{
  fprintf(stdout, "%s - RC: %d\n", prog, err);
  while(hasUnreadErrors()) {
    ErrorInfo* pErr = getErrorInfo();
	char* pErrStr = getErrorString(pErr->code);
    fprintf(stdout, "ERROR: %d - %s - %s\n",
	      pErr->code, pErrStr, pErr->assertion);
    
  }
}