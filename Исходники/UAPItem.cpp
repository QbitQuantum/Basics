fulliautomatix_data* UAPItem::getData(unsigned char* pData, long len, int byteoffset)
{
  int byteShift = m_nBit/8;
  if (byteShift<len)
    return newDataUL(NULL, getPID(), byteoffset+byteShift, 1, *(pData+byteShift));
  return NULL;
}