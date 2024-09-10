time_t EmacsFile::fio_modify_date()
{
    EmacsFileStat s;

    if( !s.stat( m_file ) )
        return 0;

    return s.data().st_mtime;
}