rnb_err_t
RNBSocket::Disconnect (bool save_errno)
{
#ifdef WITH_LOCKDOWN
    if (m_fd_from_lockdown)
    {
        m_fd_from_lockdown = false;
        m_fd = -1;
        lockdown_disconnect (m_ld_conn);
        return rnb_success;
    }
#endif
    return ClosePort (m_fd, save_errno);
}