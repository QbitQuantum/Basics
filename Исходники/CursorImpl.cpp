void CursorImpl::release()
{
    if (m_cursor) {
        DestroyCursor(m_cursor);
        m_cursor = NULL;
    }
}