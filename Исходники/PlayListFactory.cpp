bool CPlayListFactory::IsPlaylist(const CFileItem& item)
{
  CStdString strMimeType = item.GetMimeType();
  strMimeType.ToLower();

/* These are abit uncertain 
  if(strMimeType == "video/x-ms-asf"
  || strMimeType == "video/x-ms-asx"
  || strMimeType == "video/x-ms-wmv"
  || strMimeType == "video/x-ms-wma"
  || strMimeType == "video/x-ms-wfs"
  || strMimeType == "video/x-ms-wvx"
  || strMimeType == "video/x-ms-wax"
  || strMimeType == "video/x-ms-asf")
    return true;
*/

  // online m3u8 files are hls:// -- do not treat as playlist
  if (item.IsInternetStream() && item.IsType(".m3u8"))
    return false;

  if(strMimeType == "audio/x-pn-realaudio"
  || strMimeType == "playlist"
  || strMimeType == "audio/x-mpegurl")
    return true;

  return IsPlaylist(item.GetPath());
}