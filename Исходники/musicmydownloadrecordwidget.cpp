void MusicMyDownloadRecordWidget::createItem(int index, const QString &name,
                                             const QString &size, qint64 time)
{
    QTableWidgetItem *item = new QTableWidgetItem;
    setItem(index, 0, item);

                      item = new QTableWidgetItem(QFontMetrics(font()).elidedText(name,
                                                                                  Qt::ElideRight, 170));
    item->setTextColor(QColor(50,50,50));
    item->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    item->setToolTip( name );
    setItem(index, 1, item);

                      item = new QTableWidgetItem;
    item->setData(Qt::DisplayRole, 100);
    setItem(index, 2, item);

                      item = new QTableWidgetItem( size );
    item->setTextAlignment(Qt::AlignCenter);
    item->setData(Qt::UserRole + 1, time);
    setItem(index, 3, item);
}