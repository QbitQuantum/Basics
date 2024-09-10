void OptionsTabPlugins::listPlugins()
{
	if ( !w )
		return;

	OptPluginsUI *d = (OptPluginsUI *)w;

	d->tw_Plugins->clear();

	PluginManager *pm=PluginManager::instance();

	QStringList plugins = pm->availablePlugins();
	plugins.sort();
	const QSize buttonSize = QSize(21,21);
	foreach ( const QString& plugin, plugins ){
		QIcon icon = pm->icon(plugin);
		bool enabled = pm->isEnabled(plugin);
		const QString path = pm->pathToPlugin(plugin);
		QString toolTip = tr("Plugin Path:\n%1").arg(path);
		Qt::CheckState state = enabled ? Qt::Checked : Qt::Unchecked;
		QTreeWidgetItem *item = new QTreeWidgetItem(d->tw_Plugins, QTreeWidgetItem::Type);
		item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
		item->setText(C_NAME, plugin);
		item->setText(C_VERSION, pm->version(plugin));
		item->setTextAlignment(C_VERSION, Qt::AlignHCenter);
		item->setToolTip(C_NAME, toolTip);
		item->setCheckState(C_NAME, state);
		if ( !enabled ) {
			icon = QIcon(icon.pixmap(icon.availableSizes().at(0), QIcon::Disabled));
		}
		item->setIcon(C_NAME,icon);
		QString shortName = PluginManager::instance()->shortName(plugin);

		QToolButton *aboutbutton = new QToolButton(d->tw_Plugins);
		aboutbutton->setIcon(QIcon(IconsetFactory::iconPixmap("psi/info")));
		aboutbutton->resize(buttonSize);
		aboutbutton->setObjectName("ab_" + shortName);
		aboutbutton->setToolTip(tr("Show information about plugin"));
		connect(aboutbutton, SIGNAL(clicked()), this, SLOT(showPluginInfo()));
		d->tw_Plugins->setItemWidget(item, C_ABOUT, aboutbutton);

		QToolButton *settsbutton = new QToolButton(d->tw_Plugins);
		settsbutton->setIcon(QIcon(IconsetFactory::iconPixmap("psi/options")));
		settsbutton->resize(buttonSize);
		settsbutton->setObjectName("sb_" + shortName);
		settsbutton->setToolTip(tr("Open plugin settings dialog"));
		connect(settsbutton, SIGNAL(clicked()), this, SLOT(settingsClicked()));
		settsbutton->setEnabled(enabled);
		d->tw_Plugins->setItemWidget(item, C_SETTS, settsbutton);
	}