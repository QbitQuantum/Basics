unsigned char *BBWin8Game::LoadAudioData( String path,int *length,int *channels,int *format,int *hertz ){

	String url=PathToFilePath( path );
	
	DXASS( MFStartup( MF_VERSION ) );
	
	IMFAttributes *attrs;
	DXASS( MFCreateAttributes( &attrs,1 ) );
	DXASS( attrs->SetUINT32( MF_LOW_LATENCY,TRUE ) );
	
	IMFSourceReader *reader;
	DXASS( MFCreateSourceReaderFromURL( url.ToCString<wchar_t>(),attrs,&reader ) );
	
	attrs->Release();

	IMFMediaType *mediaType;
	DXASS( MFCreateMediaType( &mediaType ) );
	DXASS( mediaType->SetGUID( MF_MT_MAJOR_TYPE,MFMediaType_Audio ) );
	DXASS( mediaType->SetGUID( MF_MT_SUBTYPE,MFAudioFormat_PCM ) );

	DXASS( reader->SetCurrentMediaType( MF_SOURCE_READER_FIRST_AUDIO_STREAM,0,mediaType ) );
    
	mediaType->Release();

	IMFMediaType *outputMediaType;
	DXASS( reader->GetCurrentMediaType( MF_SOURCE_READER_FIRST_AUDIO_STREAM,&outputMediaType ) );
	
	WAVEFORMATEX *wformat;
	uint32 formatByteCount=0;
	DXASS( MFCreateWaveFormatExFromMFMediaType( outputMediaType,&wformat,&formatByteCount ) );

	*channels=wformat->nChannels;
	*format=wformat->wBitsPerSample/8;
	*hertz=wformat->nSamplesPerSec;

	CoTaskMemFree( wformat );
    
	outputMediaType->Release();
/*    
	PROPVARIANT var;
	DXASS( reader->GetPresentationAttribute( MF_SOURCE_READER_MEDIASOURCE,MF_PD_DURATION,&var ) );
	LONGLONG duration=var.uhVal.QuadPart;
	float64 durationInSeconds=(duration / (float64)(10000 * 1000));
	m_maxStreamLengthInBytes=(uint32)( durationInSeconds * m_waveFormat.nAvgBytesPerSec );
*/
	std::vector<unsigned char*> bufs;
	std::vector<uint32> lens;
	uint32 len=0;
    
	for( ;; ){
		uint32 flags=0;
		IMFSample *sample;
		DXASS( reader->ReadSample( MF_SOURCE_READER_FIRST_AUDIO_STREAM,0,0,reinterpret_cast<DWORD*>(&flags),0,&sample ) );
		
		if( flags & MF_SOURCE_READERF_ENDOFSTREAM ){
			break;
		}
		if( sample==0 ){ 
			abort();
		}
		
		IMFMediaBuffer *mediaBuffer;
		DXASS( sample->ConvertToContiguousBuffer( &mediaBuffer ) );

		uint8 *audioData=0;
		uint32 sampleBufferLength=0;
		DXASS( mediaBuffer->Lock( &audioData,0,reinterpret_cast<DWORD*>( &sampleBufferLength ) ) );
		
		unsigned char *buf=(unsigned char*)malloc( sampleBufferLength );
		memcpy( buf,audioData,sampleBufferLength );
		
		bufs.push_back( buf );
		lens.push_back( sampleBufferLength );
		len+=sampleBufferLength;
		
		DXASS( mediaBuffer->Unlock() );
		mediaBuffer->Release();
		
		sample->Release();
	}
	
	reader->Release();
	
	*length=len/(*channels * *format);

	unsigned char *data=(unsigned char*)malloc( len );
	unsigned char *p=data;
	
	for( int i=0;i<bufs.size();++i ){
		memcpy( p,bufs[i],lens[i] );
		free( bufs[i] );
		p+=lens[i];
	}
	
	gc_force_sweep=true;
	
	return data;
}	