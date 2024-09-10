void Branch::addArc( const Vec2f &p1 )
{
	if ( mPath.empty() )
	{
		mPath.moveTo( p1 );
		return;
	}

	size_t segmentNum = mPath.getNumSegments();
	if ( segmentNum == 0 )
	{
		mPath.lineTo( p1 );
		return;
	}

	// last point
	Vec2f p0 = mPath.getSegmentPosition( segmentNum - 1, 1.f );
	// same point as the last one -> skip
	if ( p0.distanceSquared( p1 ) < EPSILON )
		return;

	// segment tangent - direction of the last segment
	Vec2f tangent = p0 - mPath.getSegmentPosition( segmentNum - 1, .98f );
	Vec2f n( -tangent.y, tangent.x ); // segment normal

	Vec2f d( p1 - p0 ); // distance of the arc center and the last path point
	d *= .5f;
	Vec2f b( -d.y, d.x ); // arc bisector

	// parallel vectors, p1 lies on the tangent
	float dot = b.dot( n );
	float sqrLength = b.lengthSquared() * n.lengthSquared();
	// does not seem to be a very precise test, hence the .1f limit instead of EPSILON
	if ( math< float >::abs( dot * dot - sqrLength ) < .1f )
	{
		mPath.lineTo( p1 );
		return;
	}

	// the arc center is the intersection of the segment normal and the bisector
	float s;
	if ( n.x == 0.f )
	{
		if ( b.x == 0.f ) // parallel
		{
			mPath.lineTo( p1 );
			return;
		}
		s = -d.x / b.x;
	}
	else
	{
		float den = b.x * n.y / n.x - b.y;
		if ( den == 0.f ) // parallel
		{
			mPath.lineTo( p1 );
			return;
		}
		s = ( d.y - d.x * n.y / n.x ) / ( b.x * n.y / n.x - b.y );
	}
	Vec2f c( ( p0 + p1 ) *.5f + s * b ); // arc center

	Vec2f d0( p0 - c );
	float a0 = math< float >::atan2( d0.y, d0.x );
	Vec2f d1( p1 - c );
	float a1 = math< float >::atan2( d1.y, d1.x );

	// segment normal line and segment bisector distance
	tangent.normalize();
	float C = tangent.dot( p0 );
	float dist = tangent.dot( ( p0 + p1 ) * .5f ) - C;

	// arc direction depends on the quadrant, in which the new point resides
	bool forward = ( s > 0.f ) ^ ( dist < 0.f );
	mPath.arc( c, d0.length(), a0, a1, forward );
}