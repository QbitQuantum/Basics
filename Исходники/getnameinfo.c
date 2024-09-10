/* getnameinfo worker thread implementation */
static DWORD WINAPI getnameinfo_thread_proc(void* parameter) {
  uv_getnameinfo_t* req = (uv_getnameinfo_t*)parameter;
  uv_loop_t* loop = req->loop;
  WCHAR host[NI_MAXHOST];
  WCHAR service[NI_MAXSERV];
  int ret = 0;

  assert(req != NULL);

  ret = GetNameInfoW((struct sockaddr*)&req->storage,
                     sizeof(req->storage),
                     host,
                     sizeof(host),
                     service,
                     sizeof(service),
                     req->flags);
  req->retcode = uv__getaddrinfo_translate_error(ret);

  /* convert results to UTF-8 */
  WideCharToMultiByte(CP_UTF8,
                      0,
                      host,
                      -1,
                      req->host,
                      sizeof(req->host),
                      NULL,
                      NULL);

  WideCharToMultiByte(CP_UTF8,
                      0,
                      service,
                      -1,
                      req->service,
                      sizeof(req->service),
                      NULL,
                      NULL);

  /* post getnameinfo completed */
  POST_COMPLETION_FOR_REQ(loop, req);

  return 0;
}