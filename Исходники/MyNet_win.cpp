	 /**
	  * ?????????????
	  **/
	 unsigned int Connection::recv(void *cmd,unsigned int size)
	 {
		unsigned int realcopy = 0;
	//	while (recvs.size())
		while (!recvs.empty())
		{
			Record *record = NULL;
			if (recvs.readOnly(record))
			{
				realcopy = record->recv(cmd,size);
				if (record->empty())
				{
					delete record;
					recvs.pop();
				}
				if (realcopy == size)
				{
					return size;
				}
			}else break;
		}
		return realcopy;
	}