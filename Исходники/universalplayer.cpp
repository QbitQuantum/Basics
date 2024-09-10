    // Overridden from QAbstractVideoSurface
    virtual bool start( const QVideoSurfaceFormat &format )
    {
        m_mutex.lock();

        m_flipped = ( format.scanLineDirection() == QVideoSurfaceFormat::BottomToTop );
        m_frameFormat = QVideoFrame::imageFormatFromPixelFormat( format.pixelFormat() );
        m_viewport = format.viewport();
        m_valid = 1;

        // We want to unlock it before calling the parent function, which may call present() and deadlock
        m_mutex.unlock();

        return QAbstractVideoSurface::start( format );
    }