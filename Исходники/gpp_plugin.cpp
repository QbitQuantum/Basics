// args: bitmap pointer, mode, unknown, unknown, unknown
int __stdcall GppDraw( unsigned char* pImg, int mode, int unknown1, int unknown2, int unknown3 )
{
	switch( mode )
	{
	case 0:
		image.setPixel( 1, 1, !image.getPixel( 1, 1 ) );
		image.copyTo( pImg, 0 );
		break;
	case 1:
		image.setPixel( 2, 2, !image.getPixel( 2, 2 ) );
		image.copyTo( pImg, 1 );
		break;
	case 2:
		image.setPixel( 3, 3, !image.getPixel( 3, 3 ) );
		image.copyTo( pImg, 2 );
		break;
	}

	return 0;
}