/////////////////////////////////////////////////////////////////////////////
// Demuxer Functions
STDMETHODIMP CBDDemuxer::Open(LPCOLESTR pszFileName)
{
  CAutoLock lock(m_pLock);
  HRESULT hr = S_OK;

  int ret; // return code from C functions

  // Convert the filename from wchar to char for libbluray
  char fileName[4096];
  ret = WideCharToMultiByte(CP_UTF8, 0, pszFileName, -1, fileName, 4096, NULL, NULL);

  int iPlaylist = -1;

  DbgLog((LOG_TRACE, 10, L"Initializing BluRay Demuxer; Entry Point: %s", pszFileName));

  size_t len = strlen(fileName);
  if (len > 16) {
    char *bd_path = fileName;
    if(_strcmpi(bd_path+strlen(bd_path) - 16, "\\BDMV\\index.bdmv") == 0) {
      bd_path[strlen(bd_path) - 15] = 0;
    } else if (len > 22 && _strcmpi(bd_path+strlen(bd_path) - 22, "\\BDMV\\MovieObject.bdmv") == 0) {
      bd_path[strlen(bd_path) - 21] = 0;
    } else if (len > 25 && _strnicmp(bd_path+strlen(bd_path) - 25, "\\BDMV\\PLAYLIST\\", 15) == 0) {
      char *playlist = &bd_path[strlen(bd_path) - 10];
      bd_path[strlen(bd_path) - 24] = 0;

      playlist[5] = 0;
      iPlaylist = atoi(playlist);
    } else {
      return E_FAIL;
    }
    // Open BluRay
    BLURAY *bd = bd_open(bd_path, NULL);
    if(!bd) {
      return E_FAIL;
    }
    m_pBD = bd;

    uint32_t timelimit = (iPlaylist != -1) ? 0 : 180;
    uint8_t flags = (iPlaylist != -1) ? TITLES_ALL : TITLES_RELEVANT;

    // Fetch titles
fetchtitles:
    m_nTitleCount = bd_get_titles(bd, flags, timelimit);

    if (m_nTitleCount <= 0) {
      if (timelimit > 0) {
        timelimit = 0;
        goto fetchtitles;
      }
      if (flags != TITLES_ALL) {
        flags = TITLES_ALL;
        goto fetchtitles;
      }
      return E_FAIL;
    }

    DbgLog((LOG_TRACE, 20, L"Found %d titles", m_nTitleCount));
    DbgLog((LOG_TRACE, 20, L" ------ Begin Title Listing ------"));

    uint64_t longest_duration = 0;
    uint32_t title_id = 0;
    boolean found = false;
    for(uint32_t i = 0; i < m_nTitleCount; i++) {
      BLURAY_TITLE_INFO *info = bd_get_title_info(bd, i, 0);
      if (info) {
        DbgLog((LOG_TRACE, 20, L"Title %u, Playlist %u (%u clips, %u chapters), Duration %I64u (%I64u seconds)", i, info->playlist, info->clip_count, info->chapter_count, info->duration, Convert90KhzToDSTime(info->duration) / DSHOW_TIME_BASE));
        if (iPlaylist != -1 && info->playlist == iPlaylist) {
          title_id = i;
          found = true;
        } else if (iPlaylist == -1 && info->duration > longest_duration) {
          title_id = i;
          longest_duration = info->duration;
        }
        bd_free_title_info(info);
      }
      if (found)
        break;
    }
    DbgLog((LOG_TRACE, 20, L" ------ End Title Listing ------"));

    hr = SetTitle(title_id);
  }

  return hr;
}