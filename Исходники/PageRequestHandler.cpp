 void PageRequestHandler::handleRequest(HTTPServerRequest &req, HTTPServerResponse &resp) {
   resp.setStatus(HTTPResponse::HTTP_OK);
   // std::cout << Poco::format("Received request %s", req.getURI()) << std::endl;
   string fileName = req.getURI() == "/" ? "index.html" : (req.getURI().substr(1));
   
   if (stringEndsWith(fileName, ".html")) {
     resp.setContentType("text/html");
   } else if (stringEndsWith(fileName, ".css")) {
     resp.setContentType("text/css");
   } else if (stringEndsWith(fileName, ".js")) {
     resp.setContentType("application/javascript");
   } else if (stringEndsWith(fileName, ".woff")) {
     resp.setContentType("font/woff");
   } else {
     resp.setContentType("text/html");
   }
   FileInputStream input(fileName);
   StreamCopier::copyStream(input, resp.send());
 }