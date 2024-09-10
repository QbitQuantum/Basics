void ripng_router::broadcast(ripng_header *hdr, uint16_t len) {
	for (std::vector<intf_timer>::const_iterator i =
			m_intftimers.begin(); i != m_intftimers.end(); ++i) {
		m_sock.sendto(hdr, len, &m_ripnggrp, i->argument()->localaddr());
	}
}