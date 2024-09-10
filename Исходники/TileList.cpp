void TileList::addPiece(QPixmap pixmap, QPoint location, int type, QString text)
{
	QListWidgetItem *pieceItem = new QListWidgetItem(this,type);
    pieceItem->setIcon(QIcon(pixmap));
    pieceItem->setData(Qt::UserRole, QVariant(pixmap));
    pieceItem->setData(Qt::UserRole+1, location);
    pieceItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
	pieceItem->setText(text);
}