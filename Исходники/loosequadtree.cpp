Model* SpaceTree::QueryRay( const Vector3F& _origin, 
							const Vector3F& _direction, 
							int required, int excluded, const Model** ignore,
							HitTestMethod testType,
							Vector3F* intersection ) 
{
	//GLOUTPUT(( "query ray\n" ));
	modelRoot = 0;
	nodesVisited = 0;
	modelsFound = 0;
	requiredFlags = required;
	excludedFlags = excluded | Model::MODEL_HIDDEN_FROM_TREE;
	++queryID;

	Vector3F dummy;
	if ( !intersection ) {
		intersection = &dummy;
	}

	Vector3F dir = _direction;
	dir.Normalize();

	Rectangle3F aabb;
	aabb.min.Set( 0, yMin, 0 );
	aabb.max.Set( Map::SIZE, yMax, Map::SIZE );

	// Where does this ray enter and leave the spaceTree?
	// It enters at 'p0' and leaves at 'p1'
	int p0Test, p1Test;
	Vector3F p0, p1;
	int test = IntersectRayAllAABB( _origin, dir, aabb, &p0Test, &p0, &p1Test, &p1 );
	if ( test != grinliz::INTERSECT ) {
		// Can click outside of AABB pretty commonly, actually.
		return 0;
	}
	Plane planes[6];
	Rectangle3F rect;
	rect.FromPair( p0, p1 );
	Plane::CreatePlanes( rect, planes );

	Model* modelRoot = Query( planes, 6, required, excluded );

	// We now have a batch of models. Are any of them a hit??
	GLASSERT( testType == TEST_HIT_AABB || testType == TEST_TRI );

	float close = FLT_MAX;
	Model* closeModel = 0;
	Vector3F testInt;
	float t;

	for( Model* root=modelRoot; root; root=root->next ) {
		if ( Ignore( root, ignore ) )
			continue;

		//GLOUTPUT(( "Consider: %s\n", root->GetResource()->header.name ));
		int result = grinliz::REJECT;

		if ( testType == TEST_HIT_AABB ) {
			Rectangle3F modelAABB;

			root->CalcHitAABB( &modelAABB );
			result = IntersectRayAABB( p0, dir, modelAABB, &testInt, &t );
		}
		else if ( testType == TEST_TRI ) {
			t = FLT_MAX;
			result = root->IntersectRay( p0, dir, &testInt );

			if ( result == grinliz::INTERSECT ) {
				Vector3F delta = p0 - testInt;
				t = delta.LengthSquared();
				//GLOUTPUT(( "Hit: %s t=%.2f\n", root->GetResource()->header.name, t ));
			}	
		}

		if ( result == grinliz::INTERSECT ) {
			// Ugly little bug: check for t>=0, else could collide with objects
			// that touch the bounding box but are before the ray starts.
			if ( t >= 0.0f && t < close ) {
				closeModel = root;
				*intersection = testInt;
				close = t;
			}
		}
	}
	if ( closeModel ) {
		return closeModel;
	}
	return 0;
}