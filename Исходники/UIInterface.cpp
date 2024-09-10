int UIInterface::HandleEvents(void *arg)
{
    UIInterface *uii = static_cast<UIInterface *>(arg);

    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        uii->handleEvent(&event);
    }

    if (uii->m_DoRefresh) {
        uii->hitRefresh();
        uii->m_DoRefresh = false;
    }

    if (uii->m_DoRefresh) {
        uii->hitRefresh();
        uii->m_DoRefresh = false;
    }

    if (ttfps % 300 == 0 && uii->isContextReady()) {
        uii->m_NidiumCtx->getNJS()->gc();
    }

    if (uii->m_CursorNeedsUpdate) {
        uii->setSystemCursor(uii->m_CurrentCursor);
        uii->m_CursorNeedsUpdate = false;
    }

    if (uii->isContextReady()) {
        uii->makeMainGLCurrent();
        uii->m_NidiumCtx->frame(true);
    }

    if (uii->getConsole()) {
        uii->getConsole()->flush();
    }

    if (uii->getFBO() != 0 && uii->m_NidiumCtx) {
#ifndef NIDIUM_OPENGLES2
        glReadBuffer(GL_COLOR_ATTACHMENT0);

        glReadPixels(0, 0, uii->getWidth(), uii->getHeight(), GL_RGBA,
                     GL_UNSIGNED_BYTE, uii->getFrameBufferData());
        uint8_t *pdata = uii->getFrameBufferData();

        uii->m_NidiumCtx->rendered(pdata, uii->getWidth(), uii->getHeight());
#endif
    } else {
        uii->makeMainGLCurrent();
        SDL_GL_SwapWindow(uii->m_Win);
    }

    ttfps++;
    return 8;
}