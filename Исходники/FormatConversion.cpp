// static
void FormatConversion::image3ubToImage4f( const Image3ub& source, Image4f& destination, bool flipUpDown, float fillAlpha )
{
	int width = source.width();
	int height = source.height();

	for( int y = 0; y < height; ++y )
	{
		int yy = y;
		if( flipUpDown )
		{
			yy = height - y - 1;
		}

		for( int x = 0; x < width; ++x )
		{
			Vector3i input = source.pixel( x, y );
			Vector3f output = ColorUtils::intToFloat( input );			
			destination.setPixel( x, yy, Vector4f( output, fillAlpha ) );
		}
	}
}