KSlovar::KSlovar()
  : KMainWindow( 0, "KSlovar" ), m_dictionarydlg(0), m_recievedPackages(0)
{
  KSlovar::m_instance=this;
  m_configDialog=new KSConfigDialog(this, "settings", Configuration::self());

  new KStatusBar(this);
  statusBar()->insertItem(i18n("Ready."), 0);

  if(!QFile::exists(locateLocal("config", "kslovarrc", false)))
  {
    slotFirstRunWizard();
  }
  else
  {
    if(Configuration::autoUpdateLanguage())
    {
      slotDownloadLanguage();
    }
    else
    {
      loadLanguages();
    }
  }

  m_welcomeMessage=i18n("<h1>Welcome to KSlovar</h1> <p>This is an editor and viewer that is capable of creating, editing and showing diferent kinds of dictionaries.</p><p>If you encounter any bugs, please send a bug report to [email protected].</p>");


  registerButtons();
  addMenu();
  addToolbar();

  QHBox * horiz = new QHBox(this);

  m_split = new QSplitter(horiz);

  QVBox * vert = new QVBox(m_split);
  vert->setMaximumWidth(200);
  vert->setMinimumWidth(200);

  m_search = new KSSearchLine(vert);
  m_list = new KSListView( vert );
  m_list->addColumn("name");
  m_list->setColumnWidth(0, 193);
  m_list->setFullWidth(true);
  m_search->setList(m_list);

  KSData::instance()->setMainList(m_list);

  m_browser=new KHTMLPart(m_split);
  m_browser->setEncoding("utf-8", true);
  m_browser->view()->viewport()->installEventFilter(this); //For searching with middle click
  slotClose();

  connect( m_browser->browserExtension(), SIGNAL( openURLRequest( const KURL &, const KParts::URLArgs & ) ), this, SLOT( slotShowBrowser(const KURL &, const KParts::URLArgs &) ) );
  connect(m_list, SIGNAL( selectionChanged(QListViewItem *)), this, SLOT( slotShowList(QListViewItem *) ) );
  connect(m_list, SIGNAL(doubleClicked( QListViewItem *)), this, SLOT(slotEditPhrase()));
  connect(kapp, SIGNAL(shutDown()), this, SLOT(slotClose()));
  connect(m_list, SIGNAL(contextMenu(KListView*, QListViewItem*, const QPoint&)), this, SLOT(showPopup( KListView*, QListViewItem*, const QPoint& )));
  connect(m_list, SIGNAL(recievedPackage(bool, bool)), this, SLOT(slotCountPackages(bool, bool)));

  setCentralWidget(horiz);
}