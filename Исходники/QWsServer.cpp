QString QWsServer::computeAcceptV0( QString key1, QString key2, QString key3 )
{
	QString numStr1;
	QString numStr2;

	QChar carac;
	for ( int i=0 ; i<key1.size() ; i++ )
	{
		carac = key1[ i ];
		if ( carac.isDigit() )
			numStr1.append( carac );
	}
	for ( int i=0 ; i<key2.size() ; i++ )
	{
	    carac = key2[ i ];
		if ( carac.isDigit() )
			numStr2.append( carac );
	}

	quint32 num1 = numStr1.toUInt();
	quint32 num2 = numStr2.toUInt();

	int numSpaces1 = key1.count( ' ' );
	int numSpaces2 = key2.count( ' ' );

	num1 /= numSpaces1;
	num2 /= numSpaces2;

	QString concat = serializeInt( num1 ) + serializeInt( num2 ) + key3;

    QByteArray md5 = QCryptographicHash::hash( concat.toLatin1(), QCryptographicHash::Md5 );
  
	return QString( md5 );
}