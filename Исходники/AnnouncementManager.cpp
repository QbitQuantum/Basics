void CAnnouncementManager::Announce(AnnouncementFlag flag, const char *sender, const char *message, CFileItemPtr item, CVariant &data)
{
  if (!item.get())
  {
    Announce(flag, sender, message, data);
    return;
  }

  // Extract db id of item
  CVariant object = data.isNull() || data.isObject() ? data : CVariant::VariantTypeObject;
  CStdString type;
  int id = 0;
  
  if(item->HasPVRChannelInfoTag())
  {
    const PVR::CPVRChannel *channel = item->GetPVRChannelInfoTag();
    id = channel->ChannelID();
    type = "channel";

    object["item"]["title"] = channel->ChannelName();
    object["item"]["channeltype"] = channel->IsRadio() ? "radio" : "tv";

    if (data.isMember("player") && data["player"].isMember("playerid"))
      object["player"]["playerid"] = channel->IsRadio() ? PLAYLIST_MUSIC : PLAYLIST_VIDEO;
  }
  else if (item->HasVideoInfoTag())
  {
    id = item->GetVideoInfoTag()->m_iDbId;

    // TODO: Can be removed once this is properly handled when starting playback of a file
    if (id <= 0 && !item->GetPath().empty() &&
       (!item->HasProperty(LOOKUP_PROPERTY) || item->GetProperty(LOOKUP_PROPERTY).asBoolean()))
    {
      CVideoDatabase videodatabase;
      if (videodatabase.Open())
      {
        CStdString path = item->GetPath();
        CStdString videoInfoTagPath(item->GetVideoInfoTag()->m_strFileNameAndPath);
        if (StringUtils::StartsWith(videoInfoTagPath, "removable://"))
          path = videoInfoTagPath;
        if (videodatabase.LoadVideoInfo(path, *item->GetVideoInfoTag()))
          id = item->GetVideoInfoTag()->m_iDbId;

        videodatabase.Close();
      }
    }

    if (!item->GetVideoInfoTag()->m_type.empty())
      type = item->GetVideoInfoTag()->m_type;
    else
      CVideoDatabase::VideoContentTypeToString((VIDEODB_CONTENT_TYPE)item->GetVideoContentType(), type);

    if (id <= 0)
    {
      // TODO: Can be removed once this is properly handled when starting playback of a file
      item->SetProperty(LOOKUP_PROPERTY, false);

      CStdString title = item->GetVideoInfoTag()->m_strTitle;
      if (title.empty())
        title = item->GetLabel();
      object["item"]["title"] = title;

      switch (item->GetVideoContentType())
      {
      case VIDEODB_CONTENT_MOVIES:
        if (item->GetVideoInfoTag()->m_iYear > 0)
          object["item"]["year"] = item->GetVideoInfoTag()->m_iYear;
        break;
      case VIDEODB_CONTENT_EPISODES:
        if (item->GetVideoInfoTag()->m_iEpisode >= 0)
          object["item"]["episode"] = item->GetVideoInfoTag()->m_iEpisode;
        if (item->GetVideoInfoTag()->m_iSeason >= 0)
          object["item"]["season"] = item->GetVideoInfoTag()->m_iSeason;
        if (!item->GetVideoInfoTag()->m_strShowTitle.empty())
          object["item"]["showtitle"] = item->GetVideoInfoTag()->m_strShowTitle;
        break;
      case VIDEODB_CONTENT_MUSICVIDEOS:
        if (!item->GetVideoInfoTag()->m_strAlbum.empty())
          object["item"]["album"] = item->GetVideoInfoTag()->m_strAlbum;
        if (!item->GetVideoInfoTag()->m_artist.empty())
          object["item"]["artist"] = StringUtils::Join(item->GetVideoInfoTag()->m_artist, " / ");
        break;
      }
    }
  }
  else if (item->HasMusicInfoTag())
  {
    id = item->GetMusicInfoTag()->GetDatabaseId();
    type = MediaTypeSong;

    // TODO: Can be removed once this is properly handled when starting playback of a file
    if (id <= 0 && !item->GetPath().empty() &&
       (!item->HasProperty(LOOKUP_PROPERTY) || item->GetProperty(LOOKUP_PROPERTY).asBoolean()))
    {
      CMusicDatabase musicdatabase;
      if (musicdatabase.Open())
      {
        CSong song;
        if (musicdatabase.GetSongByFileName(item->GetPath(), song, item->m_lStartOffset))
        {
          item->GetMusicInfoTag()->SetSong(song);
          id = item->GetMusicInfoTag()->GetDatabaseId();
        }

        musicdatabase.Close();
      }
    }

    if (id <= 0)
    {
      // TODO: Can be removed once this is properly handled when starting playback of a file
      item->SetProperty(LOOKUP_PROPERTY, false);

      CStdString title = item->GetMusicInfoTag()->GetTitle();
      if (title.empty())
        title = item->GetLabel();
      object["item"]["title"] = title;

      if (item->GetMusicInfoTag()->GetTrackNumber() > 0)
        object["item"]["track"] = item->GetMusicInfoTag()->GetTrackNumber();
      if (!item->GetMusicInfoTag()->GetAlbum().empty())
        object["item"]["album"] = item->GetMusicInfoTag()->GetAlbum();
      if (!item->GetMusicInfoTag()->GetArtist().empty())
        object["item"]["artist"] = item->GetMusicInfoTag()->GetArtist();
    }
  }
  else if (item->IsVideo())
  {
    // video item but has no video info tag.
    type = "movies";
    object["item"]["title"] = item->GetLabel();
  }
  else if (item->HasPictureInfoTag())
  {
    type = "picture";
    object["item"]["file"] = item->GetPath();
  }
  else
    type = "unknown";

  object["item"]["type"] = type;
  if (id > 0)
    object["item"]["id"] = id;

  Announce(flag, sender, message, object);
}