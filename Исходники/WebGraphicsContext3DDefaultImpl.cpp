bool WebGraphicsContext3DDefaultImpl::readBackFramebuffer(unsigned char* pixels, size_t bufferSize)
{
    if (bufferSize != static_cast<size_t>(4 * width() * height()))
        return false;

    makeContextCurrent();

#ifdef RENDER_TO_DEBUGGING_WINDOW
    SwapBuffers(m_canvasDC);
#else
    // Earlier versions of this code used the GPU to flip the
    // framebuffer vertically before reading it back for compositing
    // via software. This code was quite complicated, used a lot of
    // GPU memory, and didn't provide an obvious speedup. Since this
    // vertical flip is only a temporary solution anyway until Chrome
    // is fully GPU composited, it wasn't worth the complexity.

    bool mustRestoreFBO;
    if (m_attributes.antialias) {
        glBindFramebufferEXT(GL_READ_FRAMEBUFFER_EXT, m_multisampleFBO);
        glBindFramebufferEXT(GL_DRAW_FRAMEBUFFER_EXT, m_fbo);
        glBlitFramebufferEXT(0, 0, m_cachedWidth, m_cachedHeight, 0, 0, m_cachedWidth, m_cachedHeight, GL_COLOR_BUFFER_BIT, GL_LINEAR);
        glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_fbo);
        mustRestoreFBO = true;
    } else {
        if (m_boundFBO != m_fbo) {
            mustRestoreFBO = true;
            glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_fbo);
        }
    }

    GLint packAlignment = 4;
    bool mustRestorePackAlignment = false;
    glGetIntegerv(GL_PACK_ALIGNMENT, &packAlignment);
    if (packAlignment > 4) {
        glPixelStorei(GL_PACK_ALIGNMENT, 4);
        mustRestorePackAlignment = true;
    }

#if PLATFORM(SKIA)
    glReadPixels(0, 0, m_cachedWidth, m_cachedHeight, GL_BGRA, GL_UNSIGNED_BYTE, pixels);
#elif PLATFORM(CG)
    glReadPixels(0, 0, m_cachedWidth, m_cachedHeight, GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV, pixels);
#else
#error Must port to your platform
#endif

    if (mustRestorePackAlignment)
        glPixelStorei(GL_PACK_ALIGNMENT, packAlignment);

    if (mustRestoreFBO)
        glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_boundFBO);

#ifdef FLIP_FRAMEBUFFER_VERTICALLY
    if (pixels)
        flipVertically(pixels, m_cachedWidth, m_cachedHeight);
#endif

#endif // RENDER_TO_DEBUGGING_WINDOW
    return true;
}