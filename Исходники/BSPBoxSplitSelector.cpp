bool BSPBoxSplitSelector::getSplitPlane( const util::Vector<BSPPolygon*>& polys,
	ProgressIndicator* progress, Vector4* splitPlane ) const
{
	assert( polys.size() > 0 );

	double workUnit = polys.size();

	if ( progress )
		progress->addProgress( workUnit );

	OBBoxBuilder builder;
	while ( builder.nextPass() )
	{
		for ( int i = 0 ; i < polys.size() ; ++i )
		{
			const BSPPolygon& poly = *polys[i];
			for ( int k = 0 ; k < poly.vertices() ; ++k )
				builder.addPoints( &poly.getVertex(k), 1 );
		}
	}

	OBBox box = builder.box();
	Vector3 center = box.translation();
	Vector3 normal = box.rotation().getColumn(0);
	*splitPlane = Vector4( normal.x, normal.y, normal.z, -center.dot(normal) );
	return Math::abs(normal.length()-1.f) < 1e-3f && splitPlane->finite();
}