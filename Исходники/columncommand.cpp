void InsertEmptyColumnsUndo::redo() const {
  TApp *app    = TApp::instance();
  TXsheet *xsh = app->getCurrentXsheet()->getXsheet();

  // If this is the very first column, add one now since there is always
  // 1 visible on the screen but its not actually there yet.
  if (!xsh->getColumnCount()) xsh->insertColumn(0);

  std::vector<std::pair<int, int>>::const_reverse_iterator bt,
      bEnd = m_columnBlocks.rend();
  for (bt = m_columnBlocks.rbegin(); bt != bEnd; ++bt)
    for (int n = 0; n != bt->second; ++n) xsh->insertColumn(bt->first);

  app->getCurrentScene()->setDirtyFlag(true);
  app->getCurrentXsheet()->notifyXsheetChanged();
  app->getCurrentObject()->notifyObjectIdSwitched();
}