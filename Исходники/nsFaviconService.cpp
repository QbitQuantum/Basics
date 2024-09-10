NS_IMETHODIMP
nsFaviconService::ReplaceFaviconDataFromDataURL(nsIURI* aFaviconURI,
                                               const nsAString& aDataURL,
                                               PRTime aExpiration)
{
  NS_ENSURE_ARG(aFaviconURI);
  NS_ENSURE_TRUE(aDataURL.Length() > 0, NS_ERROR_INVALID_ARG);
  if (aExpiration == 0) {
    aExpiration = PR_Now() + MAX_FAVICON_EXPIRATION;
  }

  nsCOMPtr<nsIURI> dataURI;
  nsresult rv = NS_NewURI(getter_AddRefs(dataURI), aDataURL);
  NS_ENSURE_SUCCESS(rv, rv);

  // Use the data: protocol handler to convert the data.
  nsCOMPtr<nsIIOService> ioService = do_GetIOService(&rv);
  NS_ENSURE_SUCCESS(rv, rv);
  nsCOMPtr<nsIProtocolHandler> protocolHandler;
  rv = ioService->GetProtocolHandler("data", getter_AddRefs(protocolHandler));
  NS_ENSURE_SUCCESS(rv, rv);

  nsCOMPtr<nsILoadInfo> loadInfo =
    new mozilla::LoadInfo(nsContentUtils::GetSystemPrincipal(),
                          nullptr, // aTriggeringPrincipal
                          nullptr, // aLoadingNode
                          nsILoadInfo::SEC_NORMAL,
                          nsIContentPolicy::TYPE_IMAGE);

  nsCOMPtr<nsIChannel> channel;
  rv = protocolHandler->NewChannel2(dataURI, loadInfo, getter_AddRefs(channel));
  NS_ENSURE_SUCCESS(rv, rv);

  // Blocking stream is OK for data URIs.
  nsCOMPtr<nsIInputStream> stream;
  rv = channel->Open(getter_AddRefs(stream));
  NS_ENSURE_SUCCESS(rv, rv);

  uint64_t available64;
  rv = stream->Available(&available64);
  NS_ENSURE_SUCCESS(rv, rv);
  if (available64 == 0 || available64 > UINT32_MAX / sizeof(uint8_t))
    return NS_ERROR_FILE_TOO_BIG;
  uint32_t available = (uint32_t)available64;

  // Read all the decoded data.
  uint8_t* buffer = static_cast<uint8_t*>
                               (moz_xmalloc(sizeof(uint8_t) * available));
  if (!buffer)
    return NS_ERROR_OUT_OF_MEMORY;
  uint32_t numRead;
  rv = stream->Read(TO_CHARBUFFER(buffer), available, &numRead);
  if (NS_FAILED(rv) || numRead != available) {
    free(buffer);
    return rv;
  }

  nsAutoCString mimeType;
  rv = channel->GetContentType(mimeType);
  if (NS_FAILED(rv)) {
    free(buffer);
    return rv;
  }

  // ReplaceFaviconData can now do the dirty work.
  rv = ReplaceFaviconData(aFaviconURI, buffer, available, mimeType, aExpiration);
  free(buffer);
  NS_ENSURE_SUCCESS(rv, rv);

  return NS_OK;
}