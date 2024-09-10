Error initialize()
{         
   // add suspend handler
   using namespace session::module_context;
   addSuspendHandler(SuspendHandler(onSuspend, onResume));

   // subscribe to events
   using boost::bind;
   events().onClientInit.connect(bind(onClientInit));
   events().onDetectChanges.connect(bind(onDetectChanges, _1));

   return Success();
}