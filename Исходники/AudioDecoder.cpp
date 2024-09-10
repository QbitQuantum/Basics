bool CAudioDecoder::Init(const CFileItem& file, unsigned int filecache)
{
  if (!Initialized())
    return false;

  // for replaygain
  CTagLoaderTagLib tag;
  tag.Load(file.GetPath(), XFILE::CMusicFileDirectory::m_tag, NULL);

  int channels;
  int sampleRate;

  m_context = m_struct.toAddon.Init(file.GetPath().c_str(), filecache,
                              &channels, &sampleRate,
                              &m_bitsPerSample, &m_TotalTime,
                              &m_bitRate, &m_format.m_dataFormat, &m_channel);

  m_format.m_sampleRate = sampleRate;
  if (m_channel)
    m_format.m_channelLayout = CAEChannelInfo(m_channel);
  else
    m_format.m_channelLayout = CAEUtil::GuessChLayout(channels);

  return (m_context != NULL);
}