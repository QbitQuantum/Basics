  void async_accept(implementation_type& impl, Socket& peer,
      endpoint_type* peer_endpoint, Handler& handler)
  {
    // Allocate and construct an operation to wrap the handler.
    typedef win_iocp_socket_accept_op<Socket, protocol_type, Handler> op;
    typename op::ptr p = { asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    bool enable_connection_aborted =
      (impl.state_ & socket_ops::enable_connection_aborted) != 0;
    p.p = new (p.v) op(*this, impl.socket_, peer, impl.protocol_,
        peer_endpoint, enable_connection_aborted, handler);

    ASIO_HANDLER_CREATION((io_context_, *p.p, "socket",
          &impl, impl.socket_, "async_accept"));

    start_accept_op(impl, peer.is_open(), p.p->new_socket(),
        impl.protocol_.family(), impl.protocol_.type(),
        impl.protocol_.protocol(), p.p->output_buffer(),
        p.p->address_length(), p.p);
    p.v = p.p = 0;
  }