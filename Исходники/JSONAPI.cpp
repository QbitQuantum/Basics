bool JSONAPI::handlePage(HTTP::WebContext &ctx, ostream &stream,
                         const URI &uri) {
  if (!String::startsWith(uri.getPath(), root)) return false;

  string cmd = uri.getPath().substr(root.length());

  // Look up command
  api_t::const_iterator it = api.find(cmd);
  if (it == api.end()) return false;

  ctx.setDynamic(); // Don't cache
  HTTP::Connection &con = ctx.getConnection();

  bool jsonp = !jsonpCB.empty() && uri.has(jsonpCB);

  if (jsonp) {
    con.getResponse().setContentType("application/javascript");
    con << uri.get(jsonpCB) << '(';

  } else con.getResponse().setContentType("application/json");

  JSON::Writer writer(con, 0, !uri.has("pretty"),
                      uri.has("python_mode") ? JSON::Writer::PYTHON_MODE :
                      JSON::Writer::JSON_MODE);

  try {
    // Parse JSON data
    JSON::ValuePtr msg;

    if (con.getRequest().hasContentType() &&
        String::startsWith(con.getRequest().getContentType(),
                           "application/json")) {
      MemoryBuffer &payload = con.getPayload();
      if (payload.getFill()) msg = JSON::Reader(payload).parse();

    } else if (!uri.empty()) {
      msg = new JSON::Dict;

      for (URI::const_iterator it = uri.begin(); it != uri.end(); it++)
        msg->insert(it->first, it->second);
    }

    // Dispatch API command
    if (msg.isNull()) LOG_DEBUG(5, "JSONAPI Call: " << cmd << "()");
    else LOG_DEBUG(5, "JSONAPI Call: " << cmd << '(' << *msg << ')');
    it->second->handle(ctx, cmd, msg, writer);

    // Make sure JSON stream is complete
    writer.close();

  } catch (const Exception &e) {
    LOG_ERROR(e);

    // Clear possibly partial or invalid response
    con.clearResponseBuffer();

    // jsonp header
    if (jsonp) con << uri.get(jsonpCB) << '(';

    // Send error message
    JSON::Writer writer(con, 0, true);
    writer.beginList();
    writer.append("error");
    writer.append(e.getMessage());
    writer.endList();
    writer.close();
  }

  if (jsonp) con << ");";

  return true;
}