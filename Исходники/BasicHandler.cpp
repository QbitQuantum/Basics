void server::BasicHandler::handleRequest( Poco::Net::HTTPServerRequest & request,
					  Poco::Net::HTTPServerResponse & response) {
  std::cout << "Received Request!" << std::endl;

  response.setContentType("text/txt");
  response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
  std::ostream& os = response.send();
  os << "12345 this is all pretty weird" << std::endl;
}