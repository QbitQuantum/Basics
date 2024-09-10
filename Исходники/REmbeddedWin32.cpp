Error completeEmbeddedRInitialization(bool useInternet2)
{
   // set memory limit
   setMemoryLimit();

   // use IE proxy settings if requested
   boost::format fmt("suppressWarnings(utils::setInternet2(%1%))");
   Error error = r::exec::executeString(boost::str(fmt % useInternet2));
   if (error)
      LOG_ERROR(error);

   using boost::bind;
   using namespace r::function_hook ;
   ExecBlock block ;
   block.addFunctions()
      (bind(registerUnsupported, "loadhistory", "utils"))
      (bind(registerUnsupported, "savehistory", "utils"))
      (bind(registerUnsupported, "history", "utils"))
      (bind(registerUnsupported, "timestamp", "utils"))
      (bind(registerUnsupported, "winMenuAdd", "utils"))
      (bind(registerUnsupported, "winMenuAddItem", "utils"))
      (bind(registerUnsupported, "winMenuDel", "utils"))
      (bind(registerUnsupported, "winMenuDelItem", "utils"))
      (bind(registerUnsupported, "winMenuNames", "utils"))
      (bind(registerUnsupported, "winMenuItems", "utils"));
   return block.execute();
}