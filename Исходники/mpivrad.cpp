void VMPI_DistributeLightData()
{
	if ( !g_bUseMPI )
		return;

	if ( g_bMPIMaster )
	{
		const char *pVirtualFilename = "--plightdata--";
		
		CUtlBuffer lightFaceData;

		// write out the light data
		lightFaceData.EnsureCapacity( pdlightdata->Count() + (numfaces * (MAXLIGHTMAPS+sizeof(int))) );
		Q_memcpy( lightFaceData.PeekPut(), pdlightdata->Base(), pdlightdata->Count() );
		lightFaceData.SeekPut( CUtlBuffer::SEEK_HEAD, pdlightdata->Count() );

		// write out the relevant face info into the stream
		for ( int i = 0; i < numfaces; i++ )
		{
			for ( int j = 0; j < MAXLIGHTMAPS; j++ )
			{
				lightFaceData.PutChar(g_pFaces[i].styles[j]);
			}
			lightFaceData.PutInt(g_pFaces[i].lightofs);
		}
		VMPI_FileSystem_CreateVirtualFile( pVirtualFilename, lightFaceData.Base(), lightFaceData.TellMaxPut() );

		char cPacketID[2] = { VMPI_VRAD_PACKET_ID, VMPI_SUBPACKETID_PLIGHTDATA_RESULTS };
		VMPI_Send2Chunks( cPacketID, sizeof( cPacketID ), pVirtualFilename, strlen( pVirtualFilename ) + 1, VMPI_PERSISTENT );
	}
	else
	{
		VMPI_SetCurrentStage( "VMPI_DistributeLightData" );

		// Wait until we've received the filename from the master.
		while ( g_LightResultsFilename.Count() == 0 )
		{
			VMPI_DispatchNextMessage();
		}

		// Open 
		FileHandle_t fp = g_pFileSystem->Open( g_LightResultsFilename.Base(), "rb", VMPI_VIRTUAL_FILES_PATH_ID );
		if ( !fp )
			Error( "Can't open '%s' to read lighting info.", g_LightResultsFilename.Base() );

		int size = g_pFileSystem->Size( fp );
		int faceSize = (numfaces*(MAXLIGHTMAPS+sizeof(int)));

		if ( size > faceSize )
		{
			int lightSize = size - faceSize;
			CUtlBuffer faceData;
			pdlightdata->EnsureCount( lightSize );
			faceData.EnsureCapacity( faceSize );

			g_pFileSystem->Read( pdlightdata->Base(), lightSize, fp );
			g_pFileSystem->Read( faceData.Base(), faceSize, fp );
			g_pFileSystem->Close( fp );

			faceData.SeekPut( CUtlBuffer::SEEK_HEAD, faceSize );

			// write out the face data
			for ( int i = 0; i < numfaces; i++ )
			{
				for ( int j = 0; j < MAXLIGHTMAPS; j++ )
				{
					g_pFaces[i].styles[j] = faceData.GetChar();
				}
				g_pFaces[i].lightofs = faceData.GetInt();
			}
		}
	}
}