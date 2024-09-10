inline int KFileReaderPrivate::next()
{
  if (!m_file.getChar(&m_currChar))
    return KFileReader::EndOfFile;
 return m_currChar;
}