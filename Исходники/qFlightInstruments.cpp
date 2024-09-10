void QKeyValueListView::listUpdate_slot(void)
{
    int                 i, n;
    ListMap::iterator   it;

    QColor              clCL1, clCL2;
    QColor              clB1, clB2;

    int                 fontSize = 8;
    int                 rowHeight = 20;

    clCL1 = QColor(0x00, 0x00, 0xFF);
    clCL2 = QColor(0x00, 0x00, 0x00);
    clB1  = QColor(0xFF, 0xFF, 0xFF);
    clB2  = QColor(0xE0, 0xE0, 0xE0);

    m_mutex->lock();

    n = m_data.size();
    setRowCount(n);
    setColumnCount(2);

    for(i=0, it=m_data.begin(); it!=m_data.end(); i++, it++) {
        // set name cell
        if( this->item(i, 0) != NULL ) {
            this->item(i, 0)->setText(it.key());
        } else {
            QTableWidgetItem* item = new QTableWidgetItem();
            item->setText(it.key());

            item->setTextColor(clCL1);
            if( i % 2 == 0 ) item->setBackgroundColor(clB1);
            else             item->setBackgroundColor(clB2);

            item->setFont(QFont("", fontSize));

            this->setItem(i, 0, item);
        }

        // set value cell
        if( this->item(i, 1) != NULL ) {
            this->item(i, 1)->setText(it.value());
        } else {
            QTableWidgetItem* item = new QTableWidgetItem();
            item->setText(it.value());

            item->setTextColor(clCL2);
            if( i % 2 == 0 ) item->setBackgroundColor(clB1);
            else             item->setBackgroundColor(clB2);

            item->setFont(QFont("", fontSize));

            this->setItem(i, 1, item);
        }

        setRowHeight(i, rowHeight);
    }

    m_mutex->unlock();
}