/** Constructor */
PeersDialog::PeersDialog(QWidget *parent)
            : RsAutoUpdatePage(1000,parent),
              historyKeeper(Rshare::dataDirectory() + "/his1.xml")
{
  /* Invoke the Qt Designer generated object setup routine */
  ui.setupUi(this);

  connect( ui.peertreeWidget, SIGNAL( customContextMenuRequested( QPoint ) ), this, SLOT( peertreeWidgetCostumPopupMenu( QPoint ) ) );
  connect( ui.peertreeWidget, SIGNAL( itemDoubleClicked ( QTreeWidgetItem *, int)), this, SLOT(chatfriend()));

  /* hide the Tree +/- */
  ui.peertreeWidget -> setRootIsDecorated( false );
  
    /* Set header resize modes and initial section sizes */
	QHeaderView * _header = ui.peertreeWidget->header () ;
   	_header->setResizeMode (0, QHeaderView::Custom);
	_header->setResizeMode (1, QHeaderView::Interactive);
	_header->setResizeMode (2, QHeaderView::Interactive);
	/*_header->setResizeMode (3, QHeaderView::Interactive);
	_header->setResizeMode (4, QHeaderView::Interactive);
	_header->setResizeMode (5, QHeaderView::Interactive);
	_header->setResizeMode (6, QHeaderView::Interactive);
	_header->setResizeMode (7, QHeaderView::Interactive);*/

    
	_header->resizeSection ( 0, 25 );
	_header->resizeSection ( 1, 100 );
	_header->resizeSection ( 2, 100 );
	/*_header->resizeSection ( 3, 120 );
	_header->resizeSection ( 4, 100 );
	_header->resizeSection ( 5, 230 );
	_header->resizeSection ( 6, 120 );
	_header->resizeSection ( 7, 220 );*/
	
    // set header text aligment
	QTreeWidgetItem * headerItem = ui.peertreeWidget->headerItem();
	headerItem->setTextAlignment(0, Qt::AlignHCenter | Qt::AlignVCenter);
	headerItem->setTextAlignment(1, Qt::AlignHCenter | Qt::AlignVCenter);
	headerItem->setTextAlignment(2, Qt::AlignHCenter | Qt::AlignVCenter);

	
	  
  loadEmoticonsgroupchat();
  
  //setWindowIcon(QIcon(QString(":/images/rstray3.png")));

  connect(ui.lineEdit, SIGNAL(textChanged ( ) ), this, SLOT(checkChat( ) ));
  connect(ui.Sendbtn, SIGNAL(clicked()), this, SLOT(sendMsg()));
  connect(ui.emoticonBtn, SIGNAL(clicked()), this, SLOT(smileyWidgetgroupchat()));

   
  //connect( ui.msgSendList, SIGNAL( customContextMenuRequested( QPoint ) ), this, SLOT( msgSendListCostumPopupMenu( QPoint ) ) );
  connect( ui.msgText, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(displayInfoChatMenu(const QPoint&)));
 
  connect(ui.textboldChatButton, SIGNAL(clicked()), this, SLOT(setFont()));  
  connect(ui.textunderlineChatButton, SIGNAL(clicked()), this, SLOT(setFont()));  
  connect(ui.textitalicChatButton, SIGNAL(clicked()), this, SLOT(setFont()));
  connect(ui.fontsButton, SIGNAL(clicked()), this, SLOT(getFont()));  
  connect(ui.colorChatButton, SIGNAL(clicked()), this, SLOT(setColor()));
   
  ui.fontsButton->setIcon(QIcon(QString(":/images/fonts.png")));
  
  _currentColor = Qt::black;
  QPixmap pxm(16,16);
  pxm.fill(_currentColor);
  ui.colorChatButton->setIcon(pxm);
  
  mCurrentFont = QFont("Comic Sans MS", 12);
  ui.lineEdit->setFont(mCurrentFont);
  
  setChatInfo(tr("Welcome to RetroShare's group chat."),
              QString::fromUtf8("blue"));

  QStringList him;
  historyKeeper.getMessages(him, "", "THIS", 8);
  foreach(QString mess, him)
      ui.msgText->append(mess);
      //setChatInfo(mess,  "green");
              
  
  QMenu * grpchatmenu = new QMenu();
  grpchatmenu->addAction(ui.actionClearChat);
  ui.menuButton->setMenu(grpchatmenu);
  
  _underline = false;

  QTimer *timer = new QTimer(this);
  timer->connect(timer, SIGNAL(timeout()), this, SLOT(insertChat()));
  timer->start(500); /* half a second */

	ui.peertreeWidget->sortItems( 1, Qt::AscendingOrder );


  /* Hide platform specific features */
#ifdef Q_WS_WIN

#endif
}