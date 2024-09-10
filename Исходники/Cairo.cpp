void Context::appendPath( const cinder::Path2d &path )
{
	size_t point = 0;
	if( path.empty() )
		return;
	moveTo( path.getPoint( point++ ) );
	for( size_t seg = 0; seg < path.getNumSegments(); ++seg ) {
		switch( path.getSegmentType( seg ) ) {
			case Path2d::LINETO:
				lineTo( path.getPoint( point++ ) );
			break;
			case Path2d::QUADTO: {
				const Vec2f &spl0( path.getPoint( point - 1 ) ); const Vec2f &spl1( path.getPoint( point + 0 ) ); const Vec2f &spl2( path.getPoint( point + 1 ) );
				curveTo( spl0 + (spl1 - spl0) / 3.0f * 2.0f, spl1 + (spl2 - spl1) / 3.0f, spl2 );
				point += 2;
			}
			break;
			case Path2d::CUBICTO:
				curveTo( path.getPoint( point ), path.getPoint( point + 1 ), path.getPoint( point + 2 ) );
				point += 3;
			break;
			case Path2d::CLOSE:
				closePath();
			break;
		}
	}
}