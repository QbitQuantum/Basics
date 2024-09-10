/*virtual*/ int HTTPText::write(const char* buf, size_t len)
{
  size_t writeLen = MIN(len, m_size - 1 - m_pos);
  memcpy(m_str + m_pos, buf, writeLen);
  m_pos += writeLen;
  m_str[m_pos] = '\0';
  return OK;
}