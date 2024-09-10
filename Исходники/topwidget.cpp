TopWidget::TopWidget(MainWindow * parent) : QWidget(parent)
{
	this->parent = parent;
	setMinimumWidth(300);
	setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);

	stopButton = new QToolButton();
	stopButton->setIcon(QIcon(DATAPATH "stop.png"));
	pauseButton = new QToolButton();
	pauseButton->setIcon(QIcon(DATAPATH "pause.png"));
	playButton = new QToolButton();
	playButton->setIcon(QIcon(DATAPATH "play.png"));
	prevButton = new QToolButton();
	prevButton->setIcon(QIcon(DATAPATH "prev.png"));
	nextButton = new QToolButton();
	nextButton->setIcon(QIcon(DATAPATH "next.png"));
	randomButton = new QToolButton();
	randomButton->setIcon(QIcon(DATAPATH "random.png"));
	libraryButton = new QToolButton();
	if(Settings::getLibraryFolded())
		libraryButton->setIcon(QIcon(DATAPATH "unfold.png"));
	else
		libraryButton->setIcon(QIcon(DATAPATH "fold.png"));

	trackBar = new Slider(parent);
	volumeBar = new Slider(parent);
	volumeBar->setMaximumWidth(70);
	volumeBar->setValue(100);
	volumeBar->style = 2;

	playModeBox = new QComboBox();
	playModeBox->setMaximumWidth(150);
	playModeBox->addItem("Normal");
	playModeBox->addItem("Loop All");
	playModeBox->addItem("Loop Track");
	playModeBox->addItem("Shuffle");

	grid = new QGridLayout();
	grid->addWidget(stopButton, 0, 0);
	grid->addWidget(pauseButton, 0, 1);
	grid->addWidget(playButton, 0, 2);
	grid->addWidget(prevButton, 0, 3);
	grid->addWidget(nextButton, 0, 4);
	grid->addWidget(randomButton, 0, 5);
	grid->addWidget(trackBar, 0, 6);
	grid->addWidget(playModeBox, 0, 7);
	grid->addWidget(volumeBar, 0, 8);
	grid->addWidget(libraryButton, 0, 9);
	grid->setContentsMargins(4, 4, 4, 4);

	connect(trackBar, SIGNAL(changed()), this, SLOT(onTrackBarChanged()));
	connect(volumeBar, SIGNAL(step()), this, SLOT(onVolumeBarChanged()));
	connect(pauseButton, SIGNAL(clicked()), this, SLOT(onPauseClick()));
	connect(playButton, SIGNAL(clicked()), this, SLOT(onPlayClick()));
	connect(stopButton, SIGNAL(clicked()), this, SLOT(onStopClick()));
	connect(prevButton, SIGNAL(clicked()), this, SLOT(onPrevClick()));
	connect(nextButton, SIGNAL(clicked()), this, SLOT(onNextClick()));
	connect(libraryButton, SIGNAL(clicked()), this, SLOT(onLibraryClick()));
	setLayout(grid);

	//Library View
	libraryWidget = new QWidget();
	libraryGrid = new QGridLayout();
	artistLabel = new QLabel("Artists: ");
	artistListWidget = new QListView();
	artistListWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	artistModel = new QStringListModel();
	albumLabel = new QLabel("Albums: ");
	albumListWidget = new QListView();
	albumListWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	albumModel = new QStringListModel();
	libraryGrid->addWidget(artistLabel, 1, 0);
	libraryGrid->addWidget(artistListWidget, 2, 0);
	libraryGrid->addWidget(albumLabel, 1, 1);
	libraryGrid->addWidget(albumListWidget, 2, 1);
	libraryGrid->setContentsMargins(0, 0, 0, 0);
	libraryWidget->setLayout(libraryGrid);
	if(Settings::getLibraryFolded())
		foldLibrary();
	else
		unfoldLibrary();

	artistList << "(Any)";
	mpdconfirm(mpd_search_db_tags(mpd, MPD_TAG_ARTIST));
	mpd_search_commit(mpd);
	mpd_pair * mp;
	while((mp = mpd_recv_pair_tag(mpd, MPD_TAG_ARTIST)) != NULL)
	{
		const QString artist = mp->value;
		if (artist != "")
			artistList << artist;
		mpd_return_pair(mpd, mp);
	}
	artistListWidget->setModel(artistModel);
	artistModel->setStringList(artistList);

	albumListWidget->setModel(albumModel);
	albumModel->setStringList(albumList);

	connect(artistListWidget->selectionModel(), SIGNAL(selectionChanged(QItemSelection, QItemSelection)), this, SLOT(onArtistSelectionChanged(QItemSelection)));
	connect(albumListWidget->selectionModel(), SIGNAL(selectionChanged(QItemSelection, QItemSelection)), this, SLOT(onAlbumSelectionChanged(QItemSelection)));

	artistListWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	albumListWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	selectedArtist = "(Any)";

}