// This is WritePart function
HRESULT CChmFolderOutStream::Write2(const void *data, UInt32 size, UInt32 *processedSize, bool isOK)
{
  UInt32 realProcessed = 0;
  if (processedSize != NULL)
   *processedSize = 0;
  while(size != 0)
  {
    if (m_FileIsOpen)
    {
      UInt32 numBytesToWrite = (UInt32)MyMin(m_RemainFileSize, (UInt64)(size));
      HRESULT res = S_OK;
      if (numBytesToWrite > 0)
      {
        if (!isOK)
          m_IsOk = false;
        if (m_RealOutStream)
        {
          UInt32 processedSizeLocal = 0;
          res = m_RealOutStream->Write((const Byte *)data, numBytesToWrite, &processedSizeLocal);
          numBytesToWrite = processedSizeLocal;
        }
      }
      realProcessed += numBytesToWrite;
      if (processedSize != NULL)
        *processedSize = realProcessed;
      data = (const void *)((const Byte *)data + numBytesToWrite);
      size -= numBytesToWrite;
      m_RemainFileSize -= numBytesToWrite;
      m_PosInSection += numBytesToWrite;
      m_PosInFolder += numBytesToWrite;
      if (res != S_OK)
        return res;
      if (m_RemainFileSize == 0)
      {
        m_RealOutStream.Release();
        RINOK(m_ExtractCallback->SetOperationResult(
          m_IsOk ?
            NExtract::NOperationResult::kOK:
            NExtract::NOperationResult::kDataError));
        m_FileIsOpen = false;
      }
      if (realProcessed > 0)
        break; // with this break this function works as write part
    }
    else
    {
      if (m_CurrentIndex >= m_NumFiles)
        return E_FAIL;
      int fullIndex = m_StartIndex + m_CurrentIndex;
      m_RemainFileSize = m_Database->GetFileSize(fullIndex);
      UInt64 fileOffset = m_Database->GetFileOffset(fullIndex);
      if (fileOffset < m_PosInSection)
        return E_FAIL;
      if (fileOffset > m_PosInSection)
      {
        UInt32 numBytesToWrite = (UInt32)MyMin(fileOffset - m_PosInSection, UInt64(size));
        realProcessed += numBytesToWrite;
        if (processedSize != NULL)
          *processedSize = realProcessed;
        data = (const void *)((const Byte *)data + numBytesToWrite);
        size -= numBytesToWrite;
        m_PosInSection += numBytesToWrite;
        m_PosInFolder += numBytesToWrite;
      }
      if (fileOffset == m_PosInSection)
      {
        RINOK(OpenFile());
        m_FileIsOpen = true;
        m_CurrentIndex++;
        m_IsOk = true;
      }
    }
  }
  return WriteEmptyFiles();
}