TSeparatorKit* ComponentHeliostatField::OpenHeliostatComponent( QString fileName )
{
	if ( fileName.isEmpty() ) return 0;

	SoInput componentInput;
	if ( !componentInput.openFile( fileName.toLatin1().constData() ) )
	{
        QMessageBox::warning( 0, QString( "Scene Graph Structure" ),
        		QString( "Cannot open file %1:\n." ).arg( fileName ) );
		return 0;
	}

	SoSeparator* componentSeparator = SoDB::readAll( &componentInput );
	componentInput.closeFile();

	if ( !componentSeparator )
	{
        QMessageBox::warning( 0, QString( "Scene Graph Structure" ),
        		QString( "Error reading file %1:\n%2." )
                             .arg( fileName ) );
		return 0;
	}

	TSeparatorKit* componentRoot = static_cast< TSeparatorKit* >( componentSeparator->getChild(0) );
	componentRoot->ref();


   return componentRoot;

}