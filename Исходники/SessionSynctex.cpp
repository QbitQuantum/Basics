Error initialize()
{
   // register postback handler for sumatra pdf
#ifdef _WIN32
   std::string ignoredCommand; // assumes bash script invocation, we
                               // don't/can't use that for rsinverse
   Error error = module_context::registerPostbackHandler("rsinverse",
                                                         rsinversePostback,
                                                         &ignoredCommand);
   if (error)
      return error ;

#endif

   // install rpc methods
   using boost::bind;
   using namespace module_context;
   ExecBlock initBlock ;
   initBlock.addFunctions()
      (bind(registerRpcMethod, "apply_forward_concordance", rpcApplyForwardConcordance))
      (bind(registerRpcMethod, "apply_inverse_concordance", rpcApplyInverseConcordance))
      (bind(registerRpcMethod, "synctex_forward_search", synctexForwardSearch))
      (bind(registerRpcMethod, "synctex_inverse_search", synctexInverseSearch))
   ;
   return initBlock.execute();
}