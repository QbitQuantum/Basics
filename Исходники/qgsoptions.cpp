void QgsOptions::on_mAddUrlPushButton_clicked()
{
  QListWidgetItem* newItem = new QListWidgetItem( mExcludeUrlListWidget );
  newItem->setText( "URL" );
  newItem->setFlags( Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable );
  mExcludeUrlListWidget->addItem( newItem );
  mExcludeUrlListWidget->setCurrentItem( newItem );
}