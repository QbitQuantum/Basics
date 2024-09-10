void CVideoInfoTag::ToSortable(SortItem& sortable, Field field) const
{
  switch (field)
  {
  case FieldDirector:                 sortable[FieldDirector] = m_director; break;
  case FieldWriter:                   sortable[FieldWriter] = m_writingCredits; break;
  case FieldGenre:                    sortable[FieldGenre] = m_genre; break;
  case FieldCountry:                  sortable[FieldCountry] = m_country; break;
  case FieldTagline:                  sortable[FieldTagline] = m_strTagLine; break;
  case FieldPlotOutline:              sortable[FieldPlotOutline] = m_strPlotOutline; break;
  case FieldPlot:                     sortable[FieldPlot] = m_strPlot; break;
  case FieldTitle:
  {
    // make sure not to overwrite an existing title with an empty one
    std::string title = m_strTitle;
    if (!title.empty() || sortable.find(FieldTitle) == sortable.end())
      sortable[FieldTitle] = title;
    break;
  }
  case FieldVotes:                    sortable[FieldVotes] = m_strVotes; break;
  case FieldStudio:                   sortable[FieldStudio] = m_studio; break;
  case FieldTrailer:                  sortable[FieldTrailer] = m_strTrailer; break;
  case FieldSet:                      sortable[FieldSet] = m_strSet; break;
  case FieldTime:                     sortable[FieldTime] = GetDuration(); break;
  case FieldFilename:                 sortable[FieldFilename] = m_strFile; break;
  case FieldMPAA:                     sortable[FieldMPAA] = m_strMPAARating; break;
  case FieldPath:
  {
    // make sure not to overwrite an existing path with an empty one
    std::string path = GetPath();
    if (!path.empty() || sortable.find(FieldPath) == sortable.end())
      sortable[FieldPath] = path;
    break;
  }
  case FieldSortTitle:                sortable[FieldSortTitle] = m_strSortTitle; break;
  case FieldTvShowStatus:             sortable[FieldTvShowStatus] = m_strStatus; break;
  case FieldProductionCode:           sortable[FieldProductionCode] = m_strProductionCode; break;
  case FieldAirDate:                  sortable[FieldAirDate] = m_firstAired.IsValid() ? m_firstAired.GetAsDBDate() : (m_premiered.IsValid() ? m_premiered.GetAsDBDate() : StringUtils::Empty); break;
  case FieldTvShowTitle:              sortable[FieldTvShowTitle] = m_strShowTitle; break;
  case FieldAlbum:                    sortable[FieldAlbum] = m_strAlbum; break;
  case FieldArtist:                   sortable[FieldArtist] = m_artist; break;
  case FieldPlaycount:                sortable[FieldPlaycount] = m_playCount; break;
  case FieldLastPlayed:               sortable[FieldLastPlayed] = m_lastPlayed.IsValid() ? m_lastPlayed.GetAsDBDateTime() : StringUtils::Empty; break;
  case FieldTop250:                   sortable[FieldTop250] = m_iTop250; break;
  case FieldYear:                     sortable[FieldYear] = m_iYear; break;
  case FieldSeason:                   sortable[FieldSeason] = m_iSeason; break;
  case FieldEpisodeNumber:            sortable[FieldEpisodeNumber] = m_iEpisode; break;
  case FieldNumberOfEpisodes:         sortable[FieldNumberOfEpisodes] = m_iEpisode; break;
  case FieldNumberOfWatchedEpisodes:  sortable[FieldNumberOfWatchedEpisodes] = m_iEpisode; break;
  case FieldEpisodeNumberSpecialSort: sortable[FieldEpisodeNumberSpecialSort] = m_iSpecialSortEpisode; break;
  case FieldSeasonSpecialSort:        sortable[FieldSeasonSpecialSort] = m_iSpecialSortSeason; break;
  case FieldRating:                   sortable[FieldRating] = m_fRating; break;
  case FieldUserRating:               sortable[FieldUserRating] = m_iUserRating; break;
  case FieldId:                       sortable[FieldId] = m_iDbId; break;
  case FieldTrackNumber:              sortable[FieldTrackNumber] = m_iTrack; break;
  case FieldTag:                      sortable[FieldTag] = m_tags; break;

  case FieldVideoResolution:          sortable[FieldVideoResolution] = m_streamDetails.GetVideoHeight(); break;
  case FieldVideoAspectRatio:         sortable[FieldVideoAspectRatio] = m_streamDetails.GetVideoAspect(); break;
  case FieldVideoCodec:               sortable[FieldVideoCodec] = m_streamDetails.GetVideoCodec(); break;
  case FieldStereoMode:               sortable[FieldStereoMode] = m_streamDetails.GetStereoMode(); break;

  case FieldAudioChannels:            sortable[FieldAudioChannels] = m_streamDetails.GetAudioChannels(); break;
  case FieldAudioCodec:               sortable[FieldAudioCodec] = m_streamDetails.GetAudioCodec(); break;
  case FieldAudioLanguage:            sortable[FieldAudioLanguage] = m_streamDetails.GetAudioLanguage(); break;

  case FieldSubtitleLanguage:         sortable[FieldSubtitleLanguage] = m_streamDetails.GetSubtitleLanguage(); break;

  case FieldInProgress:               sortable[FieldInProgress] = m_resumePoint.IsPartWay(); break;
  case FieldDateAdded:                sortable[FieldDateAdded] = m_dateAdded.IsValid() ? m_dateAdded.GetAsDBDateTime() : StringUtils::Empty; break;
  case FieldMediaType:                sortable[FieldMediaType] = m_type; break;
  default: break;
  }
}