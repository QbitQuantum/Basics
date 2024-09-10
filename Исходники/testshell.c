void testShell()
{
	int fd, i, byte ;
	const char *microKeyer = "/dev/cu.usbserial-M2Q5BDJC" ;
	unsigned char split[] = { 0x0, 0x0, 0x0, 0x1, 0x1 } ;
	unsigned char vfoData[] = { 0x0, 0x0, 0x0, 0x3, 0x10 } ;
	
	fd = openPort( microKeyer ) ;
	if ( fd < 0 ) {
		printf( "cannot open microKeyer %s\n", microKeyer ) ;
		return ;
	}
	
	setRadio1Params( fd, 4800, 2, 8 ) ;			//  set radio baud rate
	sleep( 1 ) ;
	writeRadioBuffer( fd, 0, split, 5 ) ;		//  set split mode
	sleep( 1 ) ;
	writeRadioBuffer( fd, 0, vfoData, 5 ) ;		//  get VFO A and B data (should get 32 bytes back)
	
	//  read from Radio 1 until timed out
	for ( i = 0; i < 64; i++ ) {
		byte = getRadio( fd, 0 ) ;
		if ( byte < 0 ) break ;
		printf( "read byte %2d: 0x%02x\n", i, byte ) ;
	}
	
	close( fd ) ;
}