req::ptr<File>
HttpStreamWrapper::open(const String& filename,
                        const String& mode,
                        int options,
                        const req::ptr<StreamContext>& context) {
  if (RuntimeOption::ServerHttpSafeMode && !is_cli_mode()) {
    return nullptr;
  }

  if (strncmp(filename.data(), "http://",  sizeof("http://")  - 1) &&
      strncmp(filename.data(), "https://", sizeof("https://") - 1)) {
    return nullptr;
  }

  Array headers;
  String method = s_GET;
  String post_data = null_string;
  String proxy_host;
  String proxy_user;
  String proxy_pass;
  int proxy_port = -1;
  int max_redirs = 20;
  int timeout = -1;
  bool ignore_errors = false;

  if (context && !context->getOptions().isNull() &&
      !context->getOptions()[s_http].isNull()) {
    Array opts = context->getOptions()[s_http].toArray();
    if (opts.exists(s_method)) {
      method = opts[s_method].toString();
    }
    if (opts.exists(s_header)) {
      Array lines;
      if (opts[s_header].isString()) {
        lines = StringUtil::Explode(
          opts[s_header].toString(), "\r\n").toArray();
      } else if (opts[s_header].isArray()) {
        lines = opts[s_header];
      }

      for (ArrayIter it(lines); it; ++it) {
        Array parts = StringUtil::Explode(
          it.second().toString(), ":", 2).toArray();
        headers.set(parts.rvalAt(0), parts.rvalAt(1));
      }
    }
    if (opts.exists(s_user_agent) && !headers.exists(s_User_Agent)) {
      headers.set(s_User_Agent, opts[s_user_agent]);
    }
    if (opts.exists(s_max_redirects)) {
      max_redirs = opts[s_max_redirects].toInt64();
    }
    if (opts.exists(s_timeout)) {
      timeout = opts[s_timeout].toInt64();
    }
    if (opts.exists(s_ignore_errors)) {
      ignore_errors = opts[s_ignore_errors].toBoolean();
    }
    if (opts.exists(s_proxy)) {
      Variant host = f_parse_url(opts[s_proxy].toString(), k_PHP_URL_HOST);
      Variant port = f_parse_url(opts[s_proxy].toString(), k_PHP_URL_PORT);
      if (!same(host, false) && !same(port, false)) {
        proxy_host = host.toString();
        proxy_port = port.toInt64();
        Variant user = f_parse_url(opts[s_proxy].toString(), k_PHP_URL_USER);
        Variant pass = f_parse_url(opts[s_proxy].toString(), k_PHP_URL_PASS);
        if (!same(user, false) && !same(pass, false)) {
          proxy_user = user.toString();
          proxy_pass = pass.toString();
        }
      }
    }
    post_data = opts[s_content].toString();
  }

  if (!headers.exists(s_User_Agent)) {
    auto default_user_agent = ThreadInfo::s_threadInfo.getNoCheck()
      ->m_reqInjectionData.getUserAgent();
    if (!default_user_agent.empty()) {
      headers.set(s_User_Agent, default_user_agent);
    }
  }
  auto file = req::make<UrlFile>(method.data(), headers,
                                    post_data, max_redirs,
                                    timeout, ignore_errors);
  file->setStreamContext(context);
  file->setProxy(proxy_host, proxy_port, proxy_user, proxy_pass);
  bool ret = file->open(filename, mode);
  if (!ret) {
    raise_warning("Failed to open %s (%s)", filename.data(),
                  file->getLastError().c_str());
    return nullptr;
  }
  return file;
}