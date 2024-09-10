void DefaultRequestHandler(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
{
  response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_OK);
  response.setContentType(Poco::Net::MediaType("text/plain"));
  response.setKeepAlive(true);
  auto& os = response.send();

  os << "It Works! " << request.getURI() << std::flush;
}