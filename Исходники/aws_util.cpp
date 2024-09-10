std::shared_ptr<Aws::Http::HttpResponse> NetlibHttpClient::MakeRequest(
    Aws::Http::HttpRequest& request,
    Aws::Utils::RateLimits::RateLimiterInterface* readLimiter,
    Aws::Utils::RateLimits::RateLimiterInterface* writeLimiter) const {
  // AWS allows rate limiters to be passed around, but we are doing rate
  // limiting on the logger plugin side and so don't implement this.
  if (readLimiter != nullptr || writeLimiter != nullptr) {
    LOG(WARNING) << "Read/write limiters are unsupported";
  }

  Aws::Http::URI uri = request.GetUri();
  uri.SetPath(Aws::Http::URI::URLEncodePath(uri.GetPath()));
  Aws::String url = uri.GetURIString();

  bn::http::client client = TLSTransport().getClient();
  bn::http::client::request req(url);

  for (const auto& requestHeader : request.GetHeaders()) {
    req << bn::header(requestHeader.first, requestHeader.second);
  }

  std::string body;
  if (request.GetContentBody()) {
    std::stringstream ss;
    ss << request.GetContentBody()->rdbuf();
    body = ss.str();
  }

  auto response = std::make_shared<Standard::StandardHttpResponse>(request);
  try {
    bn::http::client::response resp;

    switch (request.GetMethod()) {
    case Aws::Http::HttpMethod::HTTP_GET:
      resp = client.get(req);
      if (resp.status() == 301 || resp.status() == 302) {
        VLOG(1) << "Attempting custom redirect as cpp-netlib does not support "
                   "redirects";
        for (const auto& header : resp.headers()) {
          if (header.first == "Location") {
            req.uri(header.second);
            resp = client.get(req);
          }
        }
      }
      break;
    case Aws::Http::HttpMethod::HTTP_POST:
      resp = client.post(req, body, request.GetContentType());
      break;
    case Aws::Http::HttpMethod::HTTP_PUT:
      resp = client.put(req, body, request.GetContentType());
      break;
    case Aws::Http::HttpMethod::HTTP_HEAD:
      resp = client.head(req);
      break;
    case Aws::Http::HttpMethod::HTTP_PATCH:
      LOG(ERROR) << "cpp-netlib does not support HTTP PATCH";
      return nullptr;
      break;
    case Aws::Http::HttpMethod::HTTP_DELETE:
      resp = client.delete_(req);
      break;
    default:
      LOG(ERROR) << "Unrecognized HTTP Method used: "
                 << static_cast<int>(request.GetMethod());
      return nullptr;
      break;
    }

    response->SetResponseCode(
        static_cast<Aws::Http::HttpResponseCode>(resp.status()));

    for (const auto& header : resp.headers()) {
      if (header.first == "content-type") {
        response->SetContentType(header.second);
      }
      response->AddHeader(header.first, header.second);
    }

    response->GetResponseBody() << resp.body();

  } catch (const std::exception& /*e*/) {
    LOG(ERROR) << "Exception making HTTP request to URL: " << url;
    return nullptr;
  }

  return response;
}