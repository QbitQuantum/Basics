	virtual void handle(uint32 type, shared_ptr<Buffer> buffer, shared_ptr<IBConnection> connection)
	{
		if(type == TEST_LARGE_BUFFER_TYPE)
		{
			handleLargeBuffer(mLogger, type, buffer);

			// send a dummy ack buffer back
			shared_ptr<Buffer> ack = connection->createBuffer(4);
			ack->write(0);
			connection->send(0, ack);
		}
		else if(type == 0)
		{
			connection->close();
		}
	}