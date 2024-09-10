void ofxWebServerBaseRouteHandler::sendErrorResponse(HTTPServerResponse& response) {
    // we will assume that the sender has set the status and
    // reason appropriately before calling the sendErrorResponse()
    
    HTTPResponse::HTTPStatus status = response.getStatus();
    string reason = response.getReason();
    response.setChunkedTransferEncoding(true);
    response.setContentType("text/html");
    std::ostream& ostr = response.send(); // get output stream
    ostr << "<html>";
    ostr << "<head><title>" << status << "-" << reason << "</title></head>";
    ostr << "<body>";
    ostr << "<h1>" << status << "-" << reason << "</h1>";
    ostr << "</body>";
    ostr << "<html>";
}