void RenderDoc::RemoteAccessClientThread(void *s)
{
	Network::Socket *client = (Network::Socket *)s;

	Serialiser ser(L"", Serialiser::WRITING, false);

	wstring api = L"";
	RDCDriver driver;
	RenderDoc::Inst().GetCurrentDriver(driver, api);

	ser.Rewind();

	wstring target = RenderDoc::Inst().GetCurrentTarget();
	ser.Serialise("", target);
	ser.Serialise("", api);

	if(!SendPacket(client, ePacket_Handshake, ser))
	{
		SAFE_DELETE(client);

		{
			SCOPED_LOCK(RenderDoc::Inst().m_SingleClientLock);
			RenderDoc::Inst().m_SingleClientName = L"";
		}

		return;
	}

	const int pingtime = 1000; // ping every 1000ms
	const int ticktime = 10; // tick every 10ms
	int curtime = 0;

	vector<wstring> captures;

	while(client)
	{
		if(RenderDoc::Inst().m_RemoteClientThreadShutdown || (client && !client->Connected()))
		{
			SAFE_DELETE(client);
			break;
		}

		ser.Rewind();

		Threading::Sleep(ticktime);
		curtime += ticktime;

		PacketType packetType = ePacket_Noop;

		wstring curapi;
		RenderDoc::Inst().GetCurrentDriver(driver, curapi);

		if(curapi != api)
		{
			api = curapi;

			ser.Serialise("", api);

			packetType = ePacket_RegisterAPI;
		}
		else
		{
			vector<wstring> caps = RenderDoc::Inst().GetCaptures();

			if(caps.size() != captures.size())
			{
				uint32_t idx = (uint32_t)captures.size();

				captures.push_back(caps[idx]);

				packetType = ePacket_NewCapture;

				uint64_t timestamp = FileIO::GetModifiedTimestamp(captures.back().c_str());
				ser.Serialise("", idx);
				ser.Serialise("", timestamp);

				ser.Serialise("", captures.back());

				uint32_t len = 128*1024;
				byte *thumb = new byte[len];
				RENDERDOC_GetThumbnail(captures.back().c_str(), thumb, len);

				size_t l = len;
				ser.Serialise("", len);
				ser.SerialiseBuffer("", thumb, l);
				delete[] thumb;
			}
		}

		if(curtime < pingtime && packetType == ePacket_Noop)
		{
			if(client->IsRecvDataWaiting())
			{
				PacketType type;
				Serialiser *recvser = NULL;

				if(!RecvPacket(client, type, &recvser))
					SAFE_DELETE(client);

				if(client == NULL)
				{
					SAFE_DELETE(recvser);
					continue;
				}
				else if(type == ePacket_TriggerCapture)
				{
					RenderDoc::Inst().TriggerCapture();
				}
				else if(type == ePacket_QueueCapture)
				{
					uint32_t frameNum = 0;
					recvser->Serialise("", frameNum);
					
					RenderDoc::Inst().QueueCapture(frameNum);
				}
				else if(type == ePacket_CopyCapture)
				{
					vector<wstring> caps = RenderDoc::Inst().GetCaptures();

					uint32_t id = 0;
					recvser->Serialise("", id);

					if(id < caps.size())
					{
						ser.Serialise("", id);

						if(!SendPacket(client, ePacket_CopyCapture, ser))
						{
							SAFE_DELETE(client);
							continue;
						}

						ser.Rewind();

						if(!SendChunkedFile(client, ePacket_CopyCapture, caps[id].c_str(), ser, NULL))
						{
							SAFE_DELETE(client);
							continue;
						}

						RenderDoc::Inst().MarkCaptureRetrieved(id);
					}
				}

				SAFE_DELETE(recvser);
			}

			continue;
		}

		curtime = 0;

		if(!SendPacket(client, packetType, ser))
		{
			SAFE_DELETE(client);
			continue;
		}
	}
	
	// give up our connection
	{
		SCOPED_LOCK(RenderDoc::Inst().m_SingleClientLock);
		RenderDoc::Inst().m_SingleClientName = L"";
	}
}