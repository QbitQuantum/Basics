// see bsa.h
bool BSA::open()
{
	QMutexLocker lock( & bsaMutex );
	
	try
	{
		if ( ! bsa.open( QIODevice::ReadOnly ) )
			throw QString( "file open" );
		
		quint32 magic, version;
		
		bsa.read( (char*) &magic, sizeof( magic ) );
		
		if ( magic == OB_BSAHEADER_FILEID )
		{
			bsa.read( (char*) &version, sizeof( version ) );
			
			if ( version != OB_BSAHEADER_VERSION && version != F3_BSAHEADER_VERSION )
				throw QString( "file version" );
			
			OBBSAHeader header;
			
			if ( bsa.read( (char *) & header, sizeof( header ) ) != sizeof( header ) )
				throw QString( "header size" );
			
			//qWarning() << bsaName << header;
			
			if ( ( header.ArchiveFlags & OB_BSAARCHIVE_PATHNAMES ) == 0 || ( header.ArchiveFlags & OB_BSAARCHIVE_FILENAMES ) == 0 )
				throw QString( "header flags" );
			
			compressToggle = header.ArchiveFlags & OB_BSAARCHIVE_COMPRESSFILES;
			
			if (version == F3_BSAHEADER_VERSION) {
				namePrefix = header.ArchiveFlags & F3_BSAARCHIVE_PREFIXFULLFILENAMES;
			} else {
				namePrefix = false;
			}
			
			if ( ! bsa.seek( header.FolderRecordOffset + header.FolderNameLength + header.FolderCount * ( 1 + sizeof( OBBSAFolderInfo ) ) + header.FileCount * sizeof( OBBSAFileInfo ) ) )
				throw QString( "file name seek" );
			
			QByteArray fileNames( header.FileNameLength, char(0) );
			if ( bsa.read( fileNames.data(), header.FileNameLength ) != header.FileNameLength )
				throw QString( "file name read" );
			quint32 fileNameIndex = 0;
			
			// qDebug() << file.pos() - header.FileNameLength << fileNames;
			
			if ( ! bsa.seek( header.FolderRecordOffset ) )
				throw QString( "folder info seek" );
			
			QVector<OBBSAFolderInfo> folderInfos( header.FolderCount );
			if ( bsa.read( (char *) folderInfos.data(), header.FolderCount * sizeof( OBBSAFolderInfo ) ) != header.FolderCount * sizeof( OBBSAFolderInfo ) )
				throw QString( "folder info read" );
			
			quint32 totalFileCount = 0;
			
			foreach ( OBBSAFolderInfo folderInfo, folderInfos )
			{
				// useless?
				/*
				qDebug() << __LINE__ << "position" << bsa.pos() << "offset" << folderInfo.offset;
				if ( folderInfo.offset < header.FileNameLength || ! bsa.seek( folderInfo.offset - header.FileNameLength ) )
					throw QString( "folder content seek" );
				*/
				
				
				QString folderName;
				if ( ! BSAReadSizedString( bsa, folderName ) || folderName.isEmpty() )
				{
					//qDebug() << "folderName" << folderName;
					throw QString( "folder name read" );
				}
				
				// qDebug() << folderName;
				
				BSAFolder * folder = insertFolder( folderName );
				
				quint32 fcnt = folderInfo.fileCount;
				totalFileCount += fcnt;
				QVector<OBBSAFileInfo> fileInfos( fcnt );
				if ( bsa.read( (char *) fileInfos.data(), fcnt * sizeof( OBBSAFileInfo ) ) != fcnt * sizeof( OBBSAFileInfo ) )
					throw QString( "file info read" );
				
				foreach ( OBBSAFileInfo fileInfo, fileInfos )
				{
					if ( fileNameIndex >= header.FileNameLength )
						throw QString( "file name size" );
					
					QString fileName = ( fileNames.data() + fileNameIndex );
					fileNameIndex += fileName.length() + 1;
					
					insertFile( folder, fileName, fileInfo.sizeFlags, fileInfo.offset );
				}
			}
			
			if ( totalFileCount != header.FileCount )
				throw QString( "file count" );
		}