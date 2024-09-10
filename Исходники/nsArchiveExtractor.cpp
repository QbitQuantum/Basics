nsArchiveExtractor::nsArchiveExtractor(const WCHAR *sArchiveName, DWORD dwSfxStubSize, nsExtractorProgress *pProgress) :
  m_sArchiveName(NULL), m_pProgress(pProgress), m_dwSfxStubSize(dwSfxStubSize)
{
  if (sArchiveName)
    m_sArchiveName = wcsdup(sArchiveName);
}