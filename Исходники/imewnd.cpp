bool input_context::enlarge_msg_buf(u32 n)
{
	HIMCC hMem;

	if (m_num_msg < m_msg_buf_size) { // this function must not be called when there's still space 
		bhjerr(" Error: enlarge_msg_buf called when still have space!");
	}

	if (m_num_msg == m_msg_buf_size) { // this should be the first time we are called
		n += m_num_msg;
	}

	if (!m_ic->hMsgBuf) {
		m_ic->dwNumMsgBuf = 0; 

		m_ic->hMsgBuf = ImmCreateIMCC( (n + m_num_msg) * sizeof(TRANSMSG));
		if (m_ic->hMsgBuf) {

			if (!copy_old_msg()) {
				return false;
			}
			m_ic->dwNumMsgBuf = n;
			return true;
		} else {
			return false;
		}
	} 
	
	if (hMem = ImmReSizeIMCC(m_ic->hMsgBuf,
									(m_ic->dwNumMsgBuf + n) * sizeof(TRANSMSG))) {
		if (hMem != m_ic->hMsgBuf) {
			ImmDestroyIMCC(m_ic->hMsgBuf);
			m_ic->hMsgBuf = hMem;
		}

		if (m_num_msg == m_msg_buf_size && m_num_msg > 0) { // copy the old messages over
			if (!copy_old_msg()) {
				return false;
			}
			m_num_msg += m_ic->dwNumMsgBuf; //number of valid messages
		}
		m_ic->dwNumMsgBuf += n; //this last n messages are not valid yet!
		return true;
	} else { // resize failed
		return false;
	}
}