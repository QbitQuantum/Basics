// static
QRgb QImageUtils::vector4fToQRgba( const Vector4f& v )
{
	int r = ColorUtils::floatToInt( v.x() );
	int g = ColorUtils::floatToInt( v.y() );
	int b = ColorUtils::floatToInt( v.z() );
	int a = ColorUtils::floatToInt( v.w() );

	return qRgba( r, g, b, a );
}