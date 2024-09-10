static std::string show_waveout_devices( std::ostream & /*log*/ ) {
	std::ostringstream devices;
	devices << " waveout:" << std::endl;
	for ( UINT i = 0; i < waveOutGetNumDevs(); ++i ) {
		devices << "    " << i << ": ";
		WAVEOUTCAPSW caps;
		ZeroMemory( &caps, sizeof( caps ) );
		waveOutGetDevCapsW( i, &caps, sizeof( caps ) );
		devices << wstring_to_utf8( caps.szPname );
		devices << std::endl;
	}
	return devices.str();
}