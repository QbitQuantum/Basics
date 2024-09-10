//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
jdlvFrame::jdlvFrame (const char *fileToLoad) : nextWorld(NULL),
  isChanged(false),
    eM(elModeView), genNo(0), curColor(0), speed(3), timerID(0)
{
  QFont fixedFont(jdlvFONTFACENAME, jdlvFONTSIZE);
        fixedFont.setStyleHint(QFont::TypeWriter);
  primeWorld = new_elMundoA();
  vista = new elVista (this, primeWorld); setCentralWidget(vista);
  vista->setMinimumSize(720, 480);
  //- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  QToolBar *bottom = new permanentToolBar("ctrl", this);
  bottom->setFloatable(false);
  bottom->setMovable  (false);
  bottom->setIconSize(QSize(28,25));
  showTimeCB = new QAction(QIcon(":/time.png"), QString("time"), this);
  showInfoPB = new QAction(QIcon(":/info.png"), QString("info"), this);
  connect(showTimeCB, SIGNAL(triggered(bool)), this, SLOT(ToggleTime(bool)));
  connect(showInfoPB, SIGNAL(triggered()),     this, SLOT(ShowInfo()));
  bottom->addAction(showTimeCB);
  bottom->addAction(showInfoPB);         showInfoPB->setEnabled(false); //+
  bottom->addWidget(new QLabel(" "));
  //- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  QActionGroup *modeGroup = new QActionGroup(this);
  modeEdit = new QAction(QIcon(":/pen-in-box.png"),QString("Edit (X)"),  this);
  modeView = new QAction(QIcon(":/eye-half.png"),  QString("View (Z)"),  this);
  setColor = new QAction(QIcon(":/empty1.png"),    QString("color"),     this);
  connect(modeView, SIGNAL(triggered()), this, SLOT(SetModeView()));
  connect(modeEdit, SIGNAL(triggered()), this, SLOT(SetModeEdit()));
  connect(setColor, SIGNAL(triggered()), this, SLOT(PopupColorMenu()));
  showTimeCB->setCheckable(true);
  modeEdit  ->setCheckable(true); modeEdit->setShortcut(QKeySequence("X"));
  modeView  ->setCheckable(true); modeView->setShortcut(QKeySequence("Z"));
  modeView  ->setChecked  (true);
  modeGroup->addAction(modeView); bottom->addAction(modeView);
  modeGroup->addAction(modeEdit); bottom->addAction(modeEdit);
                                  bottom->addAction(setColor);
  //- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  QMenu *file_menu = menuBar()->addMenu("File");
  openFile =  new QAction(QIcon(":/book.png"), QString("Open.."), this);
  reLoad = new QAction(QIcon(":/reload1.png"), QString("reload"), this);
  connect(openFile, SIGNAL(triggered()), this, SLOT(OpenFile()));
  connect(reLoad,   SIGNAL(triggered()), this, SLOT(DoReload()));
  file_menu->addAction(openFile);
  file_menu->addAction(reLoad);        reLoad->setEnabled(false);
  //- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  QMenu *edit_menu = menuBar()->addMenu("Edit");
  deleteSelected = new QAction(QString("delete"), this);
  deleteSelected->setShortcut(QKeySequence("Del"));
  cropSelected   = new QAction(QString("crop"), this);
  pasteClipboard =
            new QAction(QIcon(":/win-paste.png"),   QString("paste"),    this);
  copyCLR = new QAction(QIcon(":/export-blue.png"), QString("copy"),     this);
  copyBnW = new QAction(QIcon(":/export-mono.png"), QString("copy b/w"), this);
  newWin = new QAction(QIcon(":/windows1.png"),   QString("new window"), this);
  bottom->addAction(pasteClipboard);     pasteClipboard->setEnabled(false); //+
  bottom->addAction(copyCLR); copyCLR->setShortcut(QKeySequence("Ctrl+C"));
  bottom->addAction(copyBnW);
  bottom->addAction(newWin);       newWin->setEnabled(false); //+
  connect(deleteSelected, SIGNAL(triggered()), this, SLOT(DeleteSelected()));
  connect(  cropSelected, SIGNAL(triggered()), this, SLOT(  CropSelected()));
  connect(pasteClipboard, SIGNAL(triggered()), this, SLOT(PasteClipboard()));
  connect(copyCLR, SIGNAL(triggered()), this, SLOT(CopyCLR()));
  connect(copyBnW, SIGNAL(triggered()), this, SLOT(CopyBnW()));
  connect(newWin, SIGNAL(triggered()), this, SLOT(NewWindow()));
  edit_menu->addAction(deleteSelected);
  edit_menu->addAction(  cropSelected); edit_menu->addSeparator();
  edit_menu->addAction(pasteClipboard); edit_menu->addAction(copyCLR);
                                        edit_menu->addAction(copyBnW);
  //- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  colorMenu = menuBar()->addMenu("Color");
#define ADD_colorMenu(ico,text,shortcut) \
  colorMenu->addAction(*ico,text)->setShortcut(QKeySequence(shortcut))
  ADD_colorMenu(enBlancoIco,            "blanco",     "B");
  ADD_colorMenu(enRojoIco,              "rojo (red)", "R");
  ADD_colorMenu(enCastanoIco, Utf8("castaño (brown)"),"C");
  ADD_colorMenu(enVerdeIco,          "verde (green)", "V");
  ADD_colorMenu(enAzulIco,             "azul (blue)", "A");
  colorMenu->addSeparator();
  colorMenu->addAction("random Bicolor")->setShortcut(QKeySequence("Ctrl+B"));
  colorMenu->addAction("random Recolor")->setShortcut(QKeySequence("Ctrl+R"));
  colorMenu->addAction("Un-color all")  ->setShortcut(QKeySequence("Ctrl+U"));
  connect(colorMenu, SIGNAL(triggered(QAction*)),
               this, SLOT(SelectColor(QAction*)));
  //- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  QLabel *magIcon = new QLabel; magIcon->setPixmap(QPixmap(":/zoom3.png"));
  magText = new QLabel(QString("+1"));
  magText->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
  magText->setFont(fixedFont);
  magText->setMinimumSize(QSize(30,25));     bottom->addWidget(magText);
                                             bottom->addWidget(magIcon);
  fitView = new QAction(QIcon(":/full-size.png"), QString("fit"), this);
  connect(fitView, SIGNAL(triggered()), this, SLOT(DoFitView()));
  bottom->addAction(fitView);
  //- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  QMenu *play_menu = menuBar()->addMenu("Play");
  playGen = new QLabel(QString("0"));
  playGen->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
  playGen->setMinimumSize(QSize(66,25));
  prevGen =  new QAction(QIcon(":/step-back.png"),    QString("back"), this);
  nextGen =  new QAction(QIcon(":/go-forward.png") ,  QString("step"), this);
  playStop = new QAction(QIcon(":/fast-forward.png"), QString("go!"),  this);
  connect(prevGen,  SIGNAL(triggered()), this, SLOT(DoPrevGen()));
  connect(nextGen,  SIGNAL(triggered()), this, SLOT(DoNextGen()));
  connect(playStop, SIGNAL(triggered()), this, SLOT(DoPlayStop()));
  play_menu->addAction(nextGen);
  play_menu->addAction(playStop);
  play_menu->addAction(prevGen); prevGen->setEnabled(false);
  //- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  speedSlider = new QSlider(Qt::Horizontal, this);
  speedSlider->setMinimum(1); speedSlider->setValue(speed);
  speedSlider->setMaximum(4); speedSlider->setMaximumSize(50,22);
  speedSlider->setSingleStep(1);
  speedSlider->setTickInterval(1);
  speedSlider->setTickPosition(QSlider::TicksBelow);
  connect(speedSlider, SIGNAL(valueChanged(int)), this, SLOT(ChangeSpeed(int)));
  bottom->addWidget(playGen);
  bottom->addAction(nextGen);
  bottom->addWidget(speedSlider);
  bottom->addAction(playStop);
  addToolBar(Qt::BottomToolBarArea, bottom);
  //- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  if (fileToLoad) LoadTheWorld(fileToLoad);
  else                       SetWinTitle();
  show(); raise();
}