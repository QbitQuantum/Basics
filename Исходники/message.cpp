message& message::operator<<(double const& double_precision)
{
	assert(sizeof(double) == 8);

	uint64_t const host_order = *reinterpret_cast<uint64_t const*>(&double_precision);
	uint64_t network_order = htonll(host_order);
	add(&network_order, sizeof(uint64_t));

	return *this;
}