bool_t NetworkTask::DispatchMsg()
{
	bool_t ret = FALSE;

	Buffer *buffer = network_q_->Pop();
	if(!buffer) { return FALSE; }

	Session *sess = 0;
	PacketHeader pkt_header;
	ret = buffer->GetBinary((char_t*)&pkt_header, sizeof(pkt_header));
	if(!ret) { ECILA_TRACE(); goto _ERROR; }

	//network task 는 비동기, dispatch task 는 동기이므로 세션이 먼저 close 될수 있다.
	//그러므로 활성 세션을 찻지 못했을경우는 스킵한다. 
	sess = act_sess_pool_->ACTSession(pkt_header.uidx_);
	if(!sess) { goto _ABORT; }

	if(pkt_header.cmd_ & PKT_CMD_SEND)
	{
		ret = sess->Send(buffer->GetOutPtr(), pkt_header.size_);
		if(!ret) { ECILA_TRACE(); goto _ERROR; }
	}

	if(pkt_header.cmd_ & PKT_CMD_CLOSE)
	{
		ret = sess->Close(TRUE);
		if(!ret) { ECILA_TRACE(); goto _ERROR; }
	}


_ABORT:

	ret = buff_pool_->Release(buffer);
	if(!ret) { ECILA_TRACE(); return FALSE; }

	return TRUE;



_ERROR:
	ret = buff_pool_->Release(buffer);
	if(!ret) { ECILA_TRACE(); return FALSE; }

	return FALSE;
}