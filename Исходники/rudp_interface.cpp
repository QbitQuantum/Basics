//发送一个握手失败的SYN2
void RUDPObject::send_syn2(uint32_t remote_rudp_id, uint8_t result, uint16_t check_sum, const Inet_Addr& remote_addr, IRUDPAdapter* adapter)
{
	if(adapter == NULL)
		return ;

	RUDPHeadPacket head;
	head.msg_id_ = RUDP_SYN2;
	head.remote_rudp_id_ = remote_rudp_id;
	head.check_sum_ = check_sum;

	RUDPSyn2Packet syn2;
	syn2.version_ = RUDP_VERSION;
	syn2.local_rudp_id_ = 0;
	syn2.local_ts_ = CBaseTimeValue::get_time_value().msec();
	syn2.remote_ts_ = syn2.local_ts_;
	syn2.syn2_result_ = result;
	syn2.max_segment_size_ = MAX_SEGMENT_SIZE;
	syn2.start_seq_ = 0;

	BinStream strm;
	strm.rewind(true);
	strm << adapter->get_title() << head << syn2;

	adapter->send(strm, remote_addr);
}