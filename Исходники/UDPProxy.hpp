		DWORD _SendImpl()
		{
			while(!sendThread_.IsAborted())
			{
				
				try
				{
					common::Buffer buf = queue_.Get();
					if( buf.first.get() == 0 )
						break;

					size_t len = sendSck_.SendTo(iocp::Buffer(buf.first.get(), buf.second), 0);
					if( len == 0 )
						break;

					SOCKADDR_IN addr = {0};
					char retBuf[4] = {0};
					sendSck_.RecvFrom(iocp::Buffer(retBuf), &addr);

					::InterlockedExchange(&isOK_, 1);
				}
				catch(std::exception &e)
				{
					::InterlockedExchange(&isOK_, 0);
					::OutputDebugStringA(e.what());
					::Sleep(1000);
				}
				
			}

			return 0;
		}