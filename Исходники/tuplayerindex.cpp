void TupLayerIndex::insertSoundLayer(int position, const QString &name)
{
    if (position >= 0 && position <= rowCount()) {
        QTableWidgetItem *newLayer = new QTableWidgetItem(name);
        newLayer->setTextAlignment(Qt::AlignCenter);

        newLayer->setBackgroundColor(palette().background().color());
        newLayer->setTextColor(palette().foreground().color());

        insertRow(position);
        setItem(position, 0, newLayer);
        fixSize();
    }
}