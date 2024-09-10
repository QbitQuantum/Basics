bool GSDumpLzma::Read(void* ptr, size_t size) {
	size_t off = 0;
	uint8_t* dst = (uint8_t*)ptr;
	size_t full_size = size;
	while (size && !IsEof()) {
		if (m_avail == 0) {
			Decompress();
		}

		size_t l = std::min(size, m_avail);
		memcpy(dst + off, m_area+m_start, l);
		m_avail -= l;
		size    -= l;
		m_start += l;
		off     += l;
	}

	if (size == 0) {
		Repack(ptr, full_size);
		return true;
	}

	return false;
}