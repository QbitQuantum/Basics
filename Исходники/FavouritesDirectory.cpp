bool CFavouritesDirectory::AddOrRemove(CFileItem *item, int contextWindow)
{
  if (!item) return false;

  // load our list
  CFileItemList items;
  Load(items);

  std::string executePath(GetExecutePath(*item, contextWindow));

  CFileItemPtr match = items.Get(executePath);
  if (match)
  { // remove the item
    items.Remove(match.get());
  }
  else
  { // create our new favourite item
    CFileItemPtr favourite(new CFileItem(item->GetLabel()));
    if (item->GetLabel().empty())
      favourite->SetLabel(CUtil::GetTitleFromPath(item->GetPath(), item->m_bIsFolder));
    favourite->SetArt("thumb", item->GetArt("thumb"));
    favourite->SetPath(executePath);
    items.Add(favourite);
  }

  // and save our list again
  return Save(items);
}