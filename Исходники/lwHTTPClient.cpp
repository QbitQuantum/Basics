	void HTTPMsg::onSendComplete(){
		_buff.reset();
		WinHttpReceiveResponse(_hRequest, NULL);
	}