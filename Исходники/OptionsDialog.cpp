QListWidgetItem* OptionsDialog::createItem(OptionsPage* page)
{
    QListWidgetItem* item = new QListWidgetItem(ui->listContent);
    item->setIcon(page->getIcon());
    item->setText(page->getTitle());
    item->setTextAlignment(Qt::AlignHCenter);
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    return item;
}