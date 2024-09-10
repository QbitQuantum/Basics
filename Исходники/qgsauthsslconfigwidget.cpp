// private
QTreeWidgetItem* QgsAuthSslConfigWidget::addRootItem( const QString &label )
{
  QTreeWidgetItem *item = new QTreeWidgetItem(
    QStringList() << label,
    ( int )ConfigParent );
  setItemBold_( item );
  item->setTextAlignment( 0, Qt::AlignVCenter );
  item->setFlags( item->flags() & ~Qt::ItemIsSelectable );
  treeSslConfig->insertTopLevelItem( treeSslConfig->topLevelItemCount(), item );

  return item;
}