void BaseTreeView::restoreLayout(KConfig *config, const QString &group)
{
  KListView::restoreLayout(config, group);
  KConfigGroupSaver saver(config, group);
  setShowToolTips( config->readBoolEntry("ShowToolTips", true) );

  if (! m_saveOpenFolder || ! qConfig.saveTrees)
    return;

  BaseTreeBranch *btb;
  KFileTreeBranchIterator it( branches() );
  int maxBranch = config->readNumEntry("NumOpenFolderList", 0);
  for (int i = 1; i <= maxBranch; ++i)
  {
    QStringList folderList = QuantaCommon::readPathListEntry(config, "OpenFolderList" + QString::number(i));
    if (folderList.count() > 1) {
      KURL rootURL = (*folderList.begin());
      folderList.remove(folderList.begin());  // remove the root URL
      KFileTreeBranchIterator it( branches() );
      for ( ; it.current(); ++it)
      {
        if ((*it)->rootUrl() == rootURL) {
          btb = dynamic_cast<BaseTreeBranch *>( (*it) );
          if (btb) {
            btb->folderToOpen = folderList;
            btb->reopenFolder();
            break;
          }
        }
      }
    }
  }
}