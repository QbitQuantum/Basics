static SOCKET WSAAPI accept_h(SOCKET s, struct sockaddr* addr, int* addrlen)
{
  auto thrctx = asev::ev_service::current();
  if (thrctx == nullptr)
  {
    return accept_f(s, addr, addrlen);
  }

  auto corctx = thrctx->get_corctx();
  ACTX_EXPECTS(corctx != nullptr);

  auto coraf = corctx->get_affix<cor_affix>();
  ACTX_EXPECTS(coraf != nullptr);

  io_context& ioctx = coraf->ioctx_;
  DWORD bytes = 0;
  WSABUF* wbuf = &ioctx.wsa_buf_;
  LPOVERLAPPED ol = &ioctx.overlapped_;
  DWORD addr_len = sizeof(SOCKADDR_IN) + 16;
  ioctx.ec_.clear();
  ioctx.opt_ = opt_accept;

  // Make socket.
  auto skt = WSASocketW(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
  if (skt == INVALID_SOCKET)
  {
    return INVALID_SOCKET;
  }

  // AcceptEx.
  auto result = ::AcceptEx(s, skt, wbuf->buf, 0, addr_len, addr_len, &bytes, ol);
  // Check AcceptEx result.
  DWORD last_error = ::WSAGetLastError();
  if (!result && last_error != WSA_IO_PENDING)
  {
    close_socket(skt);
    return INVALID_SOCKET;
  }
  else
  {
    corctx->yield();
  }

  if (ioctx.ec_)
  {
    close_socket(skt);
  }

  ioctx.skt_ = skt;
  return skt;
}