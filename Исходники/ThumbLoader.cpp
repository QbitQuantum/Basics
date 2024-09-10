CStdString CThumbLoader::GetCachedThumb(const CFileItem &item)
{
  CTextureDatabase db;
  if (db.Open())
    return db.GetTextureForPath(item.GetPath());
  return "";
}