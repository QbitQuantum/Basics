bool CDateTime::operator ==(const FILETIME& right) const
{
  return CompareFileTime(&m_time, &right)==0;
}