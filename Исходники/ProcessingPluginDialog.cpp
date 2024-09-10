ProcessingPluginDialog::ProcessingPluginDialog(unsigned dataSourceInputCount, OscilloscopeWindow *parent) :
	QDialog(parent),
	channelChooserGroup(this)
{
	mainWindow = parent;
	inputCount = outputCount = 0;
	this->dataSourceInputCount = dataSourceInputCount;
	
	// layout
	QGridLayout *mainLayout = new QGridLayout;
	mainLayout->setColumnMinimumWidth(1, 5);
	
	// plugins list
	mainLayout->addWidget(new QLabel(tr("Available")), 0, 0);
	pluginsAvailableList = new QListWidget;
	for (size_t i = 0; i < parent->processingPluginsDescriptions.size(); i++)
	{
		pluginsAvailableList->addItem(parent->processingPluginsDescriptions[i]->name());
		pluginsAvailableList->item(i)->setToolTip(parent->processingPluginsDescriptions[i]->description());
	}
	QPushButton *addPlugin = new QPushButton(tr("&Use"));
	
	// active plugins
	mainLayout->addWidget(new QLabel(tr("Active")), 0, 2);
	pluginsActiveTable = new QTableWidget(0, 4);
	pluginsActiveTable->setSortingEnabled(false);
	pluginsActiveTable->setDragEnabled(false);
	pluginsActiveTable->setShowGrid(false);
	pluginsActiveTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
	pluginsActiveTable->setSelectionMode(QAbstractItemView::NoSelection);
	pluginsActiveTable->setContextMenuPolicy(Qt::CustomContextMenu);

	// max channel number
	extendedChannelChooser = new QSpinBox(this);
	extendedChannelChooser->setButtonSymbols(QAbstractSpinBox::PlusMinus);
	
	// ok / cancel buttons
	QPushButton *okButton = new QPushButton(tr("OK"));
	okButton->setDefault(true);
	QPushButton *cancelButton = new QPushButton(tr("Cancel"));
	
	// connections
	connect(pluginsAvailableList, SIGNAL(itemDoubleClicked(QListWidgetItem *)), SLOT(useSelectedPlugins(QListWidgetItem *)));
	connect(addPlugin, SIGNAL(clicked()), SLOT(useSelectedPlugins()));
	connect(okButton, SIGNAL(clicked()), SLOT(accept()));
	connect(cancelButton, SIGNAL(clicked()), SLOT(reject()));
	connect(pluginsActiveTable, SIGNAL(customContextMenuRequested(const QPoint &)), SLOT(pluginChannelEdit(const QPoint &)));
	connect(pluginsActiveTable, SIGNAL(itemClicked(QTableWidgetItem *)), SLOT(pluginEdit(QTableWidgetItem *)));
	connect(extendedChannelChooser, SIGNAL(valueChanged(int)), SLOT(recreateChannelMenu(int)));
	
	// layout
	QHBoxLayout *buttonLayout = new QHBoxLayout;
	buttonLayout->addStretch(1);
	buttonLayout->addWidget(okButton);
	buttonLayout->addWidget(cancelButton);

	QHBoxLayout *maxChannelLayout = new QHBoxLayout;
	maxChannelLayout->addWidget(new QLabel(tr("Number of extended channel")));
	maxChannelLayout->addWidget(extendedChannelChooser);
	
	mainLayout->addWidget(pluginsAvailableList, 1, 0);
	mainLayout->addWidget(addPlugin, 2, 0);
	mainLayout->setColumnStretch(0, 1);
	mainLayout->addWidget(pluginsActiveTable, 1, 2);
	mainLayout->addLayout(maxChannelLayout, 2, 2);
	mainLayout->setColumnStretch(2, 2);
	mainLayout->addLayout(buttonLayout, 3, 0, 1, -1);
	
	setLayout(mainLayout);
	
	setWindowTitle(tr("Plugins configuration"));
	
	recomputeUseChannelCount();

	recreateChannelMenu(extendedChannelChooser->minimum());
	toChangeItem = NULL;
}