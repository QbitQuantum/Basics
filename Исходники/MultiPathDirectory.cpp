void CMultiPathDirectory::MergeItems(CFileItemList &items)
{
  CLog::Log(LOGDEBUG, "CMultiPathDirectory::MergeItems, items = %i", (int)items.Size());
  unsigned int time = CTimeUtils::GetTimeMS();
  if (items.Size() == 0)
    return;
  // sort items by label
  // folders are before files in this sort method
  items.Sort(SORT_METHOD_LABEL, SORT_ORDER_ASC);
  int i = 0;

  // if first item in the sorted list is a file, just abort
  if (!items.Get(i)->m_bIsFolder)
    return;

  while (i + 1 < items.Size())
  {
    // there are no more folders left, so exit the loop
    CFileItemPtr pItem1 = items.Get(i);
    if (!pItem1->m_bIsFolder)
      break;

    vector<int> stack;
    stack.push_back(i);
    CLog::Log(LOGDEBUG,"Testing path: [%03i] %s", i, pItem1->m_strPath.c_str());

    int j = i + 1;
    do
    {
      CFileItemPtr pItem2 = items.Get(j);
      if (!pItem2->GetLabel().Equals(pItem1->GetLabel()))
        break;

      // ignore any filefolders which may coincidently have
      // the same label as a true folder
      if (!pItem2->IsFileFolder())
      {
        stack.push_back(j);
        CLog::Log(LOGDEBUG,"  Adding path: [%03i] %s", j, pItem2->m_strPath.c_str());
      }
      j++;
    }
    while (j < items.Size());

    // do we have anything to combine?
    if (stack.size() > 1)
    {
      // we have a multipath so remove the items and add the new item
      CStdString newPath = ConstructMultiPath(items, stack);
      for (unsigned int k = stack.size() - 1; k > 0; --k)
        items.Remove(stack[k]);
      pItem1->m_strPath = newPath;
      CLog::Log(LOGDEBUG,"  New path: %s", pItem1->m_strPath.c_str());
    }

    i++;
  }

  CLog::Log(LOGDEBUG,
            "CMultiPathDirectory::MergeItems, items = %i,  took %d ms",
            items.Size(), CTimeUtils::GetTimeMS() - time);
}