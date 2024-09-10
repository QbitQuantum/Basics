NS_IMETHODIMP
FontTableURIProtocolHandler::NewURI(const nsACString& aSpec,
                                    const char* aCharset, nsIURI* aBaseURI,
                                    nsIURI** aResult) {
  nsresult rv;
  nsCOMPtr<nsIURI> uri;

  // Either you got here via a ref or a fonttable: uri
  if (aSpec.Length() && aSpec.CharAt(0) == '#') {
    rv = NS_MutateURI(aBaseURI).SetRef(aSpec).Finalize(uri);
    NS_ENSURE_SUCCESS(rv, rv);
  } else {
    // Relative URIs (other than #ref) are not meaningful within the
    // fonttable: scheme.
    // If aSpec is a relative URI -other- than a bare #ref,
    // this will leave uri empty, and we'll return a failure code below.
    rv = NS_MutateURI(new mozilla::net::nsSimpleURI::Mutator())
             .SetSpec(aSpec)
             .Finalize(uri);
    NS_ENSURE_SUCCESS(rv, rv);
  }

  bool schemeIs;
  if (NS_FAILED(uri->SchemeIs(FONTTABLEURI_SCHEME, &schemeIs)) || !schemeIs) {
    NS_WARNING("Non-fonttable spec in FontTableURIProtocolHandler");
    return NS_ERROR_NOT_AVAILABLE;
  }

  uri.forget(aResult);
  return NS_OK;
}