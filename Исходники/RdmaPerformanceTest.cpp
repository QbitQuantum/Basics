void RdmaPerformanceTestServer::handle(uint32 type, shared_ptr<Buffer> b, shared_ptr<RdmaConnection> connection)
{

	switch(type)
	{
		case 0:
		{
				break;
		}
		case 3:
		{
			BufferInfo info;
			info.length = 8192*1024*10;

			shared_ptr<Buffer> rb = connection->createBuffer(info.length);
			info.id = connection->registrerDirect(rb);

			shared_ptr<Buffer> cb = connection->createBuffer(sizeof(info));
			cb->writeAny(info);
			connection->send(3, cb);

			break;
		}
		default:
		{
			connection->send(type,mBuffer);
			LOG4CXX_INFO(mLogger ,"resend type "<< type <<" message ");
			break;
		}
	}

}