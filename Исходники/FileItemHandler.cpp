bool CFileItemHandler::GetField(const std::string &field, const CVariant &info, const CFileItemPtr &item, CVariant &result, bool &fetchedArt, CThumbLoader *thumbLoader /* = NULL */)
{
  if (result.isMember(field) && !result[field].empty())
    return true;

  // overwrite serialized values
  if (item)
  {
    if (field == "mimetype" && item->GetMimeType().empty())
    {
      item->FillInMimeType(false);
      result[field] = item->GetMimeType();
      return true;
    }
  }

  // check for serialized values
  if (info.isMember(field) && !info[field].isNull())
  {
    result[field] = info[field];
    return true;
  }

  // check if the field requires special handling
  if (item)
  {
    if (item->IsAlbum())
    {
      if (field == "albumlabel")
      {
        result[field] = item->GetProperty("album_label");
        return true;
      }
      if (item->HasProperty("album_" + field + "_array"))
      {
        result[field] = item->GetProperty("album_" + field + "_array");
        return true;
      }
      if (item->HasProperty("album_" + field))
      {
        result[field] = item->GetProperty("album_" + field);
        return true;
      }
    }
    
    if (item->HasProperty("artist_" + field + "_array"))
    {
      result[field] = item->GetProperty("artist_" + field + "_array");
      return true;
    }
    if (item->HasProperty("artist_" + field))
    {
      result[field] = item->GetProperty("artist_" + field);
      return true;
    }

    if (field == "art")
    {
      if (thumbLoader != NULL && item->GetArt().size() <= 0 && !fetchedArt &&
        ((item->HasVideoInfoTag() && item->GetVideoInfoTag()->m_iDbId > -1) || (item->HasMusicInfoTag() && item->GetMusicInfoTag()->GetDatabaseId() > -1)))
      {
        thumbLoader->FillLibraryArt(*item);
        fetchedArt = true;
      }

      CGUIListItem::ArtMap artMap = item->GetArt();
      CVariant artObj(CVariant::VariantTypeObject);
      for (CGUIListItem::ArtMap::const_iterator artIt = artMap.begin(); artIt != artMap.end(); ++artIt)
      {
        if (!artIt->second.empty())
          artObj[artIt->first] = CTextureUtils::GetWrappedImageURL(artIt->second);
      }

      result["art"] = artObj;
      return true;
    }
    
    if (field == "thumbnail")
    {
      if (thumbLoader != NULL && !item->HasArt("thumb") && !fetchedArt &&
        ((item->HasVideoInfoTag() && item->GetVideoInfoTag()->m_iDbId > -1) || (item->HasMusicInfoTag() && item->GetMusicInfoTag()->GetDatabaseId() > -1)))
      {
        thumbLoader->FillLibraryArt(*item);
        fetchedArt = true;
      }
      else if (item->HasPictureInfoTag() && !item->HasArt("thumb"))
        item->SetArt("thumb", CTextureUtils::GetWrappedThumbURL(item->GetPath()));
      
      if (item->HasArt("thumb"))
        result["thumbnail"] = CTextureUtils::GetWrappedImageURL(item->GetArt("thumb"));
      else
        result["thumbnail"] = "";
      
      return true;
    }
    
    if (field == "fanart")
    {
      if (thumbLoader != NULL && !item->HasArt("fanart") && !fetchedArt &&
        ((item->HasVideoInfoTag() && item->GetVideoInfoTag()->m_iDbId > -1) || (item->HasMusicInfoTag() && item->GetMusicInfoTag()->GetDatabaseId() > -1)))
      {
        thumbLoader->FillLibraryArt(*item);
        fetchedArt = true;
      }
      
      if (item->HasArt("fanart"))
        result["fanart"] = CTextureUtils::GetWrappedImageURL(item->GetArt("fanart"));
      else
        result["fanart"] = "";
      
      return true;
    }
    
    if (item->HasVideoInfoTag() && item->GetVideoContentType() == VIDEODB_CONTENT_TVSHOWS)
    {
      if (item->GetVideoInfoTag()->m_iSeason < 0 && field == "season")
      {
        result[field] = (int)item->GetProperty("totalseasons").asInteger();
        return true;
      }
      if (field == "watchedepisodes")
      {
        result[field] = (int)item->GetProperty("watchedepisodes").asInteger();
        return true;
      }
    }
    
    if (field == "lastmodified" && item->m_dateTime.IsValid())
    {
      result[field] = item->m_dateTime.GetAsLocalizedDateTime();
      return true;
    }

    if (item->HasProperty(field))
    {
      result[field] = item->GetProperty(field);
      return true;
    }
  }

  return false;
}