CGUIViewStateMusicSmartPlaylist::CGUIViewStateMusicSmartPlaylist(const CFileItemList& items) : CGUIViewStateWindowMusic(items)
{
  SortAttribute sortAttribute = SortAttributeNone;
  if (CSettings::GetInstance().GetBool(CSettings::SETTING_FILELISTS_IGNORETHEWHENSORTING))
    sortAttribute = SortAttributeIgnoreArticle;

  const CViewState *viewState = CViewStateSettings::GetInstance().Get("musicnavsongs");

  if (items.GetContent() == "songs" || items.GetContent() == "mixed") 
  {
    std::string strTrackLeft=CSettings::GetInstance().GetString(CSettings::SETTING_MUSICFILES_TRACKFORMAT);
    std::string strTrackRight=CSettings::GetInstance().GetString(CSettings::SETTING_MUSICFILES_TRACKFORMATRIGHT);

    AddSortMethod(SortByTrackNumber, 554, LABEL_MASKS(strTrackLeft, strTrackRight));  // Userdefined, Userdefined| empty, empty
    AddSortMethod(SortByTitle, sortAttribute, 556, LABEL_MASKS("%T - %A", "%D"));  // Title, Artist, Duration| empty, empty
    AddSortMethod(SortByAlbum, sortAttribute, 558, LABEL_MASKS("%B - %T - %A", "%D"));  // Album, Titel, Artist, Duration| empty, empty
    AddSortMethod(SortByArtist, sortAttribute, 557, LABEL_MASKS("%A - %T", "%D"));  // Artist, Titel, Duration| empty, empty
    AddSortMethod(SortByArtistThenYear, sortAttribute, 578, LABEL_MASKS("%A - %T", "%D"));  // Artist, Titel, Duration| empty, empty
    AddSortMethod(SortByLabel, sortAttribute, 551, LABEL_MASKS(strTrackLeft, strTrackRight));
    AddSortMethod(SortByTime, 180, LABEL_MASKS("%T - %A", "%D"));  // Titel, Artist, Duration| empty, empty
    AddSortMethod(SortByRating, 563, LABEL_MASKS("%T - %A", "%R"));  // Titel, Artist, Rating| empty, empty

    if (items.IsSmartPlayList() || items.IsLibraryFolder())
      AddPlaylistOrder(items, LABEL_MASKS(strTrackLeft, strTrackRight));
    else
    {
      SetSortMethod(viewState->m_sortDescription);
      SetSortOrder(viewState->m_sortDescription.sortOrder);
    }

    SetViewAsControl(CViewStateSettings::GetInstance().Get("musicnavsongs")->m_viewMode);
  } 
  else if (items.GetContent() == "albums") 
  {
    std::string strAlbumLeft = g_advancedSettings.m_strMusicLibraryAlbumFormat;
    if (strAlbumLeft.empty())
      strAlbumLeft = "%B"; // album
    std::string strAlbumRight = g_advancedSettings.m_strMusicLibraryAlbumFormatRight;
    if (strAlbumRight.empty())
      strAlbumRight = "%A"; // artist

    // album
    AddSortMethod(SortByAlbum, sortAttribute, 558, LABEL_MASKS("%F", "", strAlbumLeft, strAlbumRight));  // Filename, empty | Userdefined, Userdefined
    // artist
    AddSortMethod(SortByArtist, sortAttribute, 557, LABEL_MASKS("%F", "", strAlbumLeft, strAlbumRight));  // Filename, empty | Userdefined, Userdefined
    // artist / year
    AddSortMethod(SortByArtistThenYear, sortAttribute, 578, LABEL_MASKS("%F", "", strAlbumLeft, strAlbumRight));  // Filename, empty | Userdefined, Userdefined
    // year
    AddSortMethod(SortByYear, 562, LABEL_MASKS("%F", "", strAlbumLeft, strAlbumRight));

    if (items.IsSmartPlayList() || items.IsLibraryFolder())
      AddPlaylistOrder(items, LABEL_MASKS("%F", "", strAlbumLeft, strAlbumRight));
    else
    {
      SetSortMethod(viewState->m_sortDescription);
      SetSortOrder(viewState->m_sortDescription.sortOrder);
    }

    SetViewAsControl(CViewStateSettings::GetInstance().Get("musicnavalbums")->m_viewMode);
  } 
  else 
  {
    CLog::Log(LOGERROR,"Music Smart Playlist must be one of songs, mixed or albums");
  }
  
  LoadViewState(items.GetPath(), WINDOW_MUSIC_NAV);
}