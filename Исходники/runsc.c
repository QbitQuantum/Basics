int main (int argc, char *argv[])
{
  args_t args;
  struct stat st;
  
  #ifdef WIN
  // 
  PVOID   OldValue=NULL;
  WSADATA wsa;
  
  Wow64DisableWow64FsRedirection (&OldValue);
  WSAStartup(MAKEWORD(2,0), &wsa);
  #endif
  
  setbuf(stdout, NULL);
  setbuf(stderr, NULL);
  
  memset (&args, 0, sizeof(args));
  
  // set default parameters
  args.address   = NULL;
  args.file      = NULL;
  args.ai_family = AF_INET;
  args.port      = DEFAULT_PORT;
  args.port_nbr  = atoi(args.port);
  args.mode      = -1;
  args.tx_mode   = -1;
  args.sim       = 0;
  args.dbg       = 0;
  
  printf ("\n[ run shellcode v0.1\n");
  
  parse_args(&args, argc, argv);
  
  // check if we have file parameter and it accessible
  if (args.file!=NULL) {
    if (stat (args.file, &st)) {
      printf ("[ unable to access %s\n", args.file);
      return 0;
    } else {
      if (st.st_size > MAX_BUFSIZ) {
        printf ("[ %s exceeds MAX_BUFSIZ of %i bytes\n", args.file, MAX_BUFSIZ);
        return 0;
      }
    }
  }
  
  // if mode is executing
  if (args.mode==RSC_EXEC) {
    if (args.file!=NULL) {
      xfile(&args);
      return 0;
    } else {
      printf ("\n[ you've used -x without supplying file with -f");
      return 0;
    }
  }
  if (init_network(&args))
  {
    // if no file specified, we receive and execute data
    args.tx_mode = (args.file==NULL) ? RSC_RECV : RSC_SEND;
    
    // if mode is -1, we listen for incoming connections
    if (args.mode == -1) {
      args.mode=RSC_SERVER;
    }
    
    // if no file specified, set to receive one
    if (args.tx_mode == -1) {
      args.tx_mode=RSC_RECV;
    }
    
    if (args.mode==RSC_SERVER) {
      ssr (&args);
    } else {
      csr (&args);
    }
  }
  return 0;
}