void QQnxWindow::setBufferSize(const QSize &size)
{
    qWindowDebug() << Q_FUNC_INFO << "window =" << window() << "size =" << size;

    // libscreen fails when creating empty buffers
    const QSize nonEmptySize = size.isEmpty() ? QSize(1, 1) : size;
    int format = pixelFormat();

    if (nonEmptySize == m_bufferSize || format == -1)
        return;

    Q_SCREEN_CRITICALERROR(
            screen_set_window_property_iv(m_window, SCREEN_PROPERTY_FORMAT, &format),
            "Failed to set window format");

    if (m_bufferSize.isValid()) {
        // destroy buffers first, if resized
        Q_SCREEN_CRITICALERROR(screen_destroy_window_buffers(m_window),
                               "Failed to destroy window buffers");
    }

    int val[2] = { nonEmptySize.width(), nonEmptySize.height() };
    Q_SCREEN_CHECKERROR(screen_set_window_property_iv(m_window, SCREEN_PROPERTY_BUFFER_SIZE, val),
                        "Failed to set window buffer size");

    Q_SCREEN_CRITICALERROR(screen_create_window_buffers(m_window, MAX_BUFFER_COUNT),
                           "Failed to create window buffers");

    // check if there are any buffers available
    int bufferCount = 0;
    Q_SCREEN_CRITICALERROR(
        screen_get_window_property_iv(m_window, SCREEN_PROPERTY_RENDER_BUFFER_COUNT, &bufferCount),
        "Failed to query render buffer count");

    if (bufferCount != MAX_BUFFER_COUNT) {
        qFatal("QQnxWindow: invalid buffer count. Expected = %d, got = %d.",
                MAX_BUFFER_COUNT, bufferCount);
    }

    // Set the transparency. According to QNX technical support, setting the window
    // transparency property should always be done *after* creating the window
    // buffers in order to guarantee the property is paid attention to.
    if (window()->requestedFormat().alphaBufferSize() == 0) {
        // To avoid overhead in the composition manager, disable blending
        // when the underlying window buffer doesn't have an alpha channel.
        val[0] = SCREEN_TRANSPARENCY_NONE;
    } else {
        // Normal alpha blending. This doesn't commit us to translucency; the
        // normal backfill during the painting will contain a fully opaque
        // alpha channel unless the user explicitly intervenes to make something
        // transparent.
        val[0] = SCREEN_TRANSPARENCY_SOURCE_OVER;
    }

    Q_SCREEN_CHECKERROR(screen_set_window_property_iv(m_window, SCREEN_PROPERTY_TRANSPARENCY, val),
                        "Failed to set window transparency");

    // Cache new buffer size
    m_bufferSize = nonEmptySize;
    resetBuffers();
}