Error initialize()
{
   using boost::bind;
   using namespace module_context;
   ExecBlock initBlock ;
   initBlock.addFunctions()
      (bind(registerRpcMethod, "accept_agreement", handleAcceptAgreement))
      (bind(registerUriHandler, "/agreement", handleAgreementRequest))
   ;

   return initBlock.execute();
}