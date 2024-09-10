// Need a non-virtual in destructor.
bool QWindowsClipboard::ownsClipboard() const
{
    return m_data && OleIsCurrentClipboard(m_data) == S_OK;
}