bool CPlayListPlayer::Play(int iSong, bool bAutoPlay /* = false */, bool bPlayPrevious /* = false */)
{
  if (m_iCurrentPlayList == PLAYLIST_NONE)
    return false;

  CPlayList& playlist = GetPlaylist(m_iCurrentPlayList);
  if (playlist.size() <= 0) 
    return false;
  if (iSong < 0) 
    iSong = 0;
  if (iSong >= playlist.size()) 
    iSong = playlist.size() - 1;

  // check if the item itself is a playlist, and can be expanded
  // only allow a few levels, this could end up in a loop
  // if they refer to each other in a loop
  for(int i=0;i<5;i++)
  {
     if(!playlist.Expand(iSong))
        break;
  }

  m_iCurrentSong = iSong;
  CFileItemPtr item = playlist[m_iCurrentSong];
  playlist.SetPlayed(true);

  m_bPlaybackStarted = false;

  unsigned int playAttempt = XbmcThreads::SystemClockMillis();
  if (!g_application.PlayFile(*item, bAutoPlay))
  {
    CLog::Log(LOGERROR,"Playlist Player: skipping unplayable item: %i, path [%s]", m_iCurrentSong, item->GetPath().c_str());
    playlist.SetUnPlayable(m_iCurrentSong);

    // abort on 100 failed CONSECTUTIVE songs
    if (!m_iFailedSongs)
      m_failedSongsStart = playAttempt;
    m_iFailedSongs++;
    if ((m_iFailedSongs >= g_advancedSettings.m_playlistRetries && g_advancedSettings.m_playlistRetries >= 0)
        || ((XbmcThreads::SystemClockMillis() - m_failedSongsStart  >= (unsigned int)g_advancedSettings.m_playlistTimeout * 1000) && g_advancedSettings.m_playlistTimeout))
    {
      CLog::Log(LOGDEBUG,"Playlist Player: one or more items failed to play... aborting playback");

      // open error dialog
      CGUIDialogOK::ShowAndGetInput(16026, 16027, 16029, 0);

      CGUIMessage msg(GUI_MSG_PLAYLISTPLAYER_STOPPED, 0, 0, m_iCurrentPlayList, m_iCurrentSong);
      g_windowManager.SendThreadMessage(msg);
      Reset();
      GetPlaylist(m_iCurrentPlayList).Clear();
      m_iCurrentPlayList = PLAYLIST_NONE;
      m_iFailedSongs = 0;
      m_failedSongsStart = 0;
      return false;
    }

    // how many playable items are in the playlist?
    if (playlist.GetPlayable() > 0)
    {
      return bPlayPrevious ? PlayPrevious() : PlayNext();
    }
    // none? then abort playback
    else
    {
      CLog::Log(LOGDEBUG,"Playlist Player: no more playable items... aborting playback");
      CGUIMessage msg(GUI_MSG_PLAYLISTPLAYER_STOPPED, 0, 0, m_iCurrentPlayList, m_iCurrentSong);
      g_windowManager.SendThreadMessage(msg);
      Reset();
      m_iCurrentPlayList = PLAYLIST_NONE;
      return false;
    }
  }

  // TODO - move the above failure logic and the below success logic
  //        to callbacks instead so we don't rely on the return value
  //        of PlayFile()

  // consecutive error counter so reset if the current item is playing
  m_iFailedSongs = 0;
  m_failedSongsStart = 0;
  m_bPlaybackStarted = true;
  m_bPlayedFirstFile = true;
  return true;
}