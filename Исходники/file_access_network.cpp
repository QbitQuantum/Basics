Error FileAccessNetworkClient::connect(const String& p_host,int p_port,const String& p_password) {

	IP_Address ip;

	if (p_host.is_valid_ip_address()) {
		ip=p_host;
	} else {
		ip=IP::get_singleton()->resolve_hostname(p_host);
	}

	DEBUG_PRINT("IP: "+String(ip)+" port "+itos(p_port));
	Error err = client->connect(ip,p_port);
	ERR_FAIL_COND_V(err,err);
	while(client->get_status()==StreamPeerTCP::STATUS_CONNECTING) {
//DEBUG_PRINT("trying to connect....");
		OS::get_singleton()->delay_usec(1000);
	}

	if (client->get_status()!=StreamPeerTCP::STATUS_CONNECTED) {
		return ERR_CANT_CONNECT;
	}

	CharString cs = p_password.utf8();	
	put_32(cs.length());
	client->put_data((const uint8_t*)cs.ptr(),cs.length());

	int e = get_32();

	if (e!=OK) {
		return ERR_INVALID_PARAMETER;
	}

	thread = Thread::create(_thread_func,this);

	return OK;
}