/*
** GLimp_SetGamma
**
** This routine should only be called if glConfig.deviceSupportsGamma is TRUE
*/
void GLimp_SetGamma( unsigned char red[256], unsigned char green[256], unsigned char blue[256] ) {
	unsigned short table[3][256];
	int		i, j;
	int		ret;
	OSVERSIONINFO	vinfo;

	if ( !glConfig.deviceSupportsGamma || r_gammamethod->integer != GAMMA_HARDWARE || !glw_state.hDC ) {
		return;
	}

	for ( i = 0; i < 256; i++ ) {
		table[0][i] = ( ( ( unsigned short ) red[i] ) << 8 ) | red[i];
		table[1][i] = ( ( ( unsigned short ) green[i] ) << 8 ) | green[i];
		table[2][i] = ( ( ( unsigned short ) blue[i] ) << 8 ) | blue[i];
	}

	// Win2K puts this odd restriction on gamma ramps...
	// https://github.com/JACoders/OpenJK/commit/43322f7f25dfce966bdbed7376c698cddf796284
	vinfo.dwOSVersionInfoSize = sizeof(vinfo);
	GetVersionEx( &vinfo );
	if ( vinfo.dwMajorVersion >= 5 && vinfo.dwPlatformId == VER_PLATFORM_WIN32_NT ) {
		Com_DPrintf( "performing W2K gamma clamp.\n" );
		for ( j = 0 ; j < 3 ; j++ ) {
			for ( i = 0 ; i < 128 ; i++ ) {
				if ( table[j][i] > ( (128+i) << 8 ) ) {
					table[j][i] = (128+i) << 8;
				}
			}
			if ( table[j][127] > 254<<8 ) {
				table[j][127] = 254<<8;
			}
		}
	} else {
		Com_DPrintf( "skipping gamma clamp.\n" );
	}

	// enforce constantly increasing
	for ( j = 0 ; j < 3 ; j++ ) {
		for ( i = 1 ; i < 256 ; i++ ) {
			if ( table[j][i] < table[j][i-1] ) {
				table[j][i] = table[j][i-1];
			}
		}
	}

	ret = SetDeviceGammaRamp( glw_state.hDC, table );
	if ( !ret ) {
		Com_Printf( "SetDeviceGammaRamp failed.\n" );
	}
}