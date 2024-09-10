TorrentDetails::TorrentDetails(QWidget* me, TorrentDownload* obj)
	: m_download(obj), m_bFilled(false)
{
	connect(obj, SIGNAL(destroyed(QObject*)), this, SLOT(deleteLater()));
	setupUi(me);
	TorrentDownload::m_worker->setDetailsObject(this);
	
	m_pPiecesModel = new TorrentPiecesModel(treePieces, obj);
	treePieces->setModel(m_pPiecesModel);
	treePieces->setItemDelegate(new BlockDelegate(treePieces));
	
	m_pPeersModel = new TorrentPeersModel(treePeers, obj);
	treePeers->setModel(m_pPeersModel);
	
	m_pFilesModel = new TorrentFilesModel(treeFiles, obj);
	treeFiles->setModel(m_pFilesModel);
	treeFiles->setItemDelegate(new TorrentProgressDelegate(treeFiles));
	
	QHeaderView* hdr = treePeers->header();
	hdr->resizeSection(1, 110);
	hdr->resizeSection(3, 50);
	hdr->resizeSection(4, 70);
	
	for(int i=5;i<9;i++)
		hdr->resizeSection(i, 70);
	
	hdr->resizeSection(9, 300);
	
	hdr = treeFiles->header();
	hdr->resizeSection(0, 500);
	
	QAction* act;
	QMenu* submenu;
	
	m_pMenuFiles = new QMenu(me);
	submenu = new QMenu(tr("Priority"), m_pMenuFiles);
	
	act = submenu->addAction( tr("Do not download") );
	connect(act, SIGNAL(triggered()), this, SLOT(setPriority0()));
	act = submenu->addAction( tr("Normal") );
	connect(act, SIGNAL(triggered()), this, SLOT(setPriority1()));
	act = submenu->addAction( tr("Increased") );
	connect(act, SIGNAL(triggered()), this, SLOT(setPriority4()));
	act = submenu->addAction( tr("Maximum") );
	connect(act, SIGNAL(triggered()), this, SLOT(setPriority7()));
	
	m_pMenuFiles->addAction(actionOpenFile);
	m_pMenuFiles->addMenu(submenu);
	
	connect(treeFiles, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(fileContext(const QPoint&)));
	connect(treeFiles, SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(openFile()));
	
	m_pMenuPeers = new QMenu(me);
	act = m_pMenuPeers->addAction( tr("Ban") );
	act = m_pMenuPeers->addAction( tr("Information") );
	connect(act, SIGNAL(triggered()), this, SLOT(peerInfo()));
	
	connect(treePeers, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(peerContext(const QPoint&)));
	connect(actionOpenFile, SIGNAL(triggered()), this, SLOT(openFile()));
	
	refresh();
}