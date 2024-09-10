CGUIViewStateWindowVideoNav::CGUIViewStateWindowVideoNav(const CFileItemList& items) : CGUIViewStateWindowVideo(items)
{
  SortAttribute sortAttributes = SortAttributeNone;
  if (CSettings::GetInstance().GetBool(CSettings::SETTING_FILELISTS_IGNORETHEWHENSORTING))
    sortAttributes = SortAttributeIgnoreArticle;

  if (items.IsVirtualDirectoryRoot())
  {
    AddSortMethod(SortByNone, 551, LABEL_MASKS("%F", "%I", "%L", ""));  // Filename, Size | Label, empty
    SetSortMethod(SortByNone);

    SetViewAsControl(DEFAULT_VIEW_LIST);

    SetSortOrder(SortOrderNone);
  }
  else if (items.IsVideoDb())
  {
    NODE_TYPE NodeType=CVideoDatabaseDirectory::GetDirectoryChildType(items.GetPath());
    CQueryParams params;
    CVideoDatabaseDirectory::GetQueryParams(items.GetPath(),params);

    switch (NodeType)
    {
    case NODE_TYPE_MOVIES_OVERVIEW:
    case NODE_TYPE_TVSHOWS_OVERVIEW:
    case NODE_TYPE_MUSICVIDEOS_OVERVIEW:
    case NODE_TYPE_OVERVIEW:
      {
        AddSortMethod(SortByNone, 551, LABEL_MASKS("%F", "%I", "%L", ""));  // Filename, Size | Label, empty

        SetSortMethod(SortByNone);

        SetViewAsControl(DEFAULT_VIEW_LIST);

        SetSortOrder(SortOrderNone);
      }
      break;
    case NODE_TYPE_DIRECTOR:
    case NODE_TYPE_ACTOR:
      {
        AddSortMethod(SortByLabel, 551, LABEL_MASKS("%T", "%R", "%L", ""));  // Title, Rating | Label, empty
        AddSortMethod(SortByRelevance, 38026, LABEL_MASKS("%T", "%c", "%L", "%c"));  // Title, Actor's appearences (Relevance) | Label, Actor's appearences (Relevance)
        SetSortMethod(SortByLabel);

        const CViewState *viewState = CViewStateSettings::GetInstance().Get("videonavactors");
        SetViewAsControl(viewState->m_viewMode);
        SetSortOrder(viewState->m_sortDescription.sortOrder);
      }
      break;
    case NODE_TYPE_YEAR:
      {
        AddSortMethod(SortByLabel, 562, LABEL_MASKS("%T", "%R", "%L", ""));  // Title, Rating | Label, empty
        SetSortMethod(SortByLabel);

        const CViewState *viewState = CViewStateSettings::GetInstance().Get("videonavyears");
        SetViewAsControl(viewState->m_viewMode);
        SetSortOrder(viewState->m_sortDescription.sortOrder);
      }
      break;
    case NODE_TYPE_SEASONS:
      {
        AddSortMethod(SortBySortTitle, 556, LABEL_MASKS("%L", "","%L",""));  // Label, empty | Label, empty
        SetSortMethod(SortBySortTitle);

        const CViewState *viewState = CViewStateSettings::GetInstance().Get("videonavseasons");
        SetViewAsControl(viewState->m_viewMode);
        SetSortOrder(viewState->m_sortDescription.sortOrder);
      }
      break;
    case NODE_TYPE_TITLE_TVSHOWS:
      {
        AddSortMethod(SortBySortTitle, sortAttributes, 556, LABEL_MASKS("%T", "%M", "%T", "%M"));  // Title, #Episodes | Title, #Episodes

        AddSortMethod(SortByNumberOfEpisodes, 20360, LABEL_MASKS("%L", "%M", "%L", "%M"));  // Label, #Episodes | Label, #Episodes
        AddSortMethod(SortByLastPlayed, 568, LABEL_MASKS("%T", "%p", "%T", "%p"));  // Title, #Last played | Title, #Last played
        AddSortMethod(SortByDateAdded, 570, LABEL_MASKS("%T", "%a", "%T", "%a"));  // Title, DateAdded | Title, DateAdded
        AddSortMethod(SortByYear, 562, LABEL_MASKS("%L","%Y","%L","%Y")); // Label, Year | Label, Year
        AddSortMethod(SortByUserRating, 38018, LABEL_MASKS("%T", "%r", "%T", "%r"));  // Title, Userrating | Title, Userrating
        SetSortMethod(SortByLabel);

        const CViewState *viewState = CViewStateSettings::GetInstance().Get("videonavtvshows");
        SetViewAsControl(viewState->m_viewMode);
        SetSortOrder(viewState->m_sortDescription.sortOrder);
      }
      break;
    case NODE_TYPE_MUSICVIDEOS_ALBUM:
    case NODE_TYPE_GENRE:
    case NODE_TYPE_COUNTRY:
    case NODE_TYPE_STUDIO:
      {
        AddSortMethod(SortByLabel, 551, LABEL_MASKS("%T", "%R", "%L", ""));  // Title, Rating | Label, empty
        SetSortMethod(SortByLabel);

        const CViewState *viewState = CViewStateSettings::GetInstance().Get("videonavgenres");
        SetViewAsControl(viewState->m_viewMode);
        SetSortOrder(viewState->m_sortDescription.sortOrder);
      }
      break;
    case NODE_TYPE_SETS:
      {
        AddSortMethod(SortByLabel, sortAttributes, 551, LABEL_MASKS("%T","%R", "%T","%R"));  // Title, Rating | Title, Rating

        AddSortMethod(SortByYear, 562, LABEL_MASKS("%T", "%Y", "%T", "%Y"));  // Title, Year | Title, Year
        AddSortMethod(SortByRating, 563, LABEL_MASKS("%T", "%R", "%T", "%R"));  // Title, Rating | Title, Rating
        AddSortMethod(SortByDateAdded, 570, LABEL_MASKS("%T", "%a", "%T", "%a"));  // Title, DateAdded | Title, DateAdded

        if (CMediaSettings::GetInstance().GetWatchedMode(items.GetContent()) == WatchedModeAll)
          AddSortMethod(SortByPlaycount, 567, LABEL_MASKS("%T", "%V", "%T", "%V"));  // Title, Playcount | Title, Playcount

        SetSortMethod(SortByLabel);

        const CViewState *viewState = CViewStateSettings::GetInstance().Get("videonavgenres");
        SetViewAsControl(viewState->m_viewMode);
        SetSortOrder(viewState->m_sortDescription.sortOrder);
      }
      break;
    case NODE_TYPE_TAGS:
      {
        AddSortMethod(SortByLabel, sortAttributes, 551, LABEL_MASKS("%T","", "%T",""));  // Title, empty | Title, empty
        SetSortMethod(SortByLabel);
        
        const CViewState *viewState = CViewStateSettings::GetInstance().Get("videonavgenres");
        SetViewAsControl(viewState->m_viewMode);
        SetSortOrder(viewState->m_sortDescription.sortOrder);
      }
      break;
    case NODE_TYPE_EPISODES:
      {
        if (params.GetSeason() > -1)
        {
          AddSortMethod(SortByEpisodeNumber, 20359, LABEL_MASKS("%E. %T","%R"));  // Episode. Title, Rating | empty, empty
          AddSortMethod(SortByRating, 563, LABEL_MASKS("%E. %T", "%R"));  // Episode. Title, Rating | empty, empty
          AddSortMethod(SortByUserRating, 38018, LABEL_MASKS("%E. %T", "%r"));  // Episode. Title, Userrating | empty, empty
          AddSortMethod(SortByMPAA, 20074, LABEL_MASKS("%E. %T", "%O"));  // Episode. Title, MPAA | empty, empty
          AddSortMethod(SortByProductionCode, 20368, LABEL_MASKS("%E. %T","%P", "%E. %T","%P"));  // Episode. Title, ProductionCode | Episode. Title, ProductionCode
          AddSortMethod(SortByDate, 552, LABEL_MASKS("%E. %T","%J","%E. %T","%J"));  // Episode. Title, Date | Episode. Title, Date

          if (CMediaSettings::GetInstance().GetWatchedMode(items.GetContent()) == WatchedModeAll)
            AddSortMethod(SortByPlaycount, 567, LABEL_MASKS("%E. %T", "%V"));  // Episode. Title, Playcount | empty, empty
        }
        else
        {
          AddSortMethod(SortByEpisodeNumber, 20359, LABEL_MASKS("%H. %T","%R"));  // Order. Title, Rating | emtpy, empty
          AddSortMethod(SortByRating, 563, LABEL_MASKS("%H. %T", "%R"));  // Order. Title, Rating | emtpy, empty
          AddSortMethod(SortByUserRating, 38018, LABEL_MASKS("%H. %T", "%r"));  // Order. Title, Userrating | emtpy, empty
          AddSortMethod(SortByMPAA, 20074, LABEL_MASKS("%H. %T", "%O"));  // Order. Title, MPAA | emtpy, empty
          AddSortMethod(SortByProductionCode, 20368, LABEL_MASKS("%H. %T","%P", "%H. %T","%P"));  // Order. Title, ProductionCode | Episode. Title, ProductionCode
          AddSortMethod(SortByDate, 552, LABEL_MASKS("%H. %T","%J","%H. %T","%J"));  // Order. Title, Date | Episode. Title, Date

          if (CMediaSettings::GetInstance().GetWatchedMode(items.GetContent()) == WatchedModeAll)
            AddSortMethod(SortByPlaycount, 567, LABEL_MASKS("%H. %T", "%V"));  // Order. Title, Playcount | empty, empty
        }
        AddSortMethod(SortByLabel, sortAttributes, 551, LABEL_MASKS("%T","%R"));  // Title, Rating | empty, empty

        const CViewState *viewState = CViewStateSettings::GetInstance().Get("videonavepisodes");
        SetSortMethod(viewState->m_sortDescription);
        SetViewAsControl(viewState->m_viewMode);
        SetSortOrder(viewState->m_sortDescription.sortOrder);
        break;
      }
    case NODE_TYPE_RECENTLY_ADDED_EPISODES:
      {
        AddSortMethod(SortByNone, 552, LABEL_MASKS("%Z - %H. %T", "%R"));  // TvShow - Order. Title, Rating | empty, empty
        SetSortMethod(SortByNone);

        SetViewAsControl(CViewStateSettings::GetInstance().Get("videonavepisodes")->m_viewMode);
        SetSortOrder(SortOrderNone);

        break;
      }
    case NODE_TYPE_TITLE_MOVIES:
      {
        if (params.GetSetId() > -1) // Is this a listing within a set?
        {
          AddSortMethod(SortByYear, 562, LABEL_MASKS("%T", "%Y"));  // Title, Year | empty, empty
          AddSortMethod(SortBySortTitle, sortAttributes, 556, LABEL_MASKS("%T", "%R"));  // Title, Rating | empty, empty
        }
        else
        {
          AddSortMethod(SortBySortTitle, sortAttributes, 556, LABEL_MASKS("%T", "%R", "%T", "%R"));  // Title, Rating | Title, Rating
          AddSortMethod(SortByYear, 562, LABEL_MASKS("%T", "%Y", "%T", "%Y"));  // Title, Year | Title, Year
        }
        AddSortMethod(SortByRating, 563, LABEL_MASKS("%T", "%R", "%T", "%R"));  // Title, Rating | Title, Rating
        AddSortMethod(SortByUserRating, 38018, LABEL_MASKS("%T", "%r", "%T", "%r"));  // Title, Userrating | Title, Userrating
        AddSortMethod(SortByMPAA, 20074, LABEL_MASKS("%T", "%O"));  // Title, MPAA | empty, empty
        AddSortMethod(SortByTime, 180, LABEL_MASKS("%T", "%D"));  // Title, Duration | empty, empty
        AddSortMethod(SortByDateAdded, 570, LABEL_MASKS("%T", "%a", "%T", "%a"));  // Title, DateAdded | Title, DateAdded

        if (CMediaSettings::GetInstance().GetWatchedMode(items.GetContent()) == WatchedModeAll)
          AddSortMethod(SortByPlaycount, 567, LABEL_MASKS("%T", "%V", "%T", "%V"));  // Title, Playcount | Title, Playcount

        const CViewState *viewState = CViewStateSettings::GetInstance().Get("videonavtitles");
        if (params.GetSetId() > -1)
        {
          SetSortMethod(SortByYear);
          SetSortOrder(SortOrderAscending);
        }
        else
        {
          SetSortMethod(viewState->m_sortDescription);
          SetSortOrder(viewState->m_sortDescription.sortOrder);
        }

        SetViewAsControl(viewState->m_viewMode);
      }
      break;
      case NODE_TYPE_TITLE_MUSICVIDEOS:
      {
        AddSortMethod(SortByLabel, sortAttributes, 551, LABEL_MASKS("%T", "%Y"));  // Title, Year | empty, empty
        AddSortMethod(SortByMPAA, 20074, LABEL_MASKS("%T", "%O"));
        AddSortMethod(SortByYear, 562, LABEL_MASKS("%T", "%Y"));  // Title, Year | empty, empty
        AddSortMethod(SortByArtist, sortAttributes, 557, LABEL_MASKS("%A - %T", "%Y"));  // Artist - Title, Year | empty, empty
        AddSortMethod(SortByAlbum, sortAttributes, 558, LABEL_MASKS("%B - %T", "%Y"));  // Album - Title, Year | empty, empty

        if (CMediaSettings::GetInstance().GetWatchedMode(items.GetContent()) == WatchedModeAll)
          AddSortMethod(SortByPlaycount, 567, LABEL_MASKS("%T", "%V"));  // Title, Playcount | empty, empty

        std::string strTrack=CSettings::GetInstance().GetString(CSettings::SETTING_MUSICFILES_TRACKFORMAT);
        AddSortMethod(SortByTrackNumber, 554, LABEL_MASKS(strTrack, "%N"));  // Userdefined, Track Number | empty, empty

        const CViewState *viewState = CViewStateSettings::GetInstance().Get("videonavmusicvideos");
        SetSortMethod(viewState->m_sortDescription);
        SetViewAsControl(viewState->m_viewMode);
        SetSortOrder(viewState->m_sortDescription.sortOrder);
      }
      break;
    case NODE_TYPE_RECENTLY_ADDED_MOVIES:
      {
        AddSortMethod(SortByNone, 552, LABEL_MASKS("%T", "%R"));  // Title, Rating | empty, empty
        SetSortMethod(SortByNone);

        SetViewAsControl(CViewStateSettings::GetInstance().Get("videonavtitles")->m_viewMode);

        SetSortOrder(SortOrderNone);
      }
      break;
    case NODE_TYPE_RECENTLY_ADDED_MUSICVIDEOS:
      {
        AddSortMethod(SortByNone, 552, LABEL_MASKS("%A - %T", "%Y"));  // Artist - Title, Year | empty, empty
        SetSortMethod(SortByNone);

        SetViewAsControl(CViewStateSettings::GetInstance().Get("videonavmusicvideos")->m_viewMode);

        SetSortOrder(SortOrderNone);
      }
      break;
    default:
      break;
    }
  }
  else
  {
    AddSortMethod(SortByLabel, sortAttributes, 551, LABEL_MASKS("%L", "%I", "%L", ""));  // Label, Size | Label, empty
    AddSortMethod(SortBySize, 553, LABEL_MASKS("%L", "%I", "%L", "%I"));  // Label, Size | Label, Size
    AddSortMethod(SortByDate, 552, LABEL_MASKS("%L", "%J", "%L", "%J"));  // Label, Date | Label, Date
    AddSortMethod(SortByFile, 561, LABEL_MASKS("%L", "%I", "%L", ""));  // Label, Size | Label, empty
    
    const CViewState *viewState = CViewStateSettings::GetInstance().Get("videofiles");
    SetSortMethod(viewState->m_sortDescription);
    SetViewAsControl(viewState->m_viewMode);
    SetSortOrder(viewState->m_sortDescription.sortOrder);
  }
  LoadViewState(items.GetPath(), WINDOW_VIDEO_NAV);
}