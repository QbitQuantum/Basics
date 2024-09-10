void PrintSelectPageWidget::setPages(int page)
{
    for (int i = 0; i < page; ++i) {
        QListWidgetItem *item = new QListWidgetItem(i18n("Page %1", (i + 1)), mListPage);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setCheckState(Qt::Unchecked);
        item->setData(PageIndex, i);
    }
}