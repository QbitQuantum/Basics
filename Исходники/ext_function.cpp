Variant f_call_user_func_rpc(int _argc, CStrRef host, int port, CStrRef auth,
                             int timeout, CVarRef function,
                             CArrRef _argv /* = null_array */) {
  string url = "http://";
  url += host.data();
  url += ":";
  url += lexical_cast<string>(port);
  url += "/call_user_func_serialized?auth=";
  url += auth.data();

  Array blob = CREATE_MAP2("func", function, "args", _argv);
  String message = f_serialize(blob);

  string hostStr(host.data());
  vector<string> headers;
  LibEventHttpClientPtr http = LibEventHttpClient::Get(hostStr, port);
  if (!http->send(url, headers, timeout < 0 ? 0 : timeout, false,
                  message.data(), message.size())) {
    raise_warning("Unable to send RPC request");
    return false;
  }

  int code = http->getCode();
  if (code <= 0) {
    raise_warning("Server timed out or unable to find specified URL: %s",
                  url.c_str());
    return false;
  }

  int len = 0;
  char *response = http->recv(len);
  String sresponse(response, len, AttachString);
  if (code != 200) {
    raise_warning("Internal server error: %d %s", code,
                  HttpProtocol::GetReasonString(code));
    return false;
  }

  // This double decoding can be avoided by modifying RPC server to directly
  // take PHP serialization format.
  Variant res = f_unserialize(f_json_decode(sresponse));
  if (!res.isArray()) {
    raise_warning("Internal protocol error");
    return false;
  }

  if (res.toArray().exists("exception")) {
    throw res["exception"];
  }
  return res["ret"];
}