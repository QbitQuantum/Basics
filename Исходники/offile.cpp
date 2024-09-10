void
OFFile::handle( OFOS::of_handle_t handle )
{
    close( );
    m_handle = handle;
#if defined(OFOPSYS_LINUX) || defined(OFOPSYS_SOLARIS) || defined(OFOPSYS_FREEBSD) || defined(OFOPSYS_DARWIN)
    struct stat buf;
    if ( fstat( m_handle, &buf ) == 0 )
        m_open = true;
#elif defined(OFOPSYS_WIN32)
    oflong hi;
    if ( GetHandleInformation( m_handle, &hi ) )
        m_open = true;
#else
#error Undefined platform
#endif
}