void CLocalFilesSource::BindItems(CFileItemList& items)
{
  // Perform post processing here
  // Need to default video content to help with the UPnP case where we don't really know the content type
  bool bDefaultVideo = false;

  if( items.m_strPath.Equals("boxeedb://unresolvedVideoFiles") )
    bDefaultVideo = true;

  for (int i = 0 ; i < items.Size() ; i++)
  {
    CFileItemPtr pItem = items[i];

    if (pItem->IsVideo() || bDefaultVideo)
    {
      pItem->SetProperty("IsVideo", true);
    }
    else if (pItem->IsAudio())
    {
      pItem->SetProperty("IsMusic", true);
    }
    else if (pItem->IsPicture())
    {
      pItem->SetProperty("IsPhotos", true);
    }
    else if (!pItem->m_bIsFolder)
    {
      items.Remove(i);
      i--;
    }
  }

  CBrowseWindowSource::BindItems(items);
}