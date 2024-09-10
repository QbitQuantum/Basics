AdbConReply* AdbConnection::send(wxString op, wxString param, bool send_only){
	int timeouts = 0;
	AdbConReply* r;
	while(max_timeouts>timeouts++){
		r = send_layer1(op, param, send_only);
		if(m_cb->abort()) break;
		if(r==NULL) continue; // timeout
		if(!op.StartsWith(wxT("LOGOUT"))&&(r->code==rLOGIN_FIRST||r->code==rINVALID_SESSION)){
			if(remaining_auth_attempts<=0){
				AERROR(wxT("Invalid session."));
				return NULL;
			}
			remaining_auth_attempts--;
			if(login())
				return send(op, param, send_only);
			return NULL;
		}
		return r;
	}
	ALOG(getLastError());
	return NULL;
}