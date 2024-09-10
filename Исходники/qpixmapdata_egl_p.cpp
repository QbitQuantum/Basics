bool QEglGLPixmapData::isValid() const
{
    TRACE();
    return w > 0 && h > 0;    
}