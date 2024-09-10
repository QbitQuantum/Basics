void BaosIpEnumerator::sendSearchRequestFrame(MulticastSocket& socket)
{
	const IPAddress& address = socket.address().host();
	StringTokenizer stringTokenizer(address.toString(), ".");
	BOOST_ASSERT(stringTokenizer.count() == 4 && "Invalid IP Address");

	const unsigned short port = socket.address().port();

	// build SEARCH_REQUEST frame
	const std::vector<unsigned char> request =
	{
		0x06, 0x10, 0x02, 0x01, 0x00, 0x0E, 0x08, 0x01,
		static_cast<unsigned char>(NumberParser::parse(stringTokenizer[0])),
		static_cast<unsigned char>(NumberParser::parse(stringTokenizer[1])),
		static_cast<unsigned char>(NumberParser::parse(stringTokenizer[2])),
		static_cast<unsigned char>(NumberParser::parse(stringTokenizer[3])),
		static_cast<unsigned char>((port >> 8) & 0xFF),
		static_cast<unsigned char>(port & 0xFF)
	};

	// send to socket
	const SocketAddress destAddress(MulticastProtocolConstants::Address, MulticastProtocolConstants::Port);
	socket.sendTo(&request.at(0), static_cast<int>(request.size()), destAddress);
}