bool CTimidityCodec::Init(const std::string& filename, unsigned int filecache,
                     int& channels, int& samplerate,
                     int& bitspersample, int64_t& totaltime,
                     int& bitrate, AEDataFormat& format,
                     std::vector<AEChannel>& channellist)
{
  if (m_soundfont.empty())
    return false;

  if (!LoadDll(m_usedLibName)) return false;
  if (!REGISTER_DLL_SYMBOL(Timidity_Init)) return false;
  if (!REGISTER_DLL_SYMBOL(Timidity_Cleanup)) return false;
  if (!REGISTER_DLL_SYMBOL(Timidity_GetLength)) return false;
  if (!REGISTER_DLL_SYMBOL(Timidity_LoadSong)) return false;
  if (!REGISTER_DLL_SYMBOL(Timidity_FreeSong)) return false;
  if (!REGISTER_DLL_SYMBOL(Timidity_FillBuffer)) return false;
  if (!REGISTER_DLL_SYMBOL(Timidity_Seek)) return false;
  if (!REGISTER_DLL_SYMBOL(Timidity_ErrorMsg)) return false;

  int res;
  if (m_soundfont.find(".sf2") != std::string::npos)
    res = Timidity_Init(48000, 16, 2, m_soundfont.c_str(), nullptr); // real soundfont
  else
    res = Timidity_Init(48000, 16, 2, nullptr, m_soundfont.c_str()); // config file

  if (res != 0)
    return false;

  kodi::vfs::CFile file;
  if (!file.OpenFile(filename))
    return false;

  int len = file.GetLength();
  uint8_t* data = new uint8_t[len];
  if (!data)
    return false;

  file.Read(data, len);

  const char* tempfile = tmpnam(nullptr);

  FILE* f = fopen(tempfile,"wb");
  if (!f)
  {
    delete[] data;
    return false;
  }
  fwrite(data, 1, len, f);
  fclose(f);
  delete[] data;

  m_song = Timidity_LoadSong((char*)tempfile);
  unlink(tempfile);
  if (!m_song)
    return false;

  m_pos = 0;

  channels = 2;
  samplerate = 48000;
  bitspersample = 16;
  totaltime = Timidity_GetLength(m_song);
  format = AE_FMT_S16NE;
  channellist = { AE_CH_FL, AE_CH_FR };
  bitrate = 0;

  return true;
}