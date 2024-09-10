Error initialize()
{
   // install rpc methods
   using boost::bind;
   using namespace module_context;
   ExecBlock initBlock ;
   initBlock.addFunctions()
      (bind(registerUriHandler, "/view_pdf", handleViewPdf))
      (bind(registerUriHandler, kPdfJsPath, handlePdfJs))
   ;
   return initBlock.execute();
}