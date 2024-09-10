void QWindowsOleDropSource::clearCursors()
{
    if (!m_cursors.isEmpty()) {
        const ActionCursorMap::const_iterator cend = m_cursors.constEnd();
        for (ActionCursorMap::const_iterator it = m_cursors.constBegin(); it != cend; ++it)
            DestroyCursor(it.value());
        m_cursors.clear();
    }
}