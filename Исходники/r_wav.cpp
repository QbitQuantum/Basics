int
wav_dts_demuxer_c::decode_buffer(int len) {
  if (m_swap_bytes) {
    swab((char *)m_buf[m_cur_buf]->get_buffer(), (char *)m_buf[m_cur_buf ^ 1]->get_buffer(), len);
    m_cur_buf ^= 1;
  }

  if (m_pack_14_16) {
    dts_14_to_dts_16((unsigned short *)m_buf[m_cur_buf]->get_buffer(), len / 2, (unsigned short *)m_buf[m_cur_buf ^ 1]->get_buffer());
    m_cur_buf ^= 1;
    len        = len * 7 / 8;
  }

  return len;
}