QStringList QPCSC::drivers() const
{
#ifdef Q_OS_WIN
	HDEVINFO h = SetupDiGetClassDevs( 0, 0, 0, DIGCF_ALLCLASSES | DIGCF_PRESENT );
	if( !h )
		return QStringList();

	SP_DEVINFO_DATA info = { sizeof(SP_DEVINFO_DATA) };
	QStringList list;
	for( DWORD i = 0; SetupDiEnumDeviceInfo( h, i, &info ); i++ )
	{
		DWORD size = 0;
		WCHAR data[1024];

		SetupDiGetDeviceRegistryPropertyW( h, &info,
			SPDRP_CLASS, 0, LPBYTE(data), sizeof(data), &size );
		if( _wcsicmp( data, L"SmartCardReader" ) != 0 )
			continue;

		DWORD conf = 0;
		SetupDiGetDeviceRegistryPropertyW( h, &info,
			SPDRP_CONFIGFLAGS, 0, LPBYTE(&conf), sizeof(conf), &size );
		if( conf & CONFIGFLAG_DISABLED )
			continue;

		SetupDiGetDeviceRegistryPropertyW( h, &info,
			SPDRP_DEVICEDESC, 0, LPBYTE(data), sizeof(data), &size );
		QString name( (QChar*)data );

		SetupDiGetDeviceRegistryPropertyW( h, &info,
			SPDRP_HARDWAREID, 0, LPBYTE(data), sizeof(data), &size );

		list << QString( "%1 (%2)").arg( name, QString( (QChar*)data ) );
	}
	SetupDiDestroyDeviceInfoList( h );

	return list;
#else
	return readers();
#endif
}