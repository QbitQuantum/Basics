bool XboxServer::SendMessage(const String& message,
                             Array& ret,
                             int timeout_ms,
                             const String& host /* = "localhost" */) {
  if (isLocalHost(host)) {
    XboxTransport *job;
    {
      Lock l(s_dispatchMutex);
      if (!s_dispatcher) {
        return false;
      }

      job = new XboxTransport(message);
      job->incRefCount(); // paired with worker's decRefCount()
      job->incRefCount(); // paired with decRefCount() at below
      assert(s_dispatcher);
      s_dispatcher->enqueue(job);
    }

    if (timeout_ms <= 0) {
      timeout_ms = RuntimeOption::XboxDefaultLocalTimeoutMilliSeconds;
    }

    int code = 0;
    String response = job->getResults(code, timeout_ms);
    job->decRefCount(); // i'm done with this job

    if (code > 0) {
      ret.set(s_code, code);
      if (code == 200) {
        ret.set(s_response, unserialize_from_string(response));
      } else {
        ret.set(s_error, response);
      }
      return true;
    }

  } else { // remote

    string url = "http://";
    url += host.data();
    url += '/';
    url += RuntimeOption::XboxProcessMessageFunc;

    int timeoutSeconds = timeout_ms / 1000;
    if (timeoutSeconds <= 0) {
      timeoutSeconds = RuntimeOption::XboxDefaultRemoteTimeoutSeconds;
    }

    string hostStr(host.data());
    std::vector<std::string> headers;
    LibEventHttpClientPtr http =
      LibEventHttpClient::Get(hostStr, RuntimeOption::XboxServerPort);
    if (http->send(url, headers, timeoutSeconds, false,
                   message.data(), message.size())) {
      int code = http->getCode();
      if (code > 0) {
        int len = 0;
        char *response = http->recv(len);
        String sresponse(response, len, AttachString);
        ret.set(s_code, code);
        if (code == 200) {
          ret.set(s_response, unserialize_from_string(sresponse));
        } else {
          ret.set(s_error, sresponse);
        }
        return true;
      }
      // code wasn't correctly set by http client, treat it as not found
      ret.set(s_code, 404);
      ret.set(s_error, "http client failed");
    }
  }

  return false;
}