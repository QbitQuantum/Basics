SelectionView::SelectionView(Gui::Document* pcDocument, QWidget *parent)
  : DockWindow(pcDocument,parent)
{
    setWindowTitle( tr( "Property View" ) );

    QVBoxLayout* pLayout = new QVBoxLayout( this ); 
    pLayout->setSpacing( 0 );
    pLayout->setMargin ( 0 );

    QLineEdit* searchBox = new QLineEdit(this);
#if QT_VERSION >= 0x040700
    searchBox->setPlaceholderText( tr( "Search" ) );
#endif
    searchBox->setToolTip( tr( "Searches object labels" ) );
    pLayout->addWidget( searchBox );
    QHBoxLayout* llayout = new QHBoxLayout(searchBox);
    QToolButton* clearButton = new QToolButton(searchBox);
    clearButton->setFixedSize(18, 21);
    clearButton->setCursor(Qt::ArrowCursor);
    clearButton->setStyleSheet(QString::fromAscii("QToolButton {margin-bottom:6px}"));
    clearButton->setIcon(BitmapFactory().pixmap(":/icons/edit-cleartext.svg"));
    clearButton->setToolTip( tr( "Clears the search field" ) );
    llayout->addWidget(clearButton,0,Qt::AlignRight);

    selectionView = new QListWidget(this);
    selectionView->setContextMenuPolicy(Qt::CustomContextMenu);
    pLayout->addWidget( selectionView );
    resize( 200, 200 );

    QObject::connect(clearButton, SIGNAL(clicked()), searchBox, SLOT(clear()));
    QObject::connect(searchBox, SIGNAL(textChanged(QString)), this, SLOT(search(QString)));
    QObject::connect(selectionView, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(select(QListWidgetItem*)));
    QObject::connect(selectionView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(onItemContextMenu(QPoint)));
    
    Gui::Selection().Attach(this);
}