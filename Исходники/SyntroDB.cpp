void SyntroDB::initDisplayStats()
{
	QTableWidgetItem *item;
	QHBoxLayout *layout;
	QWidget *widget;

	int cellHeight = fontMetrics().lineSpacing() + CELL_HEIGHT_PAD;
	
	m_rxStreamTable = new QTableWidget(this);

	m_rxStreamTable->setColumnCount(SYNTRODB_COL_COUNT);
	m_rxStreamTable->setColumnWidth(SYNTRODB_COL_CONFIG, 80);
	m_rxStreamTable->setColumnWidth(SYNTRODB_COL_INUSE, 60);
	m_rxStreamTable->setColumnWidth(SYNTRODB_COL_STREAM, 140);
	m_rxStreamTable->setColumnWidth(SYNTRODB_COL_TOTALRECS, 80);
	m_rxStreamTable->setColumnWidth(SYNTRODB_COL_TOTALBYTES, 100);
	m_rxStreamTable->setColumnWidth(SYNTRODB_COL_FILERECS, 80);
	m_rxStreamTable->setColumnWidth(SYNTRODB_COL_FILEBYTES, 100);
	m_rxStreamTable->setColumnWidth(SYNTRODB_COL_FILE, 400);

	m_rxStreamTable->verticalHeader()->setDefaultSectionSize(cellHeight);

    m_rxStreamTable->setHorizontalHeaderLabels(QStringList() << tr("") << tr("In use") << tr("Stream") 
			<< tr("Total Recs") << tr("Total Bytes") 
			<< tr("File Recs") << tr("File Bytes") << tr("Current file path"));

    m_rxStreamTable->setSelectionMode(QAbstractItemView::NoSelection);
 
	for (int row = 0; row < SYNTRODB_MAX_STREAMS; row++) {
		m_rxStreamTable->insertRow(row);
		m_rxStreamTable->setRowHeight(row, cellHeight);
		m_rxStreamTable->setContentsMargins(5, 5, 5, 5);

		StoreButton *button = new StoreButton("Configure", this, row);
		m_rxStreamTable->setCellWidget(row, SYNTRODB_COL_CONFIG, button);
		connect(button, SIGNAL(buttonClicked(int)), this, SLOT(buttonClicked(int)));

		m_useBox[row] = new StoreCheckBox(m_rxStreamTable, row);

		// center the checkbox in cell
		widget = new QWidget;
		layout = new QHBoxLayout;
		layout->setSpacing(0);
		layout->setContentsMargins(0, 0, 0, 0);
		layout->addWidget(m_useBox[row]);
		layout->setAlignment(Qt::AlignCenter);
		widget->setLayout(layout);
		m_rxStreamTable->setCellWidget(row, SYNTRODB_COL_INUSE, widget);

		connect(m_useBox[row], SIGNAL(boxClicked(bool, int)), this, SLOT(boxClicked(bool, int)));
		
		for (int col = 2; col < SYNTRODB_COL_COUNT; col++) {
			item = new QTableWidgetItem();
			item->setTextAlignment(Qt::AlignLeft | Qt::AlignBottom);
			item->setFlags(Qt::ItemIsEnabled);
			item->setText("");
			m_rxStreamTable->setItem(row, col, item);
		}
	}
	setCentralWidget(m_rxStreamTable);
}