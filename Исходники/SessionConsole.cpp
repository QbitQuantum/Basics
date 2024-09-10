Error initialize()
{    
   if (!session::options().verifyInstallation())
   {
      // capture standard streams
      Error error = initializeOutputCapture();
      if (error)
         return error;
   }
   
   // subscribe to events
   using boost::bind;
   using namespace module_context;
   events().onClientInit.connect(bind(onClientInit));
   events().onDetectChanges.connect(bind(onDetectChanges, _1));

   // more initialization 
   using boost::bind;
   ExecBlock initBlock ;
   initBlock.addFunctions()
      (bind(sourceModuleRFile, "SessionConsole.R"))
      (bind(registerRpcMethod, "reset_console_actions", resetConsoleActions));

   return initBlock.execute();
}