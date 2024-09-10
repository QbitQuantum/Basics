void CDlgBulkRegister::AddItem( const QString &strText, int nRow, int nCol, QTableWidget* pTable )
{
    QTableWidgetItem* pItem = new QTableWidgetItem( strText );
    pItem->setFlags( Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable );
    pTable->setItem( nRow, nCol, pItem );
}