void CGUIWindowMusicBase::OnPrepareFileItems(CFileItemList &items)
{
  if (!items.GetPath().Equals("plugin://music/"))
    items.SetCachedMusicThumbs();
}