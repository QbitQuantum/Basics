void CMyAppsSource::BindItems(CFileItemList& items)
{
  // Perform post processing here
  CBrowseWindowPropertyValueFilter* filter = NULL;

  if (m_mapFilters.find("apptype") != m_mapFilters.end())
  {
    CStdString filtername = m_mapFilters["apptype"];

    if (filtername != "")
    {

      if (filtername == "video")
      {
        filter = new CBrowseWindowPropertyValueFilter(FILTER_APPS_VIDEO_ID, FILTER_APPS_VIDEO_NAME, "app-media", "video");
      }
      else if (filtername == "music")
      {
        filter = new CBrowseWindowPropertyValueFilter(FILTER_APPS_MUSIC_ID, FILTER_APPS_MUSIC_NAME, "app-media", "music");
      }
      else if (filtername == "pictures")
      {
        filter = new CBrowseWindowPropertyValueFilter(FILTER_APPS_PICTURES_ID, FILTER_APPS_PICTURES_NAME, "app-media", "pictures");
      }

      if (filter != NULL)
      {
        int i = 0;

        while (i < items.Size())
        {
          if (filter->Apply(&*items[i]) != true)
          {//need to remove this item
            items.Remove(i);
          }
          else
          {
            i++;
          }
        }

        delete filter;
      }
    }
  }

  CBrowseWindowSource::BindItems(items);
}