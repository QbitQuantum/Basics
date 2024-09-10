OpenDialog::OpenDialog(
   QWidget* pParent, const QString& n1, const QString& n2, const QString& n3,
   bool bMerge, const QString& outputName, const char* slotConfigure, OptionDialog* pOptions )
: QDialog( pParent )
{
   setObjectName("OpenDialog");
   setModal(true);
   m_pOptions = pOptions;

   QVBoxLayout* v = new QVBoxLayout( this );
   v->setMargin(5);
   QGridLayout* h = new QGridLayout();
   v->addLayout(h);
   h->setSpacing( 5 );
   h->setColumnStretch( 1, 10 );

   QLabel* label  = new QLabel( i18n("A (Base):"), this );

   m_pLineA = new QComboBox();
   m_pLineA->setEditable(true);
   m_pLineA->insertItems( 0, m_pOptions->m_recentAFiles );
   m_pLineA->setEditText( KUrl(n1).prettyUrl() );
   m_pLineA->setMinimumWidth( 200 );
   QPushButton * button = new QPushButton( i18n("File..."), this );
   connect( button, SIGNAL(clicked()), this, SLOT( selectFileA() ) );
   QPushButton * button2 = new QPushButton( i18n("Dir..."), this );
   connect( button2, SIGNAL(clicked()), this, SLOT( selectDirA() ) );
   connect( m_pLineA, SIGNAL(editTextChanged(const QString&)), this, SLOT(inputFilenameChanged() ) );

   h->addWidget( label,    0, 0 );
   h->addWidget( m_pLineA,  0, 1 );
   h->addWidget( button,   0, 2 );
   h->addWidget( button2,  0, 3 );

   label    = new QLabel( "B:", this );
   m_pLineB  = new QComboBox();
   m_pLineB->setEditable(true);
   m_pLineB->insertItems( 0, m_pOptions->m_recentBFiles );
   m_pLineB->setEditText( KUrl(n2).prettyUrl() );
   m_pLineB->setMinimumWidth( 200 );
   button   = new QPushButton( i18n("File..."), this );
   connect( button, SIGNAL(clicked()), this, SLOT( selectFileB() ) );
   button2   = new QPushButton( i18n("Dir..."), this );
   connect( button2, SIGNAL(clicked()), this, SLOT( selectDirB() ) );
   connect( m_pLineB, SIGNAL(editTextChanged(const QString&)), this, SLOT(inputFilenameChanged() ) );

   h->addWidget( label,     1, 0 );
   h->addWidget( m_pLineB,  1, 1 );
   h->addWidget( button,    1, 2 );
   h->addWidget( button2,   1, 3 );

   label  = new QLabel( i18n("C (Optional):"), this );
   m_pLineC= new QComboBox();
   m_pLineC->setEditable(true);
   m_pLineC->insertItems( 0, m_pOptions->m_recentCFiles );
   m_pLineC->setEditText( KUrl(n3).prettyUrl() );
   m_pLineC->setMinimumWidth( 200 );
   button = new QPushButton( i18n("File..."), this );
   connect( button, SIGNAL(clicked()), this, SLOT( selectFileC() ) );
   button2   = new QPushButton( i18n("Dir..."), this );
   connect( button2, SIGNAL(clicked()), this, SLOT( selectDirC() ) );
   connect( m_pLineC, SIGNAL(editTextChanged(const QString&)), this, SLOT(inputFilenameChanged() ) );

   h->addWidget( label,     2, 0 );
   h->addWidget( m_pLineC,   2, 1 );
   h->addWidget( button,    2, 2 );
   h->addWidget( button2,   2, 3 );

   m_pMerge = new QCheckBox( i18n("Merge"), this );
   h->addWidget( m_pMerge, 3, 0 );

   QHBoxLayout* hl = new QHBoxLayout();
   h->addLayout( hl, 3, 1 );
   hl->addStretch(2);
   button = new QPushButton(i18n("Swap/Copy Names ..."), this);
   //button->setToggleButton(false);
   hl->addWidget( button );

   QMenu* m = new QMenu(this);
   m->addAction( i18n("Swap %1<->%2", QString("A"),QString("B") ));
   m->addAction( i18n("Swap %1<->%2",QString("B"),QString("C") ));
   m->addAction( i18n("Swap %1<->%2",QString("C"),QString("A") ));
   m->addAction( i18n("Copy %1->Output",QString("A")  ));
   m->addAction( i18n("Copy %1->Output",QString("B")  ));
   m->addAction( i18n("Copy %1->Output",QString("C")  ));
   m->addAction( i18n("Swap %1<->Output",QString("A") ));
   m->addAction( i18n("Swap %1<->Output",QString("B") ));
   m->addAction( i18n("Swap %1<->Output",QString("C") ));
   connect( m, SIGNAL(triggered(QAction*)), this, SLOT(slotSwapCopyNames(QAction*)));
   button->setMenu(m);


   hl->addStretch(2);

   label  = new QLabel( i18n("Output (optional):"), this );
   m_pLineOut = new QComboBox();
   m_pLineOut->setEditable(true);
   m_pLineOut->insertItems( 0, m_pOptions->m_recentOutputFiles );
   m_pLineOut->setEditText( KUrl(outputName).prettyUrl() );
   m_pLineOut->setMinimumWidth( 200 );
   button = new QPushButton( i18n("File..."), this );
   connect( button, SIGNAL(clicked()), this, SLOT( selectOutputName() ) );
   button2   = new QPushButton( i18n("Dir..."), this );
   connect( button2, SIGNAL(clicked()), this, SLOT( selectOutputDir() ) );
   connect( m_pMerge, SIGNAL(stateChanged(int)), this, SLOT(internalSlot(int)) );
   connect( this, SIGNAL(internalSignal(bool)), m_pLineOut, SLOT(setEnabled(bool)) );
   connect( this, SIGNAL(internalSignal(bool)), button, SLOT(setEnabled(bool)) );
   connect( this, SIGNAL(internalSignal(bool)), button2, SLOT(setEnabled(bool)) );

   m_pMerge->setChecked( !bMerge );
   m_pMerge->setChecked( bMerge );
//   m_pLineOutput->setEnabled( bMerge );

//   button->setEnabled( bMerge );

   h->addWidget( label,          4, 0 );
   h->addWidget( m_pLineOut,      4, 1 );
   h->addWidget( button,         4, 2 );
   h->addWidget( button2,        4, 3 );

   h->addItem(new QSpacerItem(200, 0), 0, 1);

   QHBoxLayout* l = new QHBoxLayout();
   v->addLayout( l );
   l->setSpacing(5);

   button = new QPushButton( i18n("Configure..."), this );
   connect( button, SIGNAL(clicked()), pParent, slotConfigure );
   l->addWidget( button, 1 );

   l->addStretch(1);

   button = new QPushButton( i18n("&OK"), this );
   button->setDefault( true );
   connect( button, SIGNAL(clicked()), this, SLOT( accept() ) );
   l->addWidget( button, 1 );

   button = new QPushButton( i18n("&Cancel"), this );
   connect( button, SIGNAL(clicked()), this, SLOT( reject() ) );
   l->addWidget( button,1 );

   QSize sh = sizeHint();
   setFixedHeight( sh.height() );
   m_bInputFileNameChanged = false;

#ifdef KREPLACEMENTS_H
   m_pLineA->lineEdit()->installEventFilter( this );
   m_pLineB->lineEdit()->installEventFilter( this );
   m_pLineC->lineEdit()->installEventFilter( this );
   m_pLineOut->lineEdit()->installEventFilter( this );
#endif
}