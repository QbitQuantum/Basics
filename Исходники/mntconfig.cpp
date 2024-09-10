MntConfigWidget::MntConfigWidget(TQWidget *parent, const char *name, bool init)
  : TQWidget(parent, name)
{
  mInitializing = false;

  GUI = !init;
  if (GUI)
  {
    //tabList fillup waits until disklist.readDF() is done...
    mDiskList.readFSTAB();
    mDiskList.readDF();
    mInitializing = true;
    connect( &mDiskList,TQT_SIGNAL(readDFDone()),this,TQT_SLOT(readDFDone()));

    TQString text;
    TQVBoxLayout *topLayout = new TQVBoxLayout( this, 0, KDialog::spacingHint());

    mList = new CListView( this, "list", 8 );
    mList->setAllColumnsShowFocus( true );
    mList->addColumn( i18n("Icon") );
    mList->addColumn( i18n("Device") );
    mList->addColumn( i18n("Mount Point") );
    mList->addColumn( i18n("Mount Command") );
    mList->addColumn( i18n("Unmount Command") );
    mList->setFrameStyle( TQFrame::WinPanel + TQFrame::Sunken );
    connect( mList, TQT_SIGNAL(selectionChanged(TQListViewItem *)),
	     this, TQT_SLOT(clicked(TQListViewItem *)));

    topLayout->addWidget( mList );

    text = TQString("%1: %2  %3: %4").
      arg(mList->header()->label(DEVCOL)).
      arg(i18n("None")).
      arg(mList->header()->label(MNTPNTCOL)).
      arg(i18n("None"));
    mGroupBox = new TQGroupBox( text, this );
    TQ_CHECK_PTR(mGroupBox);
    topLayout->addWidget(mGroupBox);

    TQGridLayout *gl = new TQGridLayout(mGroupBox, 3, 4, KDialog::spacingHint());
    if( gl == 0 ) { return; }
    gl->addRowSpacing( 0, fontMetrics().lineSpacing() );

    mIconLineEdit = new TQLineEdit(mGroupBox);
    TQ_CHECK_PTR(mIconLineEdit);
    mIconLineEdit->setMinimumWidth( fontMetrics().maxWidth()*10 );
    connect( mIconLineEdit, TQT_SIGNAL(textChanged(const TQString&)),
	     this,TQT_SLOT(iconChanged(const TQString&)));
    connect( mIconLineEdit, TQT_SIGNAL(textChanged(const TQString&)),
	     this,TQT_SLOT(slotChanged()));
    gl->addWidget( mIconLineEdit, 2, 0 );

    mIconButton = new TDEIconButton(mGroupBox);
    mIconButton->setIconType(TDEIcon::Small, TDEIcon::Device);
    TQ_CHECK_PTR(mIconButton);
    mIconButton->setFixedWidth( mIconButton->sizeHint().height() );
    connect(mIconButton,TQT_SIGNAL(iconChanged(TQString)),this,TQT_SLOT(iconChangedButton(TQString)));
    gl->addWidget( mIconButton, 2, 1 );

    //Mount
    mMountButton = new TQPushButton( i18n("Get Mount Command"), mGroupBox );
    TQ_CHECK_PTR(mMountButton);
    connect(mMountButton,TQT_SIGNAL(clicked()),this,TQT_SLOT(selectMntFile()));
    gl->addWidget( mMountButton, 1, 2 );

    mMountLineEdit = new TQLineEdit(mGroupBox);
    TQ_CHECK_PTR(mMountLineEdit);
    mMountLineEdit->setMinimumWidth( fontMetrics().maxWidth()*10 );
    connect(mMountLineEdit,TQT_SIGNAL(textChanged(const TQString&)),
	    this,TQT_SLOT(mntCmdChanged(const TQString&)));
    connect( mMountLineEdit, TQT_SIGNAL(textChanged(const TQString&)),
	     this,TQT_SLOT(slotChanged()));
    gl->addWidget( mMountLineEdit, 1, 3 );

    //Umount
    mUmountButton = new TQPushButton(i18n("Get Unmount Command"), mGroupBox );
    TQ_CHECK_PTR( mUmountButton );
    connect(mUmountButton,TQT_SIGNAL(clicked()),this,TQT_SLOT(selectUmntFile()));
    gl->addWidget( mUmountButton, 2, 2 );

    mUmountLineEdit=new TQLineEdit(mGroupBox);
    TQ_CHECK_PTR(mUmountLineEdit);
    mUmountLineEdit->setMinimumWidth( fontMetrics().maxWidth()*10 );
    connect(mUmountLineEdit,TQT_SIGNAL(textChanged(const TQString&)),
	    this,TQT_SLOT(umntCmdChanged(const TQString&)));
    connect( mUmountLineEdit, TQT_SIGNAL(textChanged(const TQString&)),
	     this,TQT_SLOT(slotChanged()));
    gl->addWidget( mUmountLineEdit, 2, 3 );

  }

  loadSettings();
  if(init)
  {
    applySettings();
    mDiskLookup.resize(0);
  }

  mGroupBox->setEnabled( false );
}