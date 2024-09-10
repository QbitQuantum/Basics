void MusicSongsListWidget::updateSongsFileName(const MusicSongs &songs)
{
    int count = rowCount();
    setRowCount(songs.count());    //reset row count
    for(int i=count; i<songs.count(); i++)
    {
        QTableWidgetItem *item = new QTableWidgetItem;
        setItem(i, 0, item);
        //To get the song name
                          item = new QTableWidgetItem;
        item->setText(QFontMetrics(font()).elidedText(songs[i].getMusicName(), Qt::ElideRight, 242));
        item->setTextColor(QColor(50, 50, 50));
        item->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        setItem(i, 1, item);
        //add a delete icon
                          item = new QTableWidgetItem(songs[i].getMusicTime());
        item->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        setItem(i, 2, item);
    }
}