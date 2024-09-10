long CRawFile::Tell( void ) const
{
#ifdef _WIN32
    LARGE_INTEGER posToMoveTo;
    posToMoveTo.LowPart = 0;
    posToMoveTo.HighPart = 0;

    LARGE_INTEGER currentPos;

    BOOL success = SetFilePointerEx( this->m_file, posToMoveTo, &currentPos, FILE_CURRENT );

    if ( success == FALSE )
        return -1;

    return (long)( currentPos.LowPart );
#elif defined(__linux__)
    return ftell( m_file );
#else
    return -1;
#endif //OS DEPENDANT CODE
}