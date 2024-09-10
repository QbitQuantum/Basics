void WebHandler::buildResponse(HTTP::Context *_ctx) {
  if (!initialized) THROW("Not initialized");

  WebContext *ctx = dynamic_cast<WebContext *>(_ctx);
  if (!ctx) THROW("Expected WebContext");

  Connection &con = ctx->getConnection();

  // Check request method
  Request &request = con.getRequest();
  switch (request.getMethod()) {
    case RequestMethod::HTTP_GET:
    case RequestMethod::HTTP_POST:
      break;
  default: return; // We only handle GET and POST
  }

  try {
    if (!allow(*ctx)) errorPage(*ctx, StatusCode::HTTP_UNAUTHORIZED);
    else {
      URI uri = con.getRequest().getURI();
      const string &path = uri.getPath();
      if (path[path.length() - 1] == '/') uri.setPath(path + "index.html");

      // TODO sanitize path

      if (!handlePage(*ctx, con, uri))
        errorPage(*ctx, StatusCode::HTTP_NOT_FOUND);
    }

  } catch (const Exception &e) {
    StatusCode code = StatusCode::HTTP_INTERNAL_SERVER_ERROR;
    if (0 < e.getCode()) code = (StatusCode::enum_t)e.getCode();

    errorPage(*ctx, code, e.getMessage());

    LOG_ERROR(code << ": " << e);
  }

  con << flush;
}