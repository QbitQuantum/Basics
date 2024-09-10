Variant c_UConverter::t___destruct() {
  if (m_src) {
    ucnv_close(m_src);
  }
  if (m_dest) {
    ucnv_close(m_dest);
  }

  return uninit_null();
}