bool CFX_WideString::Equal(const CFX_WideString& other) const {
  if (IsEmpty()) {
    return other.IsEmpty();
  }
  if (other.IsEmpty()) {
    return false;
  }
  return other.m_pData->m_nDataLength == m_pData->m_nDataLength &&
         wmemcmp(other.m_pData->m_String, m_pData->m_String,
                 m_pData->m_nDataLength) == 0;
}