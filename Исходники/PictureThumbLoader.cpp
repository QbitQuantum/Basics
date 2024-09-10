void CPictureThumbLoader::ProcessFoldersAndArchives(CFileItem *pItem)
{
  if (pItem->HasThumbnail())
    return;

  CTextureDatabase db;
  db.Open();
  if (pItem->IsCBR() || pItem->IsCBZ())
  {
    CStdString strTBN(URIUtils::ReplaceExtension(pItem->GetPath(),".tbn"));
    if (CFile::Exists(strTBN))
    {
      db.SetTextureForPath(pItem->GetPath(), "thumb", strTBN);
      CTextureCache::Get().BackgroundCacheImage(strTBN);
      pItem->SetThumbnailImage(strTBN);
      return;
    }
  }
  if ((pItem->m_bIsFolder || pItem->IsCBR() || pItem->IsCBZ()) && !pItem->m_bIsShareOrDrive && !pItem->IsParentFolder())
  {
    // first check for a folder.jpg
    CStdString thumb = "folder.jpg";
    CStdString strPath = pItem->GetPath();
    if (pItem->IsCBR())
    {
      URIUtils::CreateArchivePath(strPath,"rar",pItem->GetPath(),"");
      thumb = "cover.jpg";
    }
    if (pItem->IsCBZ())
    {
      URIUtils::CreateArchivePath(strPath,"zip",pItem->GetPath(),"");
      thumb = "cover.jpg";
    }
    if (pItem->IsMultiPath())
      strPath = CMultiPathDirectory::GetFirstPath(pItem->GetPath());
    thumb = URIUtils::AddFileToFolder(strPath, thumb);
    if (CFile::Exists(thumb))
    {
      db.SetTextureForPath(pItem->GetPath(), "thumb", thumb);
      CTextureCache::Get().BackgroundCacheImage(thumb);
      pItem->SetThumbnailImage(thumb);
      return;
    }
    if (!pItem->IsPlugin())
    {
      // we load the directory, grab 4 random thumb files (if available) and then generate
      // the thumb.

      CFileItemList items;

      CDirectory::GetDirectory(strPath, items, g_settings.m_pictureExtensions, DIR_FLAG_NO_FILE_DIRS);
      
      // create the folder thumb by choosing 4 random thumbs within the folder and putting
      // them into one thumb.
      // count the number of images
      for (int i=0; i < items.Size();)
      {
        if (!items[i]->IsPicture() || items[i]->IsZIP() || items[i]->IsRAR() || items[i]->IsPlayList())
        {
          items.Remove(i);
        }
        else
          i++;
      }

      if (items.IsEmpty())
      {
        if (pItem->IsCBZ() || pItem->IsCBR())
        {
          CDirectory::GetDirectory(strPath, items, g_settings.m_pictureExtensions, DIR_FLAG_NO_FILE_DIRS);
          for (int i=0;i<items.Size();++i)
          {
            CFileItemPtr item = items[i];
            if (item->m_bIsFolder)
            {
              ProcessFoldersAndArchives(item.get());
              pItem->SetThumbnailImage(items[i]->GetThumbnailImage());
              pItem->SetIconImage(items[i]->GetIconImage());
              return;
            }
          }
        }
        return; // no images in this folder
      }

      // randomize them
      items.Randomize();

      if (items.Size() < 4 || pItem->IsCBR() || pItem->IsCBZ())
      { // less than 4 items, so just grab the first thumb
        items.Sort(SORT_METHOD_LABEL, SORT_ORDER_ASC);
        CStdString thumb = CTextureCache::GetWrappedThumbURL(items[0]->GetPath());
        db.SetTextureForPath(pItem->GetPath(), "thumb", thumb);
        CTextureCache::Get().BackgroundCacheImage(thumb);
        pItem->SetThumbnailImage(thumb);
      }
      else
      {
        // ok, now we've got the files to get the thumbs from, lets create it...
        // we basically load the 4 images and combine them
        vector<string> files;
        for (int thumb = 0; thumb < 4; thumb++)
          files.push_back(items[thumb]->GetPath());
        CStdString thumb = CTextureCache::GetWrappedImageURL(pItem->GetPath(), "picturefolder");
        CStdString relativeCacheFile = CTextureCache::GetCacheFile(thumb) + ".png";
        if (CPicture::CreateTiledThumb(files, CTextureCache::GetCachedPath(relativeCacheFile)))
        {
          CTextureDetails details;
          details.file = relativeCacheFile;
          details.width = g_advancedSettings.m_thumbSize;
          details.height = g_advancedSettings.m_thumbSize;
          CTextureCache::Get().AddCachedTexture(thumb, details);
          db.SetTextureForPath(pItem->GetPath(), "thumb", thumb);
          pItem->SetThumbnailImage(CTextureCache::GetCachedPath(relativeCacheFile));
        }
      }
    }
    // refill in the icon to get it to update
    pItem->FillInDefaultIcon();
  }
}