void MusicVideoTableWidget::creatSearchedItems(const QString &songname,
                                               const QString &artistname,
                                               const QString &time)
{
    int count;
    setRowCount(count = m_downLoadManager->getSongIdIndex());
    QHeaderView *headerview = horizontalHeader();

    QTableWidgetItem *item = new QTableWidgetItem;
    item->setData(MUSIC_CHECK_ROLE, false);
    setItem(count - 1, 0, item);

                      item = new QTableWidgetItem;
    item->setText(QFontMetrics(font()).elidedText(songname, Qt::ElideRight,
                                                  headerview->sectionSize(1) - 5));
    item->setTextColor(QColor(50, 50, 50));
    item->setTextAlignment(Qt::AlignCenter);
    item->setToolTip(songname);
    setItem(count - 1, 1, item);

                      item = new QTableWidgetItem;
    item->setText(QFontMetrics(font()).elidedText(artistname, Qt::ElideRight,
                                                  headerview->sectionSize(2) - 5));
    item->setTextColor(QColor(50, 50, 50));
    item->setTextAlignment(Qt::AlignCenter);
    item->setToolTip(artistname);
    setItem(count - 1, 2, item);

                      item = new QTableWidgetItem;
    item->setIcon(QIcon(randToGetStrength()));
    setItem(count - 1, 3, item);

                      item = new QTableWidgetItem(time);
    item->setTextColor(QColor(50, 50, 50));
    item->setTextAlignment(Qt::AlignCenter);
    setItem(count - 1, 4, item);

                      item = new QTableWidgetItem;
    item->setIcon(QIcon(QString::fromUtf8(":/share/showMV")));
    setItem(count - 1, 5, item);

                      item = new QTableWidgetItem;
    item->setIcon(QIcon(QString::fromUtf8(":/share/autionplay")));
    setItem(count - 1, 6, item);

                      item = new QTableWidgetItem;
    item->setIcon(QIcon(QString::fromUtf8(":/share/musicdownload")));
    setItem(count - 1, 7, item);
}