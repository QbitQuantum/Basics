void QSGVideoMaterial_YUV::bind()
{
    QOpenGLFunctions *functions = QOpenGLContext::currentContext()->functions();
    QMutexLocker lock(&m_frameMutex);
    if (m_frame.isValid()) {
        if (m_frame.map(QAbstractVideoBuffer::ReadOnly)) {
            int fw = m_frame.width();
            int fh = m_frame.height();

            // Frame has changed size, recreate textures...
            if (m_textureSize != m_frame.size()) {
                if (!m_textureSize.isEmpty())
                    functions->glDeleteTextures(m_planeCount, m_textureIds);
                functions->glGenTextures(m_planeCount, m_textureIds);
                m_textureSize = m_frame.size();
            }

            GLint previousAlignment;
            functions->glGetIntegerv(GL_UNPACK_ALIGNMENT, &previousAlignment);
            functions->glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

            if (m_format.pixelFormat() == QVideoFrame::Format_NV12
                    || m_format.pixelFormat() == QVideoFrame::Format_NV21) {
                const int y = 0;
                const int uv = 1;

                m_planeWidth[0] = m_planeWidth[1] = qreal(fw) / m_frame.bytesPerLine(y);

                functions->glActiveTexture(GL_TEXTURE1);
                bindTexture(m_textureIds[1], m_frame.bytesPerLine(uv) / 2, fh / 2, m_frame.bits(uv), GL_LUMINANCE_ALPHA);
                functions->glActiveTexture(GL_TEXTURE0); // Finish with 0 as default texture unit
                bindTexture(m_textureIds[0], m_frame.bytesPerLine(y), fh, m_frame.bits(y), GL_LUMINANCE);

            } else { // YUV420P || YV12
                const int y = 0;
                const int u = m_frame.pixelFormat() == QVideoFrame::Format_YUV420P ? 1 : 2;
                const int v = m_frame.pixelFormat() == QVideoFrame::Format_YUV420P ? 2 : 1;

                m_planeWidth[0] = qreal(fw) / m_frame.bytesPerLine(y);
                m_planeWidth[1] = m_planeWidth[2] = qreal(fw) / (2 * m_frame.bytesPerLine(u));

                functions->glActiveTexture(GL_TEXTURE1);
                bindTexture(m_textureIds[1], m_frame.bytesPerLine(u), fh / 2, m_frame.bits(u), GL_LUMINANCE);
                functions->glActiveTexture(GL_TEXTURE2);
                bindTexture(m_textureIds[2], m_frame.bytesPerLine(v), fh / 2, m_frame.bits(v), GL_LUMINANCE);
                functions->glActiveTexture(GL_TEXTURE0); // Finish with 0 as default texture unit
                bindTexture(m_textureIds[0], m_frame.bytesPerLine(y), fh, m_frame.bits(y), GL_LUMINANCE);
            }

            functions->glPixelStorei(GL_UNPACK_ALIGNMENT, previousAlignment);
            m_frame.unmap();
        }

        m_frame = QVideoFrame();
    } else {
        // Go backwards to finish with GL_TEXTURE0
        for (int i = m_planeCount - 1; i >= 0; --i) {
            functions->glActiveTexture(GL_TEXTURE0 + i);
            functions->glBindTexture(GL_TEXTURE_2D, m_textureIds[i]);
        }
    }
}