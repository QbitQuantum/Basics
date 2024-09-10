int64_t
mm_io_c::get_size() {
  if (-1 == m_cached_size) {
    save_pos();
    setFilePointer(0, seek_end);
    m_cached_size = getFilePointer();
    restore_pos();
  }

  return m_cached_size;
}