void CompressWrite(void *pInput, size_t inputSize, FileWriter &fw)
{
  if ( !pInput )
    return;

  char *_pInput = (char*)pInput;
  memset(bWorkBuff2, 0, sizeof(bWorkBuff2));
  memset(bSegment, 0, sizeof(bSegment));
  memset(&params, 0, sizeof(params));

  // Write Header
  _Part hdr = { 0 };

  // checksum
  unsigned int  dwSize = inputSize;
  unsigned long dwOld  = ~0;
  hdr.dwCrc32Sum = crc32pk((char*)pInput, &dwSize, &dwOld);

  // sections
  hdr.dwSectionCount = dwSize / 0x2000;
  if ( dwSize % 0x2000 )
    hdr.dwSectionCount++;
  
  // write
  fw.Write<_Part>(hdr);

  // Iterate sections
  DWORD dwPos = 0;
  for ( DWORD s = 0; s < hdr.dwSectionCount; ++s )
  {
    DWORD dwWriteSize = inputSize - dwPos;
    if ( dwWriteSize > 0x2000 )
      dwWriteSize = 0x2000;

    memset(&params, 0, sizeof(params));
    params.pCompressedData    = &_pInput[dwPos];
    params.dwMaxRead          = dwWriteSize;
    params.pDecompressedData  = bSegment;
    params.dwMaxWrite         = dwWriteSize;

    unsigned int dwType = 0;
    unsigned int dwImplSize = 0x400;
    if ( implode(&read_buf, &write_buf, bWorkBuff2, &params, &dwType, &dwImplSize) || params.dwWritePos >= dwWriteSize )
    {
      if ( !dwWriteSize )
        return;
      fw.Write<DWORD>(dwWriteSize);
      fw.WriteRaw(&_pInput[dwPos], dwWriteSize);
      dwPos += dwWriteSize;
    }
    else
    {
      if ( !params.dwWritePos )
        return;
      fw.Write<DWORD>(params.dwWritePos);
      fw.WriteRaw(bSegment, params.dwWritePos);
      dwPos += dwWriteSize;
    }

    
  } // for
}