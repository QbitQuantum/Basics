char*
SIPClient::createAuthenticatorString(Authenticator const* authenticator,
				      char const* cmd, char const* url) {
  if (authenticator != NULL && authenticator->realm() != NULL
      && authenticator->nonce() != NULL && authenticator->username() != NULL
      && authenticator->password() != NULL) {
    // We've been provided a filled-in authenticator, so use it:
    char const* const authFmt
      = "Proxy-Authorization: Digest username=\"%s\", realm=\"%s\", nonce=\"%s\", response=\"%s\", uri=\"%s\"\r\n";
    char const* response = authenticator->computeDigestResponse(cmd, url);
    unsigned authBufSize = strlen(authFmt)
      + strlen(authenticator->username()) + strlen(authenticator->realm())
      + strlen(authenticator->nonce()) + strlen(url) + strlen(response);
    char* authenticatorStr = new char[authBufSize];
    sprintf(authenticatorStr, authFmt,
	    authenticator->username(), authenticator->realm(),
	    authenticator->nonce(), response, url);
    authenticator->reclaimDigestResponse(response);

    return authenticatorStr;
  }

  return strDup("");
}