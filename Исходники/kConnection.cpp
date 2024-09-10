void kConnection::send_request(const Request& m) {
	std::string s;
	m.SerializeToString(&s);
	stream << varint(s.size()) << s;

	// TODO: Return future to the response
}