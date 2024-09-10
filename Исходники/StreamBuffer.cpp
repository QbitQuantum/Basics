StreamBuffer::StreamBuffer(u32 type, u32 size)
: m_buffer(genBuffer()), m_buffertype(type), m_size(ROUND_UP_POW2(size)), m_bit_per_slot(Log2(ROUND_UP_POW2(size) / SYNC_POINTS))
{
	m_iterator = 0;
	m_used_iterator = 0;
	m_free_iterator = 0;
}