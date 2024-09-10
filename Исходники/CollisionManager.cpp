const CollisionResult CollisionManager::test( const Polygon& a, const Polygon& b, const Vector2d& v )
{

	// A place to store our collision result.
	CollisionResult result;
	result.colliding = true;

	// Do a radius test first.
	if ( (a.getPosition()-a.getPosition()).getMagnitude() > (a.getRadius() + a.getRadius()) ){
		result.colliding = false;
		return result;
	}


	// The minimum distance required to separate the two polygons.
	float mintranslation = FLT_MAX;

	// Loop through both polygon's vertices and test them.
	for( unsigned int i = 0; i < a.getVertexCount() + b.getVertexCount(); ++i )
	{
		// Get the edge, polygons are stored as point clouds, so we have to subtract two points to get an edge.
		Vector2d edge;
		if( i < a.getVertexCount() ) edge = a.getVertex( i ) - a.getVertex( i+1 );
		else edge = b.getVertex( i - a.getVertexCount() ) - b.getVertex( i - a.getVertexCount()+1 );

		// Get a perpendicular ( right-hand ) to the edge.
		edge = Vector2d( -edge.getY(), edge.getX() );
		edge.normalize();

		// Project the two polygons onto the edge.
		float minA,maxA,minB,maxB;
		projectPolygon( edge, a, minA, maxA );
		projectPolygon( edge, b, minB, maxB );

		// Get the distance of separation.
		float distance = intervalDistance(minA, maxA, minB, maxB);

		// If the distance is greater than 0, they aren't overlapping, so let's try a velocity.
		if (distance > 0){
			float velocityProjection = edge * v;

			// Get the projection of object A during the movement
			if (velocityProjection < 0)
				minA += velocityProjection;
			else
				maxA += velocityProjection;

			// Do the same as above, but now with velocity projected.
			float distance = intervalDistance(minA, maxA, minB, maxB);

		}

		// If the distance is greater than 0, they aren't overlapping nor will they collide, so break.
		if (distance > 0){
			result.colliding = false;
			break;
		}

		// Check to see if this is the minimum translation so far.
		if( abs(distance) < mintranslation ){
			mintranslation = abs(distance);
			result.separation = edge;
		}

	}

	// Calculate the minimum translation vector if a collision occured.
	if( result.colliding == true ){
		// multiply it by the minimum translation distance.
		result.separation *= mintranslation;
		//make sure it's facing the right way.
		if (result.separation * (a.getPosition() - b.getPosition()) < 0) result.separation = -result.separation;

	}
	
	return result;
}