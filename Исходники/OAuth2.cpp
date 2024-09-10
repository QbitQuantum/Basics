URI OAuth2::getVerifyURL(const URI &uri, const string &state) const {
  // Check that SID matches state (Confirm anti-forgery state token)
  if (!uri.has("code") || !uri.has("state") || uri.get("state") != state) {
    LOG_DEBUG(3, "Failed anti-forgery check: uri code="
              << (uri.has("code") ? uri.get("code") : "<null>") << " uri state="
              << (uri.has("state") ? uri.get("state") : "<null>")
              << " server state=" << state);
    THROWC("Failed anti-forgery check", Event::HTTPStatus::HTTP_UNAUTHORIZED);
  }

  // Check config
  validateOption(clientID, "client-id");
  validateOption(clientSecret, "client-secret");
  validateOption(redirectBase, "redirect-base");
  validateOption(tokenURL, "token-url");

  // Exchange code for access token and ID token
  URI postURI(tokenURL);

  // Setup Query data
  postURI.set("code", uri.get("code"));
  postURI.set("client_id", clientID);
  postURI.set("client_secret", clientSecret);
  postURI.set("redirect_uri", redirectBase + uri.getPath());
  postURI.set("grant_type", "authorization_code");

  LOG_DEBUG(5, __func__ << ": " << postURI);

  return postURI;
}