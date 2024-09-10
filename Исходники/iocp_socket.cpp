void socket_ops::accept(iocp::acceptor &acceptor,
												iocp::operation *op,
												iocp::socket &socket,
												char *buffer)
{
	iocp::service &service = acceptor.service();
	service.work_started();
	iocp::error_code ec = socket.open();
	if (ec && ec.value() != iocp::error::already_open)
		service.on_completion(op, ec);
	else
		service.accept(acceptor.socket_, op, socket.socket_, buffer);
}