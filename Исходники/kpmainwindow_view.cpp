// private
void kpMainWindow::zoomTo (int zoomLevel, bool centerUnderCursor)
{
#if DEBUG_KP_MAIN_WINDOW
    kdDebug () << "kpMainWindow::zoomTo (" << zoomLevel << ")" << endl;
#endif

    if (zoomLevel <= 0)
        zoomLevel = m_mainView ? m_mainView->zoomLevelX () : 100;

// mute point since the thumbnail suffers from this too
#if 0
    else if (m_mainView && m_mainView->zoomLevelX () % 100 == 0 && zoomLevel % 100)
    {
        if (KMessageBox::warningContinueCancel (this,
            i18n ("Setting the zoom level to a value that is not a multiple of 100% "
                  "results in imprecise editing and redraw glitches.\n"
                  "Do you really want to set to zoom level to %1%?")
                .arg (zoomLevel),
            QString::null/*caption*/,
            i18n ("Set Zoom Level to %1%").arg (zoomLevel),
            "DoNotAskAgain_ZoomLevelNotMultipleOf100") != KMessageBox::Continue)
        {
            zoomLevel = m_mainView->zoomLevelX ();
        }
    }
#endif

    int index = 0;
    QValueVector <int>::Iterator it = m_zoomList.begin ();

    while (index < (int) m_zoomList.count () && zoomLevel > *it)
        it++, index++;

    if (zoomLevel != *it)
        m_zoomList.insert (it, zoomLevel);

    sendZoomListToActionZoom ();
    m_actionZoom->setCurrentItem (index);


    if (viewMenuDocumentActionsEnabled ())
    {
        m_actionActualSize->setEnabled (zoomLevel != 100);

        m_actionZoomIn->setEnabled (m_actionZoom->currentItem () < (int) m_zoomList.count () - 1);
        m_actionZoomOut->setEnabled (m_actionZoom->currentItem () > 0);
    }


    if (m_viewManager)
        m_viewManager->setQueueUpdates ();


    if (m_scrollView)
    {
        m_scrollView->setUpdatesEnabled (false);
        if (m_scrollView->viewport ())
            m_scrollView->viewport ()->setUpdatesEnabled (false);
    }

    if (m_mainView)
    {
        m_mainView->setUpdatesEnabled (false);

        if (m_scrollView && m_scrollView->viewport ())
        {
            // Ordinary flicker is better than the whole view moving
            QPainter p (m_mainView);
            p.fillRect (m_mainView->rect (),
                        m_scrollView->viewport ()->colorGroup ().background ());
        }
    }


    if (m_scrollView && m_mainView)
    {
    #if DEBUG_KP_MAIN_WINDOW && 1
        kdDebug () << "\tscrollView   contentsX=" << m_scrollView->contentsX ()
                   << " contentsY=" << m_scrollView->contentsY ()
                   << " contentsWidth=" << m_scrollView->contentsWidth ()
                   << " contentsHeight=" << m_scrollView->contentsHeight ()
                   << " visibleWidth=" << m_scrollView->visibleWidth ()
                   << " visibleHeight=" << m_scrollView->visibleHeight ()
                   << " oldZoomX=" << m_mainView->zoomLevelX ()
                   << " oldZoomY=" << m_mainView->zoomLevelY ()
                   << " newZoom=" << zoomLevel
                   << " mainViewX=" << m_scrollView->childX (m_mainView)
                   << " mainViewY=" << m_scrollView->childY (m_mainView)
                  << endl;
    #endif

        // TODO: when changing from no scrollbars to scrollbars, Qt lies about
        //       visibleWidth() & visibleHeight() (doesn't take into account the
        //       space taken by the would-be scrollbars) until it updates the
        //       scrollview; hence the centring is off by about 5-10 pixels.

        // TODO: use visibleRect() for greater accuracy?
        
        int viewX, viewY;
        
        bool targetDocAvail = false;
        double targetDocX, targetDocY;
        
        if (centerUnderCursor &&
            m_viewManager && m_viewManager->viewUnderCursor ())
        {
            kpView *const vuc = m_viewManager->viewUnderCursor ();
            QPoint viewPoint = vuc->mouseViewPoint ();
        
            // vuc->transformViewToDoc() returns QPoint which only has int
            // accuracy so we do X and Y manually.
            targetDocX = vuc->transformViewToDocX (viewPoint.x ());
            targetDocY = vuc->transformViewToDocY (viewPoint.y ());
            targetDocAvail = true;
                    
            if (vuc != m_mainView)
                viewPoint = vuc->transformViewToOtherView (viewPoint, m_mainView);
            
            viewX = viewPoint.x ();
            viewY = viewPoint.y ();
        }
        else
        {
            viewX = m_scrollView->contentsX () +
                        QMIN (m_mainView->width (),
                              m_scrollView->visibleWidth ()) / 2;
            viewY = m_scrollView->contentsY () +
                        QMIN (m_mainView->height (),
                              m_scrollView->visibleHeight ()) / 2;
        }
        
        int newCenterX = viewX * zoomLevel / m_mainView->zoomLevelX ();
        int newCenterY = viewY * zoomLevel / m_mainView->zoomLevelY ();

        m_mainView->setZoomLevel (zoomLevel, zoomLevel);
    #if DEBUG_ZOOM_FLICKER
    {
        kdDebug () << "FLICKER: just setZoomLevel" << endl;
        QTime timer; timer.start ();
        while (timer.elapsed () < 1000)
            ;
    }
    #endif

    #if DEBUG_KP_MAIN_WINDOW && 1
        kdDebug () << "\tvisibleWidth=" << m_scrollView->visibleWidth ()
                    << " visibleHeight=" << m_scrollView->visibleHeight ()
                    << endl;
        kdDebug () << "\tnewCenterX=" << newCenterX
                    << " newCenterY=" << newCenterY << endl;
    #endif

        m_scrollView->center (newCenterX, newCenterY);
    #if DEBUG_ZOOM_FLICKER
    {
        kdDebug () << "FLICKER: just centred" << endl;
        QTime timer; timer.start ();
        while (timer.elapsed () < 2000)
            ;
    }
    #endif

        if (centerUnderCursor &&
            targetDocAvail &&
            m_viewManager && m_viewManager->viewUnderCursor ())
        {
            kpView *const vuc = m_viewManager->viewUnderCursor ();
            
        #if DEBUG_KP_MAIN_WINDOW
            kdDebug () << "\tcenterUnderCursor: reposition cursor; viewUnderCursor="
                       << vuc->name () << endl;
        #endif
        
            const double viewX = vuc->transformDocToViewX (targetDocX);
            const double viewY = vuc->transformDocToViewY (targetDocY);
            // Rounding error from zooming in and out :(
            // TODO: do everything in terms of tool doc points in type "double".
            const QPoint viewPoint ((int) viewX, (int) viewY);
        #if DEBUG_KP_MAIN_WINDOW
            kdDebug () << "\t\tdoc: (" << targetDocX << "," << targetDocY << ")"
                       << " viewUnderCursor: (" << viewX << "," << viewY << ")"
                       << endl; 
        #endif
        
            if (vuc->clipRegion ().contains (viewPoint))
            {
                const QPoint globalPoint =
                    kpWidgetMapper::toGlobal (vuc, viewPoint);
            #if DEBUG_KP_MAIN_WINDOW
                kdDebug () << "\t\tglobalPoint=" << globalPoint << endl;
            #endif
                
                // TODO: Determine some sane cursor flashing indication -
                //       cursor movement is convenient but not conventional.
                //
                //       Major problem: if using QApplication::setOverrideCursor()
                //           and in some stage of flash and window quits.
                //
                //           Or if using kpView::setCursor() and change tool.
                QCursor::setPos (globalPoint);
            }
            // e.g. Zoom to 200%, scroll mainView to bottom-right.
            // Unzoomed Thumbnail shows top-left portion of bottom-right of
            // mainView.
            //
            // Aim cursor at bottom-right of thumbnail and zoom out with
            // CTRL+Wheel.
            //
            // If mainView is now small enough to largely not need scrollbars,
            // Unzoomed Thumbnail scrolls to show _top-left_ portion
            // _of top-left_ of mainView.
            //
            // Unzoomed Thumbnail no longer contains the point we zoomed out
            // on top of.
            else
            {
            #if DEBUG_KP_MAIN_WINDOW
                kdDebug () << "\t\twon't move cursor - would get outside view"
                           << endl;
            #endif
            
                // TODO: Sane cursor flashing indication that indicates
                //       that the normal cursor movement didn't happen.
            }
        }
        
    #if DEBUG_KP_MAIN_WINDOW && 1
        kdDebug () << "\t\tcheck (contentsX=" << m_scrollView->contentsX ()
                    << ",contentsY=" << m_scrollView->contentsY ()
                    << ")" << endl;
    #endif
    }

    if (m_mainView)
    {
        actionShowGridUpdate ();
    #if DEBUG_ZOOM_FLICKER
    {
        kdDebug () << "FLICKER: updated grid action" << endl;
        QTime timer; timer.start ();
        while (timer.elapsed () < 1000)
            ;
    }
    #endif


        updateMainViewGrid ();
    #if DEBUG_ZOOM_FLICKER
    {
        kdDebug () << "FLICKER: just updated grid" << endl;
        QTime timer; timer.start ();
        while (timer.elapsed () < 1000)
            ;
    }
    #endif


        // Since Zoom Level KSelectAction on ToolBar grabs focus after changing
        // Zoom, switch back to the Main View.
        // TODO: back to the last view
        m_mainView->setFocus ();
    #if DEBUG_ZOOM_FLICKER
    {
        kdDebug () << "FLICKER: just set focus to mainview" << endl;
        QTime timer; timer.start ();
        while (timer.elapsed () < 1000)
            ;
    }
    #endif

    }
#if 1
    // The view magnified and moved beneath the cursor
    if (tool ())
        tool ()->somethingBelowTheCursorChanged ();
    #if DEBUG_ZOOM_FLICKER
    {
        kdDebug () << "FLICKER: signalled something below cursor" << endl;
        QTime timer; timer.start ();
        while (timer.elapsed () < 1000)
            ;
    }
    #endif
#endif

    // HACK: make sure all of Qt's update() calls trigger
    //       kpView::paintEvent() _now_ so that they can be queued by us
    //       (until kpViewManager::restoreQueueUpdates()) to reduce flicker
    //       caused mainly by m_scrollView->center()
    //
    // TODO: remove flicker completely
    //QTimer::singleShot (0, this, SLOT (finishZoomTo ()));

    // Later: I don't think there is an update() that needs to be queued
    //        - let's reduce latency instead.
    finishZoomTo ();
}