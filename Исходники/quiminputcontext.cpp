QUimInputContext::~QUimInputContext()
{
#ifdef ENABLE_DEBUG
    qDebug( "~QUimInputContext()" );
#endif

    contextList.remove( this );

    if ( m_uc )
        uim_release_context( m_uc );

    if ( this == focusedInputContext )
    {
        focusedInputContext = NULL;
        disableFocusedContext = true;
    }

#ifdef Q_WS_X11
    delete mCompose;
#endif
}