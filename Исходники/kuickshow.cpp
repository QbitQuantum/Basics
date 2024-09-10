bool KuickShow::eventFilter( QObject *o, QEvent *e )
{
    if ( m_delayedRepeatItem ) // we probably need to install an eventFilter over
	{
        return true;    // kapp, to make it really safe
	}

    bool ret = false;
    int eventType = e->type();
    QKeyEvent *k = 0L;
    if ( eventType == QEvent::KeyPress )
        k = static_cast<QKeyEvent *>( e );

    if ( k ) {
        if ( KStdAccel::quit().contains( KKey( k ) ) ) {
            saveSettings();
            deleteAllViewers();
            FileCache::shutdown();
            ::exit(0);
        }
        else if ( KStdAccel::help().contains( KKey( k ) ) ) {
            appHelpActivated();
            return true;
        }
    }


    ImageWindow *window = dynamic_cast<ImageWindow*>( o );

    if ( window ) {
        // The XWindow used to display Imlib's image is being resized when
        // switching images, causing enter- and leaveevents for this
        // ImageWindow, leading to the cursor being unhidden. So we simply
        // don't pass those events to KCursor to prevent that.
        if ( eventType != QEvent::Leave && eventType != QEvent::Enter )
            KCursor::autoHideEventFilter( o, e );

        m_viewer = window;
        QString img;
        KFileItem *item = 0L;      // the image to be shown
        KFileItem *item_next = 0L; // the image to be cached

        if ( k ) { // keypress
            ret = true;
            int key = k->key();

            // Key_Shift shouldn't load the browser in nobrowser mode, it
            // is used for zooming in the imagewindow
            // Key_Alt shouldn't either - otherwise Alt+F4 doesn't work, the
            // F4 gets eaten (by NetAccess' modal dialog maybe?)

            if ( !fileWidget )
            {
                if ( key != Key_Escape && key != Key_Shift && key != Key_Alt )
                {
                    KuickFile *file = m_viewer->currentFile();
//                    QFileInfo fi( m_viewer->filename() );
//                    start.setPath( fi.dirPath( true ) );
                    initGUI( file->url().upURL() );

                    // the fileBrowser will list the start-directory
                    // asynchronously so we can't immediately continue. There
                    // is no current-item and no next-item (actually no item
                    // at all). So we tell the browser the initial
                    // current-item and wait for it to tell us when it's ready.
                    // Then we will replay this KeyEvent.
                    delayedRepeatEvent( m_viewer, k );

                    // OK, once again, we have a problem with the now async and
                    // sync KDirLister :( If the startDir is already cached by
                    // KDirLister, we won't ever get that finished() signal
                    // because it is emitted before we can connect(). So if
                    // our dirlister has a rootFileItem, we assume the
                    // directory is read already and simply call
                    // slotReplayEvent() without the need for the finished()
                    // signal.

                    // see slotAdvanceImage() for similar code
                    if ( fileWidget->dirLister()->isFinished() )
                    {
                        if ( fileWidget->dirLister()->rootItem() )
                        {
                            fileWidget->setCurrentItem( file->url().fileName() );
                            QTimer::singleShot( 0, this, SLOT( slotReplayEvent()));
                        }
                        else // finished, but no root-item -- probably an error, kill repeat-item!
                        {
                            abortDelayedEvent();
                        }
                    }
                    else // not finished yet
                    {
                        fileWidget->setInitialItem( file->url().fileName() );
                        connect( fileWidget, SIGNAL( finished() ),
                                 SLOT( slotReplayEvent() ));
                    }

                    return true;
                }

                return KMainWindow::eventFilter( o, e );
            }

            // we definitely have a fileWidget here!

            KKey kkey( k );
            if ( key == Key_Home || KStdAccel::home().contains( kkey ) )
            {
                item = fileWidget->gotoFirstImage();
                item_next = fileWidget->getNext( false );
            }

            else if ( key == Key_End || KStdAccel::end().contains( kkey ) )
            {
                item = fileWidget->gotoLastImage();
                item_next = fileWidget->getPrevious( false );
            }

            else if ( fileWidget->actionCollection()->action("delete")->shortcut().contains( key ))
            {
                kdDebug() << "WOW, deletion happens here!" << endl;
//      KFileItem *cur = fileWidget->getCurrentItem( false );
                (void) fileWidget->getCurrentItem( false );
                item = fileWidget->getNext( false ); // don't move
                if ( !item )
                    item = fileWidget->getPrevious( false );
                KFileItem it( KFileItem::Unknown, KFileItem::Unknown,
                              m_viewer->url() );
                KFileItemList list;
                list.append( &it );
                if ( fileWidget->del(list, window,
                                     (k->state() & ShiftButton) == 0) == 0L )
                    return true; // aborted deletion

                // ### check failure asynchronously and restore old item?
                fileWidget->setCurrentItem( item );
            }

            else if ( m_toggleBrowserAction->shortcut().contains( key ) )
            {
                toggleBrowser();
                return true; // don't pass keyEvent
            }

            else
                ret = false;


            if ( FileWidget::isImage( item ) ) {
//                QString filename;
//                KIO::NetAccess::download(item->url(), filename, this);
                m_viewer->showNextImage( item->url() );

                if ( kdata->preloadImage && item_next ) { // preload next image
                    if ( FileWidget::isImage( item_next ) )
                        m_viewer->cacheImage( item_next->url() );
                }

                ret = true; // don't pass keyEvent
            }
        } // keyPressEvent on ImageWindow


        // doubleclick closes image window
        // and shows browser when last window closed via doubleclick
        else if ( eventType == QEvent::MouseButtonDblClick )
        {
            QMouseEvent *ev = static_cast<QMouseEvent*>( e );
            if ( ev->button() == LeftButton )
            {
                if ( s_viewers.count() == 1 )
                {
                    if ( !fileWidget )
                    {
//                        KURL start;
//                        QFileInfo fi( window->filename() );
//                        start.setPath( fi.dirPath( true ) );
                        initGUI( window->currentFile()->url().fileName() );
                    }
                    show();
                    raise();
                }

                window->close( true );

                ev->accept();
                ret = true;
            }
        }

    } // isA ImageWindow


    if ( ret )
        return true;

    return KMainWindow::eventFilter( o, e );
}