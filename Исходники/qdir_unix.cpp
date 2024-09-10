QString QDir::currentDirPath()
{
    QString result;

    STATBUF st;
    if ( STAT( ".", &st ) == 0 ) {
	char currentName[PATH_MAX];
	if ( GETCWD( currentName, PATH_MAX ) != 0 )
	    result = QFile::decodeName(currentName);
#if defined(DEBUG)
	if ( result.isNull() )
	    qWarning( "QDir::currentDirPath: getcwd() failed" );
#endif
    } else {
#if defined(DEBUG)
	qWarning( "QDir::currentDirPath: stat(\".\") failed" );
#endif
    }
    slashify( result );
    return result;
}