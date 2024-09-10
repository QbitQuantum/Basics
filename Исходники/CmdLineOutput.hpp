 virtual void version(TCLAP::CmdLineInterface& cmd) {
   std::cout << std::endl
   << cmd.getMessage() << std::endl
   << "Version: " << cmd.getVersion() << std::endl
   << std::endl;
 }