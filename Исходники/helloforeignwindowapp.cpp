bool HelloForeignWindowApp::createForeignWindow(const QString &group, const QString id, int x,
        int y, int width, int height)
{
    QByteArray groupArr = group.toAscii();
    QByteArray idArr = id.toAscii();

    // Window source rectangle.
    mRect[0] = 0;
    mRect[1] = 0;
    mRect[2] = width;
    mRect[3] = height;

    // You must create a context before you create a window.
    if (screen_create_context(&mScreenCtx, SCREEN_APPLICATION_CONTEXT) != 0) {
        return false;
    }

    // Create a child window of the current window group, join the window group and set
    // a window id.
    if (screen_create_window_type(&mScreenWindow, mScreenCtx, SCREEN_CHILD_WINDOW) != 0) {
        return false;
    }
    if (screen_join_window_group(mScreenWindow, groupArr.constData()) != 0) {
        return false;
    }
    if (screen_set_window_property_cv(mScreenWindow, SCREEN_PROPERTY_ID_STRING, idArr.length(),
            idArr.constData()) != 0) {
        return false;
    }

    // In this application we will render to a pixmap buffer and then blit that to
    // the window, we set the usage to native (default is read and write but we do not need that here).
    int usage = SCREEN_USAGE_NATIVE;
    if (screen_set_window_property_iv(mScreenWindow, SCREEN_PROPERTY_USAGE, &usage) != 0) {
        return false;
    }

    // The window size is specified in QML so we need to set up the buffer size to
    // correspond to that, the default size would be the full screen.
    if (screen_set_window_property_iv(mScreenWindow, SCREEN_PROPERTY_BUFFER_SIZE, mRect + 2) != 0) {
        return false;
    }
    if (screen_set_window_property_iv(mScreenWindow, SCREEN_PROPERTY_SOURCE_SIZE, mRect + 2) != 0) {
        return false;
    }

    // Use negative Z order so that the window appears under the main window.
    // This is needed by the ForeignWindow functionality.
    int z = -5;
    if (screen_set_window_property_iv(mScreenWindow, SCREEN_PROPERTY_ZORDER, &z) != 0) {
        return false;
    }

    // Set the window position on screen.
    int pos[2] = { x, y };
    if (screen_set_window_property_iv(mScreenWindow, SCREEN_PROPERTY_POSITION, pos) != 0) {
        return false;
    }

    // Finally create the window buffers, in this application we will only use one buffer.
    if (screen_create_window_buffers(mScreenWindow, 1) != 0) {
        return false;
    }

    // In this sample we use a pixmap to render to, a pixmap. This allows us to have
    // full control of exactly which pixels we choose to push to the screen.
    screen_pixmap_t screen_pix;
    if (screen_create_pixmap(&screen_pix, mScreenCtx) != 0) {
        return false;
    }

    // A combination of write and native usage is necessary to blit the pixmap to screen.
    usage = SCREEN_USAGE_WRITE | SCREEN_USAGE_NATIVE;
    if(screen_set_pixmap_property_iv(screen_pix, SCREEN_PROPERTY_USAGE, &usage) != 0) {
        return false;
    }

    // Set the width and height of the buffer to correspond to the one we specified in QML.
    mSize[0] = width;
    mSize[1] = height;
    if (screen_set_pixmap_property_iv(screen_pix, SCREEN_PROPERTY_BUFFER_SIZE, mSize) != 0) {
        return false;
    }

    // Create the pixmap buffer and get a reference to it for rendering in the doNoise function.
    if (screen_create_pixmap_buffer(screen_pix) != 0) {
        return false;
    }
    if (screen_get_pixmap_property_pv(screen_pix, SCREEN_PROPERTY_RENDER_BUFFERS,
            (void **) &mScreenPixelBuffer) != 0) {
        return false;
    }

    // We get the stride (the number of bytes between pixels on different rows), its used
    // later on when we perform the rendering to the pixmap buffer.
    if (screen_get_buffer_property_iv(mScreenPixelBuffer, SCREEN_PROPERTY_STRIDE, &mStride) != 0) {
        return false;
    }

    return true;
}