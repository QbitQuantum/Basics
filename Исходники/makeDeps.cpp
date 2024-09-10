  void set_args(int& argc, char**& argv) {
    argc = ccommand(&argv);
#   ifdef TARGET_IS_SELF
          if (argc == 1) {
            static char *default_args[] = {
              "", "-100", "Platform_macosx", "includeDB", 
              ":::src:Platform_mac", ":::src:includeDB"};
            argc = sizeof(default_args) / sizeof(default_args[0]);
            argv = default_args;
          }
#   endif
    SIOUXSettings.autocloseonquit  = True;
    SIOUXSettings.asktosaveonclose = False;
    
    void fatal_on_new_error();
    set_new_handler(fatal_on_new_error);
  }