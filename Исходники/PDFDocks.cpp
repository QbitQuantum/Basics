void PDFOutlineDock::fillInfo()
{
	tree->clear();
	const QDomDocument *toc = document->popplerDoc()->toc();
	if (toc) {
		fillToc(*toc, tree, 0);
		connect(tree, SIGNAL(itemSelectionChanged()), this, SLOT(followTocSelection()));
		delete toc;
	} else {
		QTreeWidgetItem *item = new QTreeWidgetItem();
		item->setText(0, tr("No TOC"));
		item->setFlags(item->flags() & ~Qt::ItemIsEnabled);
		tree->addTopLevelItem(item);
	}
}