//-----------------------------------------------------------------------------
// FIXME: assumes that we don't need to do gamma correction.
//-----------------------------------------------------------------------------
bool WriteToBuffer( unsigned char *pImageData, CUtlBuffer &buffer, int width, int height, 
					ImageFormat srcFormat, ImageFormat dstFormat )
{
	TGAHeader_t header;

	// Fix the dstFormat to match what actually is going to go into the file
	switch( dstFormat )
	{
	case IMAGE_FORMAT_RGB888:
		dstFormat = IMAGE_FORMAT_BGR888;
		break;
#if defined( _X360 )
	case IMAGE_FORMAT_LINEAR_RGB888:
		dstFormat = IMAGE_FORMAT_LINEAR_BGR888;
		break;
#endif
	case IMAGE_FORMAT_RGBA8888:
		dstFormat = IMAGE_FORMAT_BGRA8888;
		break;
	}

	header.id_length = 0; // comment length
	header.colormap_type = 0; // ???

	switch( dstFormat )
	{
	case IMAGE_FORMAT_BGR888:
#if defined( _X360 )
	case IMAGE_FORMAT_LINEAR_BGR888:
#endif
		header.image_type = 2; // 24/32 bit uncompressed TGA
		header.pixel_size = 24;
		break;
	case IMAGE_FORMAT_BGRA8888:
		header.image_type = 2; // 24/32 bit uncompressed TGA
		header.pixel_size = 32;
		break;
	case IMAGE_FORMAT_I8:
		header.image_type = 1; // 8 bit uncompressed TGA
		header.pixel_size = 8;
		break;
	default:
		return false;
		break;
	}

	header.colormap_index = 0;
	header.colormap_length = 0;
	header.colormap_size = 0;
	header.x_origin = 0;
	header.y_origin = 0;
	header.width = ( unsigned short )width;
	header.height = ( unsigned short )height;
	header.attributes = 0x20;	// Makes it so we don't have to vertically flip the image

	buffer.PutChar( header.id_length );
	buffer.PutChar( header.colormap_type );
	buffer.PutChar( header.image_type );
	fputLittleShort( header.colormap_index, buffer );
	fputLittleShort( header.colormap_length, buffer );
	buffer.PutChar( header.colormap_size );
	fputLittleShort( header.x_origin, buffer );
	fputLittleShort( header.y_origin, buffer );
	fputLittleShort( header.width, buffer );
	fputLittleShort( header.height, buffer );
	buffer.PutChar( header.pixel_size );
	buffer.PutChar( header.attributes );

	int nSizeInBytes = width * height * ImageLoader::SizeInBytes( dstFormat );
	buffer.EnsureCapacity( buffer.TellPut() + nSizeInBytes );
	unsigned char *pDst = (unsigned char*)buffer.PeekPut();

	if ( !ImageLoader::ConvertImageFormat( pImageData, srcFormat, pDst, dstFormat, width, height ) )
		return false;

	buffer.SeekPut( CUtlBuffer::SEEK_CURRENT, nSizeInBytes );
	return true;
}