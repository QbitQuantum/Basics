/** Constructor */
PhotoDialog::PhotoDialog(QWidget *parent)
: MainPage(parent)
{
  /* Invoke the Qt Designer generated object setup routine */
  ui.setupUi(this);

  connect( ui.peerTreeWidget, SIGNAL( customContextMenuRequested( QPoint ) ), this, SLOT( peerTreeWidgetCustomPopupMenu( QPoint ) ) );
  connect( ui.photoTreeWidget, SIGNAL( customContextMenuRequested( QPoint ) ), this, SLOT( photoTreeWidgetCustomPopupMenu( QPoint ) ) );

  connect( ui.peerTreeWidget, SIGNAL( currentItemChanged ( QTreeWidgetItem * , QTreeWidgetItem * ) ), this, SLOT( updatePhotoList( ) ) );

  connect( ui.photoTreeWidget, SIGNAL( itemDoubleClicked ( QTreeWidgetItem * , int ) ), this, SLOT( showPhoto( QTreeWidgetItem *, int ) ) );
  connect( ui.addButton, SIGNAL( clicked( ) ), this, SLOT( addPhotos( ) ) );
  connect( ui.expandButton, SIGNAL(clicked()), this, SLOT(togglefileview()));

  /* hide the Tree +/- */
  ui.photoTreeWidget -> setRootIsDecorated( false );

  QSize iconSize(PHOTO_ICON_SIZE,PHOTO_ICON_SIZE);
  ui.photoTreeWidget->setIconSize(iconSize);
  
  /* Set header resize modes and initial section sizes */
  QHeaderView * ptw_header = ui.peerTreeWidget->header () ;
  ptw_header->setResizeMode (0, QHeaderView::Interactive);

  ptw_header->resizeSection ( 0, 175 );



	/* Set a GUI update timer - much cleaner than
	 * doing everything through the notify agent 
	 */

  QTimer *timer = new QTimer(this);
  timer->connect(timer, SIGNAL(timeout()), this, SLOT(checkUpdate()));
  timer->start(1000);
}