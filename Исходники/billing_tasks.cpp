//-------------------------------------------------------------------------------------
bool CreateAccountTask::process()
{
	if(!enable)
	{
		return false;
	}

	// 如果没有设置第三方服务地址则我们默认为成功
	if(strlen(serviceAddr()) == 0)
	{
		success = true;
		getDatas = postDatas;
		return false;
	}

	Mercury::EndPoint endpoint;
	endpoint.socket(SOCK_STREAM);

	if (!endpoint.good())
	{
		ERROR_MSG("BillingTask::process: couldn't create a socket\n");
		return false;
	}

	if(postDatas.size() == 0)
	{
		ERROR_MSG(boost::format("BillingTask::process: %1% postData is NULL.\n") % commitName);
		return false;
	}

	u_int32_t addr;
	KBEngine::Mercury::EndPoint::convertAddress(serviceAddr(), addr);

	if(endpoint.connect(htons(servicePort()), addr) == -1)
	{
		ERROR_MSG(boost::format("BillingTask::process: connect billingserver(%1%:%2%) is error(%3%)!\n") % 
			serviceAddr() % servicePort() % kbe_strerror());

		endpoint.close();
		return false;
	}

	endpoint.setnonblocking(true);
	endpoint.setnodelay(true);

	Mercury::Bundle::SmartPoolObjectPtr bundle = Mercury::Bundle::createSmartPoolObj();
	(*(*bundle)).append(postDatas.data(), postDatas.size());
	(*(*bundle)).send(endpoint);

	Mercury::TCPPacket packet;
	packet.resize(1024);

	fd_set	frds;
	struct timeval tv = { 0, 5000000 }; // 5000ms

	FD_ZERO( &frds );
	FD_SET((int)endpoint, &frds);
	int selgot = select(endpoint+1, &frds, NULL, NULL, &tv);
	if(selgot <= 0)
	{
		ERROR_MSG(boost::format("BillingTask::process: %1% send(%2%).\n") % commitName % postDatas);
		ERROR_MSG(boost::format("BillingTask::process: %1% recv is error(%2%).\n") % commitName % KBEngine::kbe_strerror());
		endpoint.close();
		return false;
	}
	
	int len = endpoint.recv(packet.data(), 1024);

	if(len <= 0)
	{
		ERROR_MSG(boost::format("BillingTask::process: %1% recv is size<= 0.\n===>postdatas=%2%\n") % commitName % postDatas);
		endpoint.close();
		return false;
	}

	packet.wpos(len);

	getDatas.assign((const char *)(packet.data() + packet.rpos()), packet.opsize());

	try
	{
		std::string::size_type fi = getDatas.find("\r\n\r\n");
		if(fi != std::string::npos)
		{
			fi += 4;
			MemoryStream s;
			s.append(getDatas.data() + fi, getDatas.size() - fi);

			while(s.opsize() > 0)
			{
				int32 type, len;
				s >> type >> len;
				EndianConvertReverse<int32>(type);
				EndianConvertReverse<int32>(len);
				
				int32 error = 0;

				switch(type)
				{
				case 1:
					s >> error;
					EndianConvertReverse<int32>(error);

					if(error != 0)
					{
						success = false;
						endpoint.close();
						
						std::string err;
						if(s.opsize() >= (sizeof(int32) * 2))
						{
							s >> type >> len;
							
							if(len > 0 && len < 1024)
							{
								char* buf = new char[len + 1];
								memcpy(buf, s.data() + s.rpos(), len);
								buf[len] = 0;
								err = buf;
								delete[] buf;
							}

						}

						DEBUG_MSG(boost::format("BillingTask::process: (%1%)op is failed! err=%2%\n<==send(%3%)\n==>recv(%4%).\n") % commitName % err % postDatas % getDatas);
						return false;
					}
					else
					{
						success = true;
					}

					break;
				case 2:
					{
						s.read_skip(len);
					}
					break;
				case 3:
					{
						char* buf = new char[len + 1];
						memcpy(buf, s.data() + s.rpos(), len);
						buf[len] = 0;
						accountName = buf;
						delete[] buf;

						s.read_skip(len);
					}
					break;
				default:
					break;
				};