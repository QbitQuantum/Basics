 /**
  * Helper function to create new item for Diagnosis table.
  * @return Created and initialized item with text
  */
 QTableWidgetItem* MuonSequentialFitDialog::createTableWidgetItem(const QString& text)
 {
   auto newItem = new QTableWidgetItem(text);
   newItem->setFlags(newItem->flags() ^ Qt::ItemIsEditable);
   return newItem;
 }