void MusicFunctionTableWidget::addFunctionItems(int index, const QStringList &icon, const QStringList &path)
{
    m_listIndex = index;
    for(int i=0; i<rowCount(); ++i)
    {
        QTableWidgetItem *item = nullptr;
        setItem(i, 0, item = new QTableWidgetItem());

        item = new QTableWidgetItem(QIcon(icon[i]), QString());
        item->setTextAlignment(Qt::AlignCenter);
        setItem(i, 1, item);

        item = new QTableWidgetItem(path[i]);
        item->setTextColor(QColor(80, 80, 80));
        item->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        setItem(i, 2, item);
    }
}