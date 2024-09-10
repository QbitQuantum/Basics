RSWappSearchFilesPage::RSWappSearchFilesPage(Wt::WContainerWidget *parent,RsFiles *mfiles)
	: WCompositeWidget(parent),mFiles(mfiles)
{
	setImplementation(_impl = new Wt::WContainerWidget()) ;

	//_treeView = new Wt::WTreeView(_impl);
	_tableView = new Wt::WTableView(_impl);

	Wt::WVBoxLayout *layout = new Wt::WVBoxLayout() ;
	_impl->setLayout(layout) ;


	search_box = new Wt::WLineEdit(_impl) ;
	search_box->setText("mp3") ;
	search_box->enterPressed().connect(this,&RSWappSearchFilesPage::searchClicked) ;

	//search_box->setHeight(50) ;

	localcb = new Wt::WCheckBox(Wt::WString("Search Local"),_impl) ;
	remotecb = new Wt::WCheckBox(Wt::WString("Search Remote"),_impl) ;
	distantcb = new Wt::WCheckBox(Wt::WString("Search Distant"),_impl) ;

	localcb->setChecked(false);
	remotecb->setChecked(true);
	distantcb->setChecked(true);

	Wt::WPushButton *btn = new Wt::WPushButton("Search!") ;
	btn->clicked().connect(this,&RSWappSearchFilesPage::searchClicked) ;

	Wt::WContainerWidget *hSearchBox = new Wt::WContainerWidget();
	Wt::WHBoxLayout *hSearchLayout = new Wt::WHBoxLayout ;
	hSearchBox->setLayout(hSearchLayout);

	hSearchLayout->addWidget(search_box) ;
	hSearchLayout->addWidget(localcb);
	hSearchLayout->addWidget(distantcb);
	hSearchLayout->addWidget(remotecb);
	hSearchLayout->addWidget(btn) ;

	layout->addWidget(hSearchBox) ;
	search_box->setWidth(1000);

	_tableView->setAlternatingRowColors(true);

	_tableView->setSelectionMode(Wt::ExtendedSelection);
	_tableView->setDragEnabled(true);


	_tableView->setColumnWidth(0, 250);
	_tableView->setColumnWidth(1, 150);
	_tableView->setColumnWidth(2, 250);
	_tableView->setColumnWidth(3, 150);
	_tableView->setColumnWidth(4, 150);
	_tableView->setColumnWidth(5, 100);

	_shared_files_model = new LocalSearchFilesModel(mfiles) ;

	_tableView->setModel(_shared_files_model) ;

	_tableView->doubleClicked().connect(this,&RSWappSearchFilesPage::tableClicked) ;
	layout->addWidget(_tableView,1) ;

	_tableView->setHeight(300) ;


	Wt::WPushButton *dlbtn = new Wt::WPushButton("Download selected") ;
	dlbtn->clicked().connect(this,&RSWappSearchFilesPage::searchClicked) ;
	layout->addWidget(dlbtn) ;

	_timer = new Wt::WTimer(this) ;
	_timer->setInterval(5000) ;
	_timer->timeout().connect(this,&RSWappSearchFilesPage::refresh) ;
	_timer->start() ;
}