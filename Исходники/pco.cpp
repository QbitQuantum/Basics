Bytes
ParsedContentObject::content() const
{
  const unsigned char *content;
  size_t len;
  int res = ccn_content_get_value(head(m_bytes), m_pco.offset[CCN_PCO_E], &m_pco, &content, &len);
  if (res < 0)
  {
    boost::throw_exception(MisformedContentObjectException());
  }

  Bytes bytes;
  readRaw(bytes, content, len);
  return bytes;
}