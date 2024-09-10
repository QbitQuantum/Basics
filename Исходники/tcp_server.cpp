bool net::tcp_server::add_listener(const socket& s, const socket_address& addr, void* data)
{
	listener** listeners;
	if ((listeners = (listener**) realloc(_M_listeners, (_M_nlisteners + 1) * sizeof(listener*))) == NULL) {
		return false;
	}

	_M_listeners = listeners;

	listener* l;
	if ((l = new (std::nothrow) listener()) == NULL) {
		return false;
	}

	if (!selector::add(s.fd(), fdset::FD_LISTENER, l, selector::READ)) {
		delete l;
		return false;
	}

	l->fd(s.fd());

	l->_M_addr = addr;
	l->_M_data = data;

	_M_listeners[_M_nlisteners++] = l;

	return true;
}