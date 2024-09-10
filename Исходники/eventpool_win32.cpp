	/**
	 * pool 
	 **/
	void Connection::doSend(EventBase *evt,bool over)
	{
		bool tag = false;
		OutEvent<Connection>* event = static_cast<OutEvent<Connection>*>( evt );
		if (event->msgLen < event->dataLen && !over)
		{
			return;
		}
		event->dataLen = 0;
		event->reset();
		int leftLen = EventBase::MAX_BUFFER_LEN;
		while (!sends.empty() && leftLen > 0)
		{
			tag = true;
			Record *record = NULL;
			if (sends.readOnly(record))
			{
				unsigned int realCopySize = record->recv(event->buffer,leftLen);
				evt->dataLen += realCopySize;
				
				if (leftLen == realCopySize)
				{
					leftLen = 0;
					if (record->empty())
					{
						delete record;
						sends.pop();
					}
					break;
				}
				else
				{
					leftLen -= realCopySize;
					if(!record->empty())
					{
						// TODO ERROR
					}
					sends.pop();
				}
			}else break;
		}
		if (tag)
			evt->redo();
	}