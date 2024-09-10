void 
FileMonitor::initialiseDosNameMap()
{
	UCHAR buffer[1024];
	PFILTER_VOLUME_BASIC_INFORMATION volumeBuffer = (PFILTER_VOLUME_BASIC_INFORMATION)buffer;
	HANDLE volumeIterator = INVALID_HANDLE_VALUE;
	ULONG volumeBytesReturned;
	WCHAR driveLetter[15];

	HRESULT hResult = FilterVolumeFindFirst( FilterVolumeBasicInformation,
										 volumeBuffer,
										 sizeof(buffer)-sizeof(WCHAR),   //save space to null terminate name
										 &volumeBytesReturned,
										 &volumeIterator );
	if (volumeIterator != INVALID_HANDLE_VALUE) {
		do {
			assert((FIELD_OFFSET(FILTER_VOLUME_BASIC_INFORMATION,FilterVolumeName) + volumeBuffer->FilterVolumeNameLength) <= (sizeof(buffer)-sizeof(WCHAR)));
			__analysis_assume((FIELD_OFFSET(FILTER_VOLUME_BASIC_INFORMATION,FilterVolumeName) + volumeBuffer->FilterVolumeNameLength) <= (sizeof(buffer)-sizeof(WCHAR)));
			volumeBuffer->FilterVolumeName[volumeBuffer->FilterVolumeNameLength/sizeof( WCHAR )] = UNICODE_NULL;
				
			if(SUCCEEDED( FilterGetDosName(volumeBuffer->FilterVolumeName,
				driveLetter,
				sizeof(driveLetter)/sizeof(WCHAR) )
				))
			{
				wstring dLetter = driveLetter;
				dosNameMap.insert(DosPair(volumeBuffer->FilterVolumeName, dLetter));
			}
		} while (SUCCEEDED( hResult = FilterVolumeFindNext( volumeIterator,
															FilterVolumeBasicInformation,
															volumeBuffer,
															sizeof(buffer)-sizeof(WCHAR),    //save space to null terminate name
															&volumeBytesReturned ) ));
	}

	if (INVALID_HANDLE_VALUE != volumeIterator) {
		FilterVolumeFindClose( volumeIterator );
	}
}