bool OAuth2SessionLogin::handlePage(HTTP::WebContext &ctx, ostream &stream,
                                    const URI &uri) {
  HTTP::Connection &con = ctx.getConnection();
  HTTP::Request &request = con.getRequest();
  HTTP::Response &response = con.getResponse();

  ctx.setDynamic(); // Don't cache

  // Force secure
  if (!con.isSecure())
    THROWCS("Cannot logon via insecure port",
            HTTP::StatusCode::HTTP_UNAUTHORIZED);

  // Get session ID
  string sid = request.findCookie(sessionManager->getSessionCookie());
  if (sid.empty() && uri.has("state")) sid = uri.get("state");

  HTTP::SessionPtr session = sessionManager->findSession(ctx, sid);

  try {
    if (session.isNull() ||
        (uri.has("state") && uri.get("state") != session->getID()) ||
        (!uri.has("state") && session->getUser().empty())) {
      session = sessionManager->openSession(ctx);
      sid = session->getID();

      URI redirectURL = auth->getRedirectURL(uri.getPath(), sid);
      response.redirect(redirectURL);

    } else if (session->getUser().empty()) {
      // TODO Make sure session is not very old

      URI postURI = auth->getVerifyURL(uri, sid);
      LOG_DEBUG(5, "Token URI: " << postURI);

      // Extract query data
      string data = postURI.getQuery();
      postURI.setQuery("");

      // Verify authorization with OAuth2 server
      HTTP::Transaction tran(sslCtx);
      tran.post(postURI, data.data(), data.length(),
                "application/x-www-form-urlencoded", 1.0);

      // Read response
      tran.receiveHeader();
      JSON::ValuePtr token = JSON::Reader(tran).parse();

      LOG_DEBUG(5, "Token Response: \n" << tran.getResponse() << *token);

      // Verify token
      string accessToken = auth->verifyToken(token);

      // Get profile
      URI profileURL = auth->getProfileURL(accessToken);
      HTTP::Transaction tran2(sslCtx);
      tran2.get(profileURL);

      // Read response
      tran2.receiveHeader();
      JSON::ValuePtr profile = JSON::Reader(tran2).parse();

      // Process profile
      string email = profile->getString("email");
      if (!profile->getBoolean("email_verified"))
        THROWCS("Email not verified", HTTP::StatusCode::HTTP_UNAUTHORIZED);
      session->setUser(email);
      LOG_INFO(1, "Authorized: " << email);

      // Final redirect to remove auth parameters
      response.redirect(uri.getPath());

    } else return false; // Already authorized

    // Make sure session cookie is set
    sessionManager->setSessionCookie(ctx);

  } catch (...) {
    // Close session on error
    if (!sid.empty()) sessionManager->closeSession(ctx, sid);
    throw;
  }

  return true;
}