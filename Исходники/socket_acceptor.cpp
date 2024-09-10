bool socket_acceptor::is_ready(const socket& s) const {
	return FD_ISSET(s.native_handle(), &pimpl->ready) != 0;
}