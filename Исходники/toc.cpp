void TocDock::fillInfo()
{
    const QDomDocument *toc = document()->toc();
    if (toc) {
        fillToc(*toc, m_tree, 0);
    } else {
        QTreeWidgetItem *item = new QTreeWidgetItem();
        item->setText(0, tr("No TOC"));
        item->setFlags(item->flags() & ~Qt::ItemIsEnabled);
        m_tree->addTopLevelItem(item);
    }
}