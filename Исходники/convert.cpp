Imath::Box3d convert( const MBoundingBox &from )
{
	return Imath::Box3d( convert<V3d>( from.min() ), convert<V3d>( from.max() ) );
}