				bool trySendPacket(sf::Packet mPacket)
				{
					if(!busy) { ssvu::lo("ManagedSocket") << "Couldn't send packet - not busy" << std::endl; return false; }

					for(int i{0}; i < 5; ++i)
					{
						if(busy && socket.send(mPacket) == sf::Socket::Done) { onPacketSent(mPacket); return true; }
						std::this_thread::sleep_for(std::chrono::milliseconds(50));
					}

					ssvu::lo("ManagedSocket") << "Couldn't send packet - disconnecting" << std::endl;
					disconnect();
					return false;
				}