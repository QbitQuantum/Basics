Error initialize()
{
   // subscribe to events
   using boost::bind;
   using namespace module_context;

   events().onPackageLoaded.connect(onPackageLoaded);

   ExecBlock initBlock ;
   initBlock.addFunctions()
      (bind(registerRpcMethod, "get_function_sync_state", getFunctionSyncState))
      (bind(sourceModuleRFile, "SessionBreakpoints.R"));

   return initBlock.execute();
}