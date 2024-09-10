int main(int argc, char * const argv[]) 
{
   try
   { 
      // initialize log
      initializeSystemLog("rpostback", core::system::kLogLevelWarning);

      // read program options 
      Options& options = session::postback::options();
      ProgramStatus status = options.read(argc, argv); 
      if ( status.exit() )
         return status.exitCode() ;
      
       // determine postback uri
      std::string uri = std::string(kLocalUriLocationPrefix kPostbackUriScope) + 
                        options.command();
      
      // determine stream path
      std::string userIdentity = core::system::getenv(kRStudioUserIdentity);
      FilePath streamPath = session::local_streams::streamPath(userIdentity);

      // build postback request
      http::Request request;
      request.setMethod("POST");
      request.setUri(uri);
      request.setHeader("Accept", "*/*");
      request.setHeader("Connection", "close");
      request.setBody(options.argument());

      // send it
      http::Response response;
      Error error = http::sendRequest(streamPath, request,  &response);
      if (error)
         return exitFailure(error);
      else
         return EXIT_SUCCESS;
   }
   CATCH_UNEXPECTED_EXCEPTION
   
   // if we got this far we had an unexpected exception
   return EXIT_FAILURE ;
}