Error HTTPClient::request(Method p_method, const String &p_url, const Vector<String> &p_headers, const String &p_body) {

	ERR_FAIL_INDEX_V(p_method, METHOD_MAX, ERR_INVALID_PARAMETER);
	ERR_FAIL_COND_V(!p_url.begins_with("/"), ERR_INVALID_PARAMETER);
	ERR_FAIL_COND_V(status != STATUS_CONNECTED, ERR_INVALID_PARAMETER);
	ERR_FAIL_COND_V(connection.is_null(), ERR_INVALID_DATA);

	String request = String(_methods[p_method]) + " " + p_url + " HTTP/1.1\r\n";
	if ((ssl && conn_port == PORT_HTTPS) || (!ssl && conn_port == PORT_HTTP)) {
		// Don't append the standard ports
		request += "Host: " + conn_host + "\r\n";
	} else {
		request += "Host: " + conn_host + ":" + itos(conn_port) + "\r\n";
	}
	bool add_uagent = true;
	bool add_accept = true;
	bool add_clen = p_body.length() > 0;
	for (int i = 0; i < p_headers.size(); i++) {
		request += p_headers[i] + "\r\n";
		if (add_clen && p_headers[i].findn("Content-Length:") == 0) {
			add_clen = false;
		}
		if (add_uagent && p_headers[i].findn("User-Agent:") == 0) {
			add_uagent = false;
		}
		if (add_accept && p_headers[i].findn("Accept:") == 0) {
			add_accept = false;
		}
	}
	if (add_clen) {
		request += "Content-Length: " + itos(p_body.utf8().length()) + "\r\n";
		// Should it add utf8 encoding?
	}
	if (add_uagent) {
		request += "User-Agent: GodotEngine/" + String(VERSION_FULL_BUILD) + " (" + OS::get_singleton()->get_name() + ")\r\n";
	}
	if (add_accept) {
		request += "Accept: */*\r\n";
	}
	request += "\r\n";
	request += p_body;

	CharString cs = request.utf8();
	Error err = connection->put_data((const uint8_t *)cs.ptr(), cs.length());
	if (err) {
		close();
		status = STATUS_CONNECTION_ERROR;
		return err;
	}

	status = STATUS_REQUESTING;

	return OK;
}