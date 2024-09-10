/** Populates the module list with installed modules and orphaned indices */
void BtIndexPage::populateModuleList() {
	m_moduleList->clear();
		
	// populate installed modules
	m_modsWithIndices = new QTreeWidgetItem(m_moduleList);
	m_modsWithIndices->setText(0, tr("Works with indexes"));
	m_modsWithIndices->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsTristate);
	m_modsWithIndices->setExpanded(true);

	m_modsWithoutIndices = new QTreeWidgetItem(m_moduleList);
	m_modsWithoutIndices->setText(0, tr("Works without indexes"));
	m_modsWithoutIndices->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsTristate);
	m_modsWithoutIndices->setExpanded(true);



	QList<CSwordModuleInfo*>& modules = CPointers::backend()->moduleList();
	QList<CSwordModuleInfo*>::iterator end_it = modules.end();
	for (QList<CSwordModuleInfo*>::iterator it = modules.begin(); it != end_it; ++it) {
		QTreeWidgetItem* item = 0;
		
		if ((*it)->hasIndex()) {
			item = new QTreeWidgetItem(m_modsWithIndices);
			item->setText(0, (*it)->name());
			item->setText(1, QString("%1 ").arg((*it)->indexSize() / 1024) + tr("KiB"));
			item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
			item->setCheckState(0, Qt::Unchecked);
		}
		else {
			item = new QTreeWidgetItem(m_modsWithoutIndices);
			item->setText(0, (*it)->name());
			item->setText(1, QString("0 ") + tr("KiB"));
			item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
			item->setCheckState(0, Qt::Checked);
		}
	}
}