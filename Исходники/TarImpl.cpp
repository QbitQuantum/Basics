bool TarImpl::extractFile( const QString& fName, const QDir& dir, const QString& newName, QString* )
{
    QString outFileName;
    if ( !ArchiveImpl::extractFile( fName, dir, newName, &outFileName ) )
    {
        return false;
    }

    // set the file modifiaction time based on header info
    setFileTime( outFileName, tarDevice()->headerInfo().time() );

    return true;
}