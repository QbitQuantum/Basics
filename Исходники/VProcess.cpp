void VProcess::_ReadProductVersion( VString& outVersion) const
{
#if VERSIONWIN
#ifndef XTOOLBOX_AS_STANDALONE
	DWORD size = ::GetFileVersionInfoSizeW( GetExecutableFilePath().GetPath().GetCPointer(), NULL);
	void *buffer = malloc( size);
	if ( (buffer != NULL) && GetFileVersionInfoW( GetExecutableFilePath().GetPath().GetCPointer(), NULL, size, buffer))
	{
		void *valueAdress;
		UINT valueSize;
		if (::VerQueryValueW( buffer, L"\\StringFileInfo\\040904B0\\ProductVersion", &valueAdress, &valueSize))
		{
			outVersion.FromBlock( valueAdress, (valueSize - 1) * sizeof( UniChar), VTC_UTF_16);
		}
	}
	if (buffer != NULL)
		free( buffer);
#endif
#elif VERSIONMAC
	// The constant for the "short version" property does not exist.
	CFStringRef cfProductVersion = (CFStringRef) CFBundleGetValueForInfoDictionaryKey( CFBundleGetMainBundle(), CFSTR ( "CFBundleShortVersionString" ) /*kCFBundleVersionKey*/);
	if (cfProductVersion != NULL)
	{
		outVersion.MAC_FromCFString( cfProductVersion);
	}

#elif VERSION_LINUX
    //jmo - We get the Linux product version with SetProductVersion() on VRIAServerApplication init
#endif
}