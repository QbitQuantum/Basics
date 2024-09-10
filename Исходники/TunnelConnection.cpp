void CTunnelingConnection::HandleDisconnectRequest(unsigned char* buffer)
{	
	CDisconnectRequest dis_req(buffer);
	if(dis_req.GetChannelID() != _state._channelid){
		return;
	}

	CDisconnectResponse dis_resp(_state._channelid,E_NO_ERROR);
	unsigned char buf[256];
	dis_resp.FillBuffer(buf,256);
	UDPSocket sock;

	LOG_DEBUG("[Send] [BUS] [Disconnect Response]");
	
	sock.SendTo(buf,dis_resp.GetTotalSize(),_device_control_address,_device_control_port);
	
	_heartbeat->Close();

	JTCSynchronized s(*this);
        _state._channelid = 0;
        _state._recv_sequence = 0;
        _state._send_sequence = 0;

        SetStatusDisconnected();
}