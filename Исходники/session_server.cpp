void server::pre_session_over(const std::shared_ptr<pre_session>& _pre, bool successful)
{
	std::lock_guard<std::mutex> lock(pre_session_mutex);
	if (!successful)
	{
		main_iosrv.post([this, port = _pre->get_port(), key = _pre->get_key()]() {
			if (port != port_null)
				free_rand_port(static_cast<port_type>(port));
			if (!key.empty())
				delete_key(key);
		});
	}
	_pre->shutdown();
	pre_sessions.erase(_pre);
}