CUnitDiskObjectPtr
CDiskObjectBuilder::CreateDiskObject(const CDeviceInfoPtr deviceInfo, unsigned _int8 nSlotNumber)
{
	// For now, only management of disks connected by LAN is implemented.
	CUnitDiskObjectPtr diskObject;
//	TARGET_DATA	targetData;
	NDASCOMM_UNIT_DEVICE_INFO UnitDeviceInfo;

	CLanSession session( deviceInfo->GetDeviceID()->Node, nSlotNumber );

	session.Connect();

    session.GetTargetData( &UnitDeviceInfo );

	if ( UnitDeviceInfo.MediaType != MEDIA_TYPE_BLOCK_DEVICE )
	{
		// Types other than HDD is not supported
		// TODO : Throw exception
		NDAS_THROW_EXCEPTION( 
			CDiskException, 
			CDiskException::ERROR_UNSUPPORTED_DISK_TYPE 
			);
	}

	CDiskInfoSectorPtr dibv2(new CDIBV2Sector(&UnitDeviceInfo));
	CDiskInfoSectorPtr dib(new CDIBSector(&UnitDeviceInfo));
	
	// First get DIB_V2
	dibv2->ReadAccept( &session );

	if ( dibv2->IsValidSignature() )
	{
		diskObject = CUnitDiskObjectPtr( 
						new CLanUnitDiskObject( 
								deviceInfo,
								nSlotNumber,
								new CHDDDiskInfoHandler( dibv2 )
								)
						);
	}
	else
	{
		dib->ReadAccept( &session );
		if ( dib->IsValidSignature() && dib->IsValid() )
		{
			diskObject = CUnitDiskObjectPtr(
							new CLanUnitDiskObject(
								deviceInfo,
								nSlotNumber,
								new CHDDDiskInfoHandler( dib )
								)
							);
		}
		else
		{
			// No DIB information : single disk
			CDiskInfoSectorPtr newDIB = 
				CDiskInfoSectorPtr( new CDIBV2Sector(&UnitDeviceInfo) );
			diskObject = CUnitDiskObjectPtr(
							new CLanUnitDiskObject(
								deviceInfo,
								nSlotNumber,
								new CHDDDiskInfoHandler( newDIB )
								)
							);
		}
	}
	session.Disconnect();
	return diskObject;
}