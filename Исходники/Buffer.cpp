sample_t* Buffer::getBuffer() const
{
	return (sample_t*) ALIGN(m_buffer);
}