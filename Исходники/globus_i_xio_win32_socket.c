static
void
globus_l_xio_win32_blocking_destroy(
    globus_l_xio_win32_blocking_info_t * blocking_info)
{
    GlobusXIOName(globus_l_xio_win32_blocking_destroy);
    
    GlobusXIOSystemDebugEnter();
    
    WSACloseEvent(blocking_info->event);
    globus_free(blocking_info);
    
    GlobusXIOSystemDebugExit();
}