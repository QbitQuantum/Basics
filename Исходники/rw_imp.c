void SWimp_SetHWGamma()
{
	unsigned short gamma[3][256];
	int i;

	for( i= 0; i< 256; i++ )
	{
		gamma[0][i]=
		gamma[1][i]=
		gamma[2][i]= sw_state.gammatable[i]<<8;
	}

	if( SetDeviceGammaRamp( sww_state.hDC, gamma ) == FALSE )
		printf( "hw gamma change error!\n" );
}