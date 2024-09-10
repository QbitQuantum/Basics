Error FramebufferGL::blit(ContextImpl *context,
                          const gl::Rectangle &sourceArea,
                          const gl::Rectangle &destArea,
                          GLbitfield mask,
                          GLenum filter)
{
    const Framebuffer *sourceFramebuffer     = context->getGLState().getReadFramebuffer();
    const Framebuffer *destFramebuffer       = context->getGLState().getDrawFramebuffer();

    const FramebufferAttachment *colorReadAttachment = sourceFramebuffer->getReadColorbuffer();
    GLsizei readAttachmentSamples                    = colorReadAttachment->getSamples();

    bool needManualColorBlit = false;

    // TODO(cwallez) when the filter is LINEAR and both source and destination are SRGB, we
    // could avoid doing a manual blit.

    // Prior to OpenGL 4.4 BlitFramebuffer (section 18.3.1 of GL 4.3 core profile) reads:
    //      When values are taken from the read buffer, no linearization is performed, even
    //      if the format of the buffer is SRGB.
    // Starting from OpenGL 4.4 (section 18.3.1) it reads:
    //      When values are taken from the read buffer, if FRAMEBUFFER_SRGB is enabled and the
    //      value of FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING for the framebuffer attachment
    //      corresponding to the read buffer is SRGB, the red, green, and blue components are
    //      converted from the non-linear sRGB color space according [...].
    {
        bool sourceSRGB = colorReadAttachment != nullptr &&
                          colorReadAttachment->getColorEncoding() == GL_SRGB;
        needManualColorBlit =
            needManualColorBlit || (sourceSRGB && mFunctions->isAtMostGL(gl::Version(4, 3)));
    }

    // Prior to OpenGL 4.2 BlitFramebuffer (section 4.3.2 of GL 4.1 core profile) reads:
    //      Blit operations bypass the fragment pipeline. The only fragment operations which
    //      affect a blit are the pixel ownership test and scissor test.
    // Starting from OpenGL 4.2 (section 4.3.2) it reads:
    //      When values are written to the draw buffers, blit operations bypass the fragment
    //      pipeline. The only fragment operations which affect a blit are the pixel ownership
    //      test,  the scissor test and sRGB conversion.
    if (!needManualColorBlit)
    {
        bool destSRGB = false;
        for (size_t i = 0; i < destFramebuffer->getDrawbufferStateCount(); ++i)
        {
            const FramebufferAttachment *attachment = destFramebuffer->getDrawBuffer(i);
            if (attachment && attachment->getColorEncoding() == GL_SRGB)
            {
                destSRGB = true;
                break;
            }
        }

        needManualColorBlit =
            needManualColorBlit || (destSRGB && mFunctions->isAtMostGL(gl::Version(4, 1)));
    }

    // Enable FRAMEBUFFER_SRGB if needed
    mStateManager->setFramebufferSRGBEnabledForFramebuffer(true, this);

    GLenum blitMask = mask;
    if (needManualColorBlit && (mask & GL_COLOR_BUFFER_BIT) && readAttachmentSamples <= 1)
    {
        ANGLE_TRY(mBlitter->blitColorBufferWithShader(sourceFramebuffer, destFramebuffer,
                                                      sourceArea, destArea, filter));
        blitMask &= ~GL_COLOR_BUFFER_BIT;
    }

    if (blitMask == 0)
    {
        return gl::NoError();
    }

    const FramebufferGL *sourceFramebufferGL = GetImplAs<FramebufferGL>(sourceFramebuffer);
    mStateManager->bindFramebuffer(GL_READ_FRAMEBUFFER, sourceFramebufferGL->getFramebufferID());
    mStateManager->bindFramebuffer(GL_DRAW_FRAMEBUFFER, mFramebufferID);

    mFunctions->blitFramebuffer(sourceArea.x, sourceArea.y, sourceArea.x1(), sourceArea.y1(),
                                destArea.x, destArea.y, destArea.x1(), destArea.y1(), blitMask,
                                filter);

    return gl::NoError();
}