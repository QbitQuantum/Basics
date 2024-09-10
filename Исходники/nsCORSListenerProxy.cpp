nsresult
nsCORSListenerProxy::StartCORSPreflight(nsIChannel* aRequestChannel,
                                        nsICorsPreflightCallback* aCallback,
                                        nsTArray<nsCString>& aUnsafeHeaders,
                                        nsIChannel** aPreflightChannel)
{
  *aPreflightChannel = nullptr;

  if (gDisableCORS) {
    LogBlockedRequest(aRequestChannel, "CORSDisabled", nullptr);
    return NS_ERROR_DOM_BAD_URI;
  }

  nsAutoCString method;
  nsCOMPtr<nsIHttpChannel> httpChannel(do_QueryInterface(aRequestChannel));
  NS_ENSURE_TRUE(httpChannel, NS_ERROR_UNEXPECTED);
  httpChannel->GetRequestMethod(method);

  nsCOMPtr<nsIURI> uri;
  nsresult rv = NS_GetFinalChannelURI(aRequestChannel, getter_AddRefs(uri));
  NS_ENSURE_SUCCESS(rv, rv);

  nsCOMPtr<nsILoadInfo> originalLoadInfo = aRequestChannel->GetLoadInfo();
  MOZ_ASSERT(originalLoadInfo, "can not perform CORS preflight without a loadInfo");
  if (!originalLoadInfo) {
    return NS_ERROR_FAILURE;
  }

  MOZ_ASSERT(originalLoadInfo->GetSecurityMode() ==
             nsILoadInfo::SEC_REQUIRE_CORS_DATA_INHERITS,
             "how did we end up here?");

  nsCOMPtr<nsIPrincipal> principal = originalLoadInfo->LoadingPrincipal();
  bool withCredentials = originalLoadInfo->GetCookiePolicy() ==
    nsILoadInfo::SEC_COOKIES_INCLUDE;

  nsPreflightCache::CacheEntry* entry =
    sPreflightCache ?
    sPreflightCache->GetEntry(uri, principal, withCredentials, false) :
    nullptr;

  if (entry && entry->CheckRequest(method, aUnsafeHeaders)) {
    aCallback->OnPreflightSucceeded();
    return NS_OK;
  }

  // Either it wasn't cached or the cached result has expired. Build a
  // channel for the OPTIONS request.

  nsCOMPtr<nsILoadInfo> loadInfo = static_cast<mozilla::LoadInfo*>
    (originalLoadInfo.get())->CloneForNewRequest();
  static_cast<mozilla::LoadInfo*>(loadInfo.get())->SetIsPreflight();

  nsCOMPtr<nsILoadGroup> loadGroup;
  rv = aRequestChannel->GetLoadGroup(getter_AddRefs(loadGroup));
  NS_ENSURE_SUCCESS(rv, rv);

  nsLoadFlags loadFlags;
  rv = aRequestChannel->GetLoadFlags(&loadFlags);
  NS_ENSURE_SUCCESS(rv, rv);

  // Preflight requests should never be intercepted by service workers and
  // are always anonymous.
  // NOTE: We ignore CORS checks on synthesized responses (see the CORS
  // preflights, then we need to extend the GetResponseSynthesized() check in
  // nsCORSListenerProxy::CheckRequestApproved()). If we change our behavior
  // here and allow service workers to intercept CORS preflights, then that
  // check won't be safe any more.
  loadFlags |= nsIChannel::LOAD_BYPASS_SERVICE_WORKER |
               nsIRequest::LOAD_ANONYMOUS;

  nsCOMPtr<nsIChannel> preflightChannel;
  rv = NS_NewChannelInternal(getter_AddRefs(preflightChannel),
                             uri,
                             loadInfo,
                             loadGroup,
                             nullptr,   // aCallbacks
                             loadFlags);
  NS_ENSURE_SUCCESS(rv, rv);

  // Set method and headers
  nsCOMPtr<nsIHttpChannel> preHttp = do_QueryInterface(preflightChannel);
  NS_ASSERTION(preHttp, "Failed to QI to nsIHttpChannel!");

  rv = preHttp->SetRequestMethod(NS_LITERAL_CSTRING("OPTIONS"));
  NS_ENSURE_SUCCESS(rv, rv);

  rv = preHttp->
    SetRequestHeader(NS_LITERAL_CSTRING("Access-Control-Request-Method"),
                     method, false);
  NS_ENSURE_SUCCESS(rv, rv);

  nsTArray<nsCString> preflightHeaders;
  if (!aUnsafeHeaders.IsEmpty()) {
    for (uint32_t i = 0; i < aUnsafeHeaders.Length(); ++i) {
      preflightHeaders.AppendElement();
      ToLowerCase(aUnsafeHeaders[i], preflightHeaders[i]);
    }
    preflightHeaders.Sort();
    nsAutoCString headers;
    for (uint32_t i = 0; i < preflightHeaders.Length(); ++i) {
      if (i != 0) {
        headers += ',';
      }
      headers += preflightHeaders[i];
    }
    rv = preHttp->
      SetRequestHeader(NS_LITERAL_CSTRING("Access-Control-Request-Headers"),
                       headers, false);
    NS_ENSURE_SUCCESS(rv, rv);
  }

  // Set up listener which will start the original channel
  RefPtr<nsCORSPreflightListener> preflightListener =
    new nsCORSPreflightListener(principal, aCallback, withCredentials,
                                method, preflightHeaders);

  rv = preflightChannel->SetNotificationCallbacks(preflightListener);
  NS_ENSURE_SUCCESS(rv, rv);

  // Start preflight
  rv = preflightChannel->AsyncOpen2(preflightListener);
  NS_ENSURE_SUCCESS(rv, rv);
  
  // Return newly created preflight channel
  preflightChannel.forget(aPreflightChannel);

  return NS_OK;
}