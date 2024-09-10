 // Define handler
 virtual void handleRequest(
   Poco::Net::HTTPServerRequest& request,
   Poco::Net::HTTPServerResponse& response) {
   {
     response.setChunkedTransferEncoding(true);
     response.setContentType("text/html");
     std::ostream& ostr = response.send();
     ostr << "<html><head><title>"
          << "My 1st POCO HTTP Server"
          << "</title></head>"
          << "<body><h1>"
          << _helloMsg
          << "</h1></body></html>";
   }
 }