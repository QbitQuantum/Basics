bool CHomeRunFile::Open(const CURL &url)
{
  if(!m_pdll->IsLoaded())
    return false;

  m_device = m_pdll->device_create_from_str(url.GetHostName().c_str(), NULL);
  if(!m_device)
    return false;

  m_pdll->device_set_tuner_from_str(m_device, url.GetFileName().c_str());

  CUrlOptions options(url.GetOptions().Mid(1));
  CUrlOptions::iterator it;

  if( (it = options.find("channel")) != options.end() )
    m_pdll->device_set_tuner_channel(m_device, it->second.c_str());

  if( (it = options.find("program")) != options.end() )
    m_pdll->device_set_tuner_program(m_device, it->second.c_str());

  // start streaming from selected device and tuner
  if( m_pdll->device_stream_start(m_device) <= 0 )
    return false;

  return true;
}