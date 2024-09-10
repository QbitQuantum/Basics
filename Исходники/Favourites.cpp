bool CFavourites::AddOrRemove(CFileItem *item, int contextWindow)
{
  if (!item) return false;

  // load our list
  CFileItemList items;
  Load(items);

  CStdString executePath(GetExecutePath(item, contextWindow));

  CFileItemPtr match = items.Get(executePath);
  if (match)
  { // remove the item
    items.Remove(match.get());
  }
  else
  { // create our new favourite item
    CFileItemPtr favourite(new CFileItem(item->GetLabel()));
    if (item->GetLabel().IsEmpty())
      favourite->SetLabel(CUtil::GetTitleFromPath(item->m_strPath, item->m_bIsFolder));
    favourite->SetThumbnailImage(item->GetThumbnailImage());
    favourite->m_strPath = executePath;
    items.Add(favourite);
  }

  // and save our list again
  return Save(items);
}