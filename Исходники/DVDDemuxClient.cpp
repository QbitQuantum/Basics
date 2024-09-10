bool CDVDDemuxClient::Open(CDVDInputStream* pInput)
{
  Abort();

  m_pInput = pInput;
  m_IDemux = dynamic_cast<CDVDInputStream::IDemux*>(m_pInput);
  if (!m_IDemux)
    return false;

  if (!m_IDemux->OpenDemux())
    return false;

  RequestStreams();

  m_displayTime = 0;
  m_dtsAtDisplayTime = DVD_NOPTS_VALUE;
  return true;
}