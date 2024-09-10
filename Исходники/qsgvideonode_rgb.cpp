 bool needsSwizzling() const {
     return m_format.pixelFormat() == QVideoFrame::Format_RGB32
             || m_format.pixelFormat() == QVideoFrame::Format_ARGB32;
 }