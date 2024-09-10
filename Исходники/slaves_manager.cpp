Future<HttpResponse> SlavesManager::deactivate(const HttpRequest& request)
{
  // Parse the query to get out the slave hostname and port.
  string hostname = "";
  uint16_t port = 0;

  map<string, vector<string> > pairs =
    strings::pairs(request.query, ",", "=");

  // Make sure there is at least a 'hostname=' and 'port='.
  if (pairs.count("hostname") == 0) {
    LOG(WARNING) << "Slaves manager expecting 'hostname' in query string"
                 << " when trying to deactivate a slave";
    return HttpNotFoundResponse();
  } else if (pairs.count("port") == 0) {
    LOG(WARNING) << "Slaves manager expecting 'port' in query string"
                 << " when trying to deactivate a slave";
    return HttpNotFoundResponse();
  }

  hostname = pairs["hostname"].front();

  // Check that 'port' is valid.
  try {
    port = lexical_cast<uint16_t>(pairs["port"].front());
  } catch (const bad_lexical_cast&) {
    LOG(WARNING) << "Slaves manager failed to parse 'port = "
		 << pairs["port"].front()
                 << "'  when trying to deactivate a slave";
    return HttpNotFoundResponse();
  }

  LOG(INFO) << "Slaves manager received HTTP request to deactivate slave at "
	    << hostname << ":" << port;

  if (deactivate(hostname, port)) {
    return HttpOKResponse();
  } else {
    return HttpInternalServerErrorResponse();
  }
}