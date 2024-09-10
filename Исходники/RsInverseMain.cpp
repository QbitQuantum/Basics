int main(int argc, char** argv)
{
   try
   {
      // initialize log
      initializeSystemLog("rsinverse", core::system::kLogLevelWarning);

      // ignore SIGPIPE
      Error error = core::system::ignoreSignal(core::system::SigPipe);
      if (error)
         LOG_ERROR(error);

      // read options
      using namespace boost::program_options ;
      options_description rsinverseOptions("rsinverse");
      unsigned int windowHandle;
      std::string port, sharedSecret, sourceFile;
      int line;
      rsinverseOptions.add_options()
         ("hwnd",
            value<unsigned int>(&windowHandle),
            "hwnd of rstudio instance")
         ("port",
            value<std::string>(&port),
            "port of rstudio instance")
         ("secret",
            value<std::string>(&sharedSecret),
            "rstudio shared secret")
         ("source-file",
            value<std::string>(&sourceFile),
            "source file to navigate to")
         ("line",
            value<int>(&line),
            "line of code to navigate to");

      // define program options (allow positional specification)
      core::program_options::OptionsDescription optDesc("rsinverse");
      optDesc.commandLine.add(rsinverseOptions);
      optDesc.positionalOptions.add("hwnd", 1);
      optDesc.positionalOptions.add("port", 1);
      optDesc.positionalOptions.add("secret", 1);
      optDesc.positionalOptions.add("source-file", 1);
      optDesc.positionalOptions.add("line", 1);

      // read options
      ProgramStatus status = core::program_options::read(optDesc, argc, argv);
      if (status.exit())
         return status.exitCode();

      // activate the window
      HWND hRStudioWnd = reinterpret_cast<HWND>(windowHandle);
      if (::IsWindow(hRStudioWnd))
      {
         HWND hwndPopup = ::GetLastActivePopup(hRStudioWnd);
         if (::IsWindow(hwndPopup))
            hRStudioWnd = hwndPopup;
         ::SetForegroundWindow(hRStudioWnd);
         if (::IsIconic(hRStudioWnd))
            ::ShowWindow(hRStudioWnd, SW_RESTORE);
      }

      // we presume that the path is passed to us in the system encoding
      sourceFile = string_utils::systemToUtf8(sourceFile);

      // enocde the source file and line as a query string
      std::string requestBody;
      core::http::Fields args;
      args.push_back(std::make_pair("source-file", sourceFile));
      args.push_back(std::make_pair("line",
                                     safe_convert::numberToString(line)));
      http::util::buildQueryString(args, &requestBody);


      // determine postback uri
      std::string uri = std::string(kLocalUriLocationPrefix kPostbackUriScope) +
                       "rsinverse";

      // build postback request
      http::Request request;
      request.setMethod("POST");
      request.setUri(uri);
      request.setHeader("Accept", "*/*");
      request.setHeader("X-Shared-Secret", sharedSecret);
      request.setHeader("Connection", "close");
      request.setBody(requestBody);

      // send it
      http::Response response;
      std::string pipeName = core::system::getenv("RS_LOCAL_PEER");
      error = http::sendRequest(pipeName,
                                request,
                                http::ConnectionRetryProfile(
                                     boost::posix_time::seconds(10),
                                     boost::posix_time::milliseconds(50)),
                                &response);

      std::string exitCode = response.headerValue(kPostbackExitCodeHeader);
      return safe_convert::stringTo<int>(exitCode, EXIT_FAILURE);
   }
   CATCH_UNEXPECTED_EXCEPTION

   // if we got this far we had an unexpected exception
   return EXIT_FAILURE ;
}