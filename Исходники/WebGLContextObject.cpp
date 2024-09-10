void WebGLContextObject::detachContext()
{
    detach();
    if (m_context) {
        deleteObject(m_context->graphicsContext3D());
        m_context->removeContextObject(this);
        m_context = 0;
    }
}