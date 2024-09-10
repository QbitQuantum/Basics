JSONRPC_STATUS CVideoLibrary::GetGenres(const CStdString &method, ITransportLayer *transport, IClient *client, const CVariant &parameterObject, CVariant &result)
{
  CStdString media = parameterObject["type"].asString();
  media = media.ToLower();
  int idContent = -1;

  CStdString strPath = "videodb://";
  /* select which video content to get genres from*/
  if (media.Equals("movie"))
  {
    idContent = VIDEODB_CONTENT_MOVIES;
    strPath += "1";
  }
  else if (media.Equals("tvshow"))
  {
    idContent = VIDEODB_CONTENT_TVSHOWS;
    strPath += "2";
  }
  else if (media.Equals("musicvideo"))
  {
    idContent = VIDEODB_CONTENT_MUSICVIDEOS;
    strPath += "3";
  }
  strPath += "/1/";
 
  CVideoDatabase videodatabase;
  if (!videodatabase.Open())
    return InternalError;

  CFileItemList items;
  if (videodatabase.GetGenresNav(strPath, items, idContent))
  {
    /* need to set strTitle in each item*/
    for (unsigned int i = 0; i < (unsigned int)items.Size(); i++)
      items[i]->GetVideoInfoTag()->m_strTitle = items[i]->GetLabel();
 
    HandleFileItemList("genreid", false, "genres", items, parameterObject, result);
  }

  videodatabase.Close();
  return OK;
}