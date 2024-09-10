void dspRunningAvailability::sHandleResort()
{
  for (int i = 0; i < list()->topLevelItemCount(); i++)
  {
    XTreeWidgetItem *item = list()->topLevelItem(i);
    if (item->data(list()->column("runningavail"), Qt::DisplayRole).toDouble() < 0)
      item->setTextColor(list()->column("runningavail"), namedColor("error"));
    else if (item->data(list()->column("runningavail"), Qt::DisplayRole).toDouble() < _reorderLevel->toDouble())
      item->setTextColor(list()->column("runningavail"), namedColor("warning"));
    else
      item->setTextColor(list()->column("runningavail"), namedColor(""));
  }
}