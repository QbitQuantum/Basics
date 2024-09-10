int
dts_reader_c::decode_buffer(size_t length) {
  if (m_swap_bytes) {
    swab(reinterpret_cast<char *>(m_buf[m_cur_buf]), reinterpret_cast<char *>(m_buf[m_cur_buf ^ 1]), length);
    m_cur_buf ^= 1;
  }

  if (m_dts14_to_16) {
    mtx::dts::convert_14_to_16_bits(m_buf[m_cur_buf], length / 2, m_buf[m_cur_buf ^ 1]);
    m_cur_buf ^= 1;
    length     = length * 7 / 8;
  }

  return length;
}