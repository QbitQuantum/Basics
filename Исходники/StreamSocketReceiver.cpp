void StreamSocketReceiver::receivePayload(net::Socket &s, ostream &stream, size_t len)
{
	void *buf = malloc(this->packet_size);
	size_t bytes_read = 0;
	while (bytes_read < len) {
		size_t exp_bytes = min(this->packet_size, len - bytes_read);
		size_t bytes_recv = s.recv((char*)buf, exp_bytes);
		if (bytes_recv != exp_bytes) {
			free(buf);
			throw IncompleteReceiveException(bytes_read + bytes_recv, len);
		}
		bytes_read += bytes_recv;
		stream.write((char*)buf, bytes_recv);
	}
	free(buf);
}