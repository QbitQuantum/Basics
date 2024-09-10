  void async_accept(implementation_type& impl, Socket& peer,
      endpoint_type* peer_endpoint, Handler& handler)
  {
    bool is_continuation =
      asio_handler_cont_helpers::is_continuation(handler);

    // Allocate and construct an operation to wrap the handler.
    typedef reactive_socket_accept_op<Socket, Protocol, Handler> op;
    typename op::ptr p = { asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(impl.socket_, impl.state_, peer,
        impl.protocol_, peer_endpoint, handler);

    ASIO_HANDLER_CREATION((p.p, "socket", &impl, "async_accept"));

    start_accept_op(impl, p.p, is_continuation, peer.is_open());
    p.v = p.p = 0;
  }