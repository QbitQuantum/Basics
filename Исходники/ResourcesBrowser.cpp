void ResourcesBrowser::setupBookmarks()
{
   ASSERT( m_tabsManager != NULL );

   QString topObjectName( "ResourcesBrowser/bookmarksFrame" );

   // frame
   QFrame* frame = NULL;
   QVBoxLayout* layout = NULL;
   {
      frame = new QFrame( m_tabsManager );
      frame->setObjectName( topObjectName );
      layout = new QVBoxLayout( frame );
      frame->setLayout( layout );
      layout->setSpacing(0);
      layout->setMargin(0);
      m_tabsManager->addTab( frame, "Bookmarks" );
   }

   // bookmarks list
   {
      m_bookmarks = new QListWidget( m_tabsManager );
      m_bookmarks->setContextMenuPolicy( Qt::CustomContextMenu );
      m_bookmarks->setObjectName( topObjectName + "/m_bookmarks" );
      layout->addWidget( m_bookmarks );

      connect( m_bookmarks, SIGNAL( itemDoubleClicked( QListWidgetItem* ) ), this, SLOT( onFocusOnFile( QListWidgetItem* ) ) );
      connect( m_bookmarks, SIGNAL( customContextMenuRequested( const QPoint& ) ), this, SLOT( showBookmarksPopupMenu( const QPoint& ) ) );
   }
}