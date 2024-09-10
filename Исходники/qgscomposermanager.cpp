void QgsComposerManager::refreshComposers()
{
  QString selName = mComposerListWidget->currentItem() ? mComposerListWidget->currentItem()->text() : "";

  mItemComposerMap.clear();
  mComposerListWidget->clear();

  QSet<QgsComposer*> composers = QgisApp::instance()->printComposers();
  QSet<QgsComposer*>::const_iterator it = composers.constBegin();
  for ( ; it != composers.constEnd(); ++it )
  {
    QListWidgetItem* item = new QListWidgetItem(( *it )->title(), mComposerListWidget );
    item->setFlags( Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable );
    mItemComposerMap.insert( item, *it );
  }
  mComposerListWidget->sortItems();

  // Restore selection
  if ( !selName.isEmpty() )
  {
    QList<QListWidgetItem*> items = mComposerListWidget->findItems( selName, Qt::MatchExactly );
    if ( !items.isEmpty() )
    {
      mComposerListWidget->setCurrentItem( items.first() );
    }
  }
}