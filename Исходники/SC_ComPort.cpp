	SC_UdpInPort(struct World * world, int inPortNum):
		mWorld(world), mPortNum(inPortNum), udpSocket(ioService)
	{
		using namespace boost::asio;
		BOOST_AUTO(protocol, ip::udp::v4());
		udpSocket.open(protocol);

		udpSocket.bind(ip::udp::endpoint(protocol, inPortNum));

		boost::asio::socket_base::send_buffer_size option(65536);
		udpSocket.set_option(option);

#ifdef USE_RENDEZVOUS
		if (world->mRendezvous) {
			thread thread( boost::bind( PublishPortToRendezvous, kSCRendezvous_UDP, sc_htons(mPortNum) ) );
			mRendezvousThread = std::move(thread);
		}
#endif

		startReceiveUDP();
	}