void SettingsJavaPluginForm::loadInstalled()
{
	for (QMap<QString,QString>::iterator it = m_installedPlugins.begin(); it != m_installedPlugins.end(); it++)
	{
		QString name = it.key();
		name.remove(".jar");

		QTreeWidgetItem* i = new QTreeWidgetItem(treeInstalled, QStringList() << name << it.value());
		i->setFlags(i->flags() | Qt::ItemIsUserCheckable);
		i->setCheckState(0, Qt::Unchecked);
		treeInstalled->addTopLevelItem(i);
	}
}