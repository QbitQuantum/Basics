void WebGLObject::detachContext()
{
    m_attachmentCount = 0; // Make sure OpenGL resource is deleted.
    if (m_context) {
        deleteObject();
        m_context->removeObject(this);
        m_context = 0;
    }
}