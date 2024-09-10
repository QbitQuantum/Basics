void TarListingThread::processDir( const KTarDirectory *tardir, const TQString & root )
{
	TQStringList list = tardir->entries();
	
	TQStringList::const_iterator itEnd = list.constEnd();

	for ( TQStringList::const_iterator it = list.constBegin(); it != itEnd; ++it )
	{
		const KTarEntry* tarEntry = tardir->entry((*it));
		if (!tarEntry)
			continue;

		TQStringList col_list;
		TQString name;
		if (root.isEmpty() || root.isNull())
			name = tarEntry->name();
		else
			name = root + tarEntry->name();
		if ( !tarEntry->isFile() )
			name += '/';
		col_list.append( name );
		TQString perms = makeAccessString(tarEntry->permissions());
		if (!tarEntry->isFile())
			perms = "d" + perms;
		else if (!tarEntry->symlink().isEmpty())
			perms = "l" + perms;
		else
			perms = "-" + perms;
		col_list.append(perms);
		col_list.append( tarEntry->user() );
		col_list.append( tarEntry->group() );
		TQString strSize = "0";
		if (tarEntry->isFile())
		{
			strSize.sprintf("%d", ((KTarFile *)tarEntry)->size());
		}
		col_list.append(strSize);
		TQString timestamp = tarEntry->datetime().toString(Qt::ISODate);
		col_list.append(timestamp);
		col_list.append(tarEntry->symlink());
		
		ListingEvent *ev = new ListingEvent( col_list );
		tqApp->postEvent( m_parent, ev );

		// if it's a directory, process it.
		// remember that name is root + / + the name of the directory
		if ( tarEntry->isDirectory() )
		{
			processDir( static_cast<const KTarDirectory *>( tarEntry ), name );
		}
	}
}