bool CGUIWindowMusicNav::GetDirectory(const std::string &strDirectory, CFileItemList &items)
{
    if (strDirectory.empty())
        AddSearchFolder();

    bool bResult = CGUIWindowMusicBase::GetDirectory(strDirectory, items);
    if (bResult)
    {
        if (items.IsPlayList())
            OnRetrieveMusicInfo(items);
    }

    // update our content in the info manager
    if (StringUtils::StartsWithNoCase(strDirectory, "videodb://") || items.IsVideoDb())
    {
        CVideoDatabaseDirectory dir;
        VIDEODATABASEDIRECTORY::NODE_TYPE node = dir.GetDirectoryChildType(items.GetPath());
        if (node == VIDEODATABASEDIRECTORY::NODE_TYPE_TITLE_MUSICVIDEOS ||
                node == VIDEODATABASEDIRECTORY::NODE_TYPE_RECENTLY_ADDED_MUSICVIDEOS)
            items.SetContent("musicvideos");
        else if (node == VIDEODATABASEDIRECTORY::NODE_TYPE_GENRE)
            items.SetContent("genres");
        else if (node == VIDEODATABASEDIRECTORY::NODE_TYPE_COUNTRY)
            items.SetContent("countries");
        else if (node == VIDEODATABASEDIRECTORY::NODE_TYPE_ACTOR)
            items.SetContent("artists");
        else if (node == VIDEODATABASEDIRECTORY::NODE_TYPE_DIRECTOR)
            items.SetContent("directors");
        else if (node == VIDEODATABASEDIRECTORY::NODE_TYPE_STUDIO)
            items.SetContent("studios");
        else if (node == VIDEODATABASEDIRECTORY::NODE_TYPE_YEAR)
            items.SetContent("years");
        else if (node == VIDEODATABASEDIRECTORY::NODE_TYPE_MUSICVIDEOS_ALBUM)
            items.SetContent("albums");
        else if (node == VIDEODATABASEDIRECTORY::NODE_TYPE_TAGS)
            items.SetContent("tags");
        else
            items.SetContent("");
    }
    else if (StringUtils::StartsWithNoCase(strDirectory, "musicdb://") || items.IsMusicDb())
    {
        CMusicDatabaseDirectory dir;
        NODE_TYPE node = dir.GetDirectoryChildType(items.GetPath());
        if (node == NODE_TYPE_ALBUM ||
                node == NODE_TYPE_ALBUM_RECENTLY_ADDED ||
                node == NODE_TYPE_ALBUM_RECENTLY_PLAYED ||
                node == NODE_TYPE_ALBUM_TOP100 ||
                node == NODE_TYPE_ALBUM_COMPILATIONS ||
                node == NODE_TYPE_YEAR_ALBUM)
            items.SetContent("albums");
        else if (node == NODE_TYPE_ARTIST)
            items.SetContent("artists");
        else if (node == NODE_TYPE_SONG ||
                 node == NODE_TYPE_SONG_TOP100 ||
                 node == NODE_TYPE_SINGLES ||
                 node == NODE_TYPE_ALBUM_RECENTLY_ADDED_SONGS ||
                 node == NODE_TYPE_ALBUM_RECENTLY_PLAYED_SONGS ||
                 node == NODE_TYPE_ALBUM_COMPILATIONS_SONGS ||
                 node == NODE_TYPE_ALBUM_TOP100_SONGS ||
                 node == NODE_TYPE_YEAR_SONG)
            items.SetContent("songs");
        else if (node == NODE_TYPE_GENRE)
            items.SetContent("genres");
        else if (node == NODE_TYPE_YEAR)
            items.SetContent("years");
        else
            items.SetContent("");
    }
    else if (items.IsPlayList())
        items.SetContent("songs");
    else if (URIUtils::PathEquals(strDirectory, "special://musicplaylists/") ||
             URIUtils::PathEquals(strDirectory, "library://music/playlists.xml/"))
        items.SetContent("playlists");
    else if (URIUtils::PathEquals(strDirectory, "plugin://music/"))
        items.SetContent("plugins");
    else if (items.IsAddonsPath())
        items.SetContent("addons");
    else if (!items.IsSourcesPath() && !items.IsVirtualDirectoryRoot() &&
             !items.IsLibraryFolder() && !items.IsPlugin() && !items.IsSmartPlayList())
        items.SetContent("files");

    return bResult;
}