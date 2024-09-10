void xInstaller::extAssign( AppEntry * app, QStringList slExt )
{
	toLog( "@ extAssign" );
	
	QStringList::Iterator it;
	
	QStringList slTypes;
	slTypes.clear();
	
	QFile file( MOD_MIME_TYPE );
	
    if ( !file.open( IO_ReadWrite ) )
		return;

	toLog( "Find exist type" );
	QTextStream stream( &file );
	QString line;
	while ( !stream.atEnd() ) 
	{
		line = stream.readLine(); // line of text excluding '\n'
		for ( int i=slExt.count()-1; i>=0; i-- ) 
		{
			it = slExt.at(i);
			if ( line.find( *it, line.find(" ") ) > 0 )
			{
				slTypes.append( line.left( line.find(" ") ) );
				slExt.remove( it );
			}
		}
	}
	
	toLog( "write ne types" );
	QString types;
	for ( it = slExt.begin(); it != slExt.end(); ++it ) 
	{
		types = "file/x-" + *it; 
		slTypes.append( types );
		stream << (types + " " + *it + "\n");
	}
	
	file.close();
	
	toLog( "write user mime" );
	ZConfig userMime ( MOD_USER_MIME );
	for ( it = slTypes.begin(); it != slTypes.end(); ++it ) 
	{
		userMime.writeEntry ( *it, "AppList", app->appId+";");
		userMime.writeEntry ( *it, "AppID", app->appId);
	}
	userMime.flush();
	
	toLog( "Send update mime" );
	QCopChannel::send("/AM/MimeRegistry", "update()");
}