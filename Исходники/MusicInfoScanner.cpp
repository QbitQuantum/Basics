int CMusicInfoScanner::RetrieveMusicInfo(const std::string& strDirectory, CFileItemList& items)
{
  MAPSONGS songsMap;

  // get all information for all files in current directory from database, and remove them
  if (m_musicDatabase.RemoveSongsFromPath(strDirectory, songsMap))
    m_needsCleanup = true;

  CFileItemList scannedItems;
  if (ScanTags(items, scannedItems) == INFO_CANCELLED || scannedItems.Size() == 0)
    return 0;

  VECALBUMS albums;
  FileItemsToAlbums(scannedItems, albums, &songsMap);
  FindArtForAlbums(albums, items.GetPath());

  int numAdded = 0;
  ADDON::AddonPtr addon;
  ADDON::ScraperPtr albumScraper;
  ADDON::ScraperPtr artistScraper;
  if(ADDON::CAddonMgr::GetInstance().GetDefault(ADDON::ADDON_SCRAPER_ALBUMS, addon))
    albumScraper = std::dynamic_pointer_cast<ADDON::CScraper>(addon);

  if(ADDON::CAddonMgr::GetInstance().GetDefault(ADDON::ADDON_SCRAPER_ARTISTS, addon))
    artistScraper = std::dynamic_pointer_cast<ADDON::CScraper>(addon);

  // Add each album
  for (VECALBUMS::iterator album = albums.begin(); album != albums.end(); ++album)
  {
    if (m_bStop)
      break;

    // mark albums without a title as singles
    if (album->strAlbum.empty())
      album->releaseType = CAlbum::Single;

    album->strPath = strDirectory;
    m_musicDatabase.AddAlbum(*album);

    // Yuk - this is a kludgy way to do what we want to do, but it will work to sort
    // out artist fanart until we can restructure the artist fanart to work more
    // like the album fanart. This has to be done after we've added the album so
    // we have the artist IDs to update, but before we call UpdateDatabaseArtistInfo.
    if (albums.size() == 1 &&
        !album->artistCredits.empty() &&
        !StringUtils::EqualsNoCase(album->artistCredits[0].GetArtist(), "various artists") &&
        !StringUtils::EqualsNoCase(album->artistCredits[0].GetArtist(), "various"))
    {
      CArtist artist;
      if (m_musicDatabase.GetArtist(album->artistCredits[0].GetArtistId(), artist))
      {
        artist.strPath = URIUtils::GetParentPath(strDirectory);
        m_musicDatabase.SetArtForItem(artist.idArtist, MediaTypeArtist, GetArtistArtwork(artist));
      }
    }

    if ((m_flags & SCAN_ONLINE))
    {
      if (!albumScraper || !artistScraper)
        continue;

      INFO_RET albumScrapeStatus = INFO_NOT_FOUND;
      if (!m_musicDatabase.HasAlbumBeenScraped(album->idAlbum))
        albumScrapeStatus = UpdateDatabaseAlbumInfo(*album, albumScraper, false);

      if (albumScrapeStatus == INFO_ADDED)
      {
        for (VECARTISTCREDITS::const_iterator artistCredit  = album->artistCredits.begin();
                                              artistCredit != album->artistCredits.end();
                                            ++artistCredit)
        {
          if (m_bStop)
            break;

          if (!m_musicDatabase.HasArtistBeenScraped(artistCredit->GetArtistId()))
          {
            CArtist artist;
            m_musicDatabase.GetArtist(artistCredit->GetArtistId(), artist);
            UpdateDatabaseArtistInfo(artist, artistScraper, false);
          }
        }

        for (VECSONGS::iterator song  = album->songs.begin();
                                song != album->songs.end();
                                ++song)
        {
          if (m_bStop)
            break;

          for (VECARTISTCREDITS::const_iterator artistCredit  = song->artistCredits.begin();
                                                artistCredit != song->artistCredits.end();
                                              ++artistCredit)
          {
            if (m_bStop)
              break;

            CMusicArtistInfo musicArtistInfo;
            if (!m_musicDatabase.HasArtistBeenScraped(artistCredit->GetArtistId()))
            {
              CArtist artist;
              m_musicDatabase.GetArtist(artistCredit->GetArtistId(), artist);
              UpdateDatabaseArtistInfo(artist, artistScraper, false);
            }
          }
        }
      }
    }
    numAdded += album->songs.size();
  }

  if (m_handle)
    m_handle->SetTitle(g_localizeStrings.Get(505));

  return numAdded;
}