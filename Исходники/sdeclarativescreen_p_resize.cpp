void SDeclarativeScreenPrivateResize::setAllowedOrientations(SDeclarativeScreen::Orientations orientations)
{
#ifdef Q_DEBUG_SCREEN
    qDebug() << "SDeclarativeScreenPrivateResize::setAllowedOrientations" << orientations;
#endif

#if defined(Q_OS_SYMBIAN)
    if((orientations != SDeclarativeScreen::Landscape) && deviceSupportsOnlyLandscape())
        return;
#endif

    SDeclarativeScreenPrivate::setAllowedOrientations(orientations);

    if (!m_initialized)
        return;

#if defined(Q_OS_SYMBIAN) || defined(Q_WS_SIMULATOR)
    if (portraitAllowed() && landscapeAllowed() && m_view)
        m_view->setAttribute(Qt::WA_AutoOrientation, true);
    else if (portraitAllowed() && !landscapeAllowed() && m_view)
        m_view->setAttribute(Qt::WA_LockPortraitOrientation, true);
    else if (!portraitAllowed() && landscapeAllowed() && m_view)
        m_view->setAttribute(Qt::WA_LockLandscapeOrientation, true);

    setScreenSize(enforceFixedOrientation(systemScreenSize()));
#else

    QSize newScreenSize = m_displaySize;
    if (portraitAllowed() && landscapeAllowed() && !portraitDisplay())
        newScreenSize.transpose();
    else if (portraitAllowed() && !landscapeAllowed() && !portraitDisplay())
        newScreenSize.transpose();
    else if (!portraitAllowed() && landscapeAllowed() && portraitDisplay())
        newScreenSize.transpose();

    if (m_view)
        m_view->resize(newScreenSize);
    else
        setScreenSize(newScreenSize);
#endif
}