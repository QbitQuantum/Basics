void Usage(char * pszProgramName)
{
   fprintf_s(stderr, "Usage:  %s\n", pszProgramName);
   fprintf_s(stderr, " -p protocol_sequence (default is '%s')\n", DEFAULT_PROTOCOL_SEQUENCE);
   fprintf_s(stderr, " -e endpoint (default is '%s')\n", DEFAULT_ENDPOINT); 
   fprintf_s(stderr, " -a server principal name\n");   
   fprintf_s(stderr, " -m maxcalls (default is %d)\n", DEFAULT_MAX_CALLS);
   fprintf_s(stderr, " -n mincalls (default is %d)\n", DEFAULT_MIN_CALLS);
   fprintf_s(stderr, " -f flag_wait_op (default is %d)\n", DEFAULT_WAIT_FLAG);
  
   exit(1);
}