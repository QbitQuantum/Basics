Void PlaYUVerApp::createMenus()
{
  m_arrayMenu.resize( TOTAL_MENUS );

  m_arrayMenu[FILE_MENU] = menuBar()->addMenu( tr( "&File" ) );
  m_arrayMenu[FILE_MENU]->addAction( m_arrayActions[OPEN_ACT] );
  m_arrayMenu[RECENT_MENU] = m_arrayMenu[FILE_MENU]->addMenu( tr( "Open Recent" ) );
  for( Int i = 0; i < MAX_RECENT_FILES; ++i )
  {
    m_arrayMenu[RECENT_MENU]->addAction( m_arrayRecentFilesActions[i] );
  }

  m_arrayMenu[FILE_MENU]->addAction( m_arrayActions[SAVE_ACT] );
  m_arrayMenu[FILE_MENU]->addSeparator();
  m_arrayMenu[FILE_MENU]->addAction( m_arrayActions[FORMAT_ACT] );
  m_arrayMenu[FILE_MENU]->addAction( m_arrayActions[RELOAD_ACT] );
  m_arrayMenu[FILE_MENU]->addAction( m_arrayActions[RELOAD_ALL_ACT] );
  m_arrayMenu[FILE_MENU]->addAction( m_arrayActions[LOAD_ALL_ACT] );
  m_arrayMenu[FILE_MENU]->addSeparator();
  m_arrayMenu[FILE_MENU]->addAction( m_arrayActions[CLOSE_ACT] );
  m_arrayMenu[FILE_MENU]->addAction( m_arrayActions[EXIT_ACT] );

  m_arrayMenu[VIEW_MENU] = menuBar()->addMenu( tr( "&View" ) );
  m_arrayMenu[VIEW_MENU]->addAction( m_arrayActions[ZOOM_IN_ACT] );
  m_arrayMenu[VIEW_MENU]->addAction( m_arrayActions[ZOOM_OUT_ACT] );
  m_arrayMenu[VIEW_MENU]->addAction( m_arrayActions[ZOOM_NORMAL_ACT] );
  m_arrayMenu[VIEW_MENU]->addAction( m_arrayActions[ZOOM_FIT_ACT] );
  m_arrayMenu[VIEW_MENU]->addAction( m_arrayActions[ZOOM_FIT_ALL_ACT] );

  m_arrayMenu[VIEW_MENU]->addSeparator();

// createPopupMenu() Returns a popup menu containing checkable entries for
// the toolbars and dock widgets present in the main window.
  m_arrayMenu[DOCK_VIEW_MENU] = createPopupMenu();
  if( m_arrayMenu[DOCK_VIEW_MENU] )
  {
    QAction *actionPopupMenu = m_arrayMenu[VIEW_MENU]->addMenu( m_arrayMenu[DOCK_VIEW_MENU] );
    actionPopupMenu->setText( tr( "&Toolbars/Docks" ) );
  }

  menuBar()->addMenu( m_appModuleVideo->createVideoMenu() );
  menuBar()->addMenu( m_appModuleVideo->createImageMenu() );
  QMenu* QualityMenu = m_appModuleQuality->createMenu();
  menuBar()->addMenu( QualityMenu );
  QMenu* ModuleMenu = m_appModuleExtensions->createMenu();
  menuBar()->addMenu( ModuleMenu );
  QMenu* windowMenu = m_pcWindowHandle->createMenu();
  menuBar()->addMenu( windowMenu );

  menuBar()->addSeparator();

  m_arrayMenu[ABOUT_MENU] = menuBar()->addMenu( tr( "&Help" ) );
#ifdef USE_FERVOR
  m_arrayMenu[ABOUT_MENU]->addAction( m_arrayActions[UPDATE_ACT] );
#endif
  m_arrayMenu[ABOUT_MENU]->addSeparator();
  m_arrayMenu[ABOUT_MENU]->addAction( m_arrayActions[ABOUT_ACT] );
  m_arrayMenu[ABOUT_MENU]->addAction( m_arrayActions[ABOUTQT_ACT] );

}