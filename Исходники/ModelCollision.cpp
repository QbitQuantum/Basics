Vector3f SlideMove(
		const Vector3f & footPos,
		const float eyeHeight,
		const Vector3f & moveDirection,
		const float moveDistance,
		const CollisionModel & collisionModel,
		const CollisionModel & groundCollisionModel
	    )
{
	// Check for collisions at eye level to prevent slipping under walls.
	Vector3f eyePos = footPos + UpVector * eyeHeight;

	// Pop out of any collision models.
	collisionModel.PopOut( eyePos );

	{
		Planef fowardCollisionPlane;
		float forwardDistance = moveDistance;
		if ( !collisionModel.TestRay( eyePos, moveDirection, forwardDistance, &fowardCollisionPlane ) )
		{
			// No collision, move the full distance.
			eyePos += moveDirection * moveDistance;
		}
		else
		{
			// Move up to the point of collision.
			eyePos += moveDirection * forwardDistance;

			// Project the remaining movement onto the collision plane.
			const float COLLISION_BOUNCE = 0.001f;	// don't creep into the plane due to floating-point rounding
			const float intoPlane = moveDirection.Dot( fowardCollisionPlane.N ) - COLLISION_BOUNCE;
			const Vector3f slideDirection = ( moveDirection - fowardCollisionPlane.N * intoPlane );

			// Try to finish the move by sliding along the collision plane.
			float slideDistance = moveDistance;
			collisionModel.TestRay( eyePos - UpVector * RailHeight, slideDirection, slideDistance, NULL );

			eyePos += slideDirection * slideDistance;
		}
	}

	if ( groundCollisionModel.Polytopes.GetSizeI() != 0 )
	{
		// Check for collisions at foot level, which allows following terrain.
		float downDistance = 10.0f;
		groundCollisionModel.TestRay( eyePos, - UpVector, downDistance, NULL );

		// Maintain the minimum camera height.
		if ( eyeHeight - downDistance < 1.0f )
		{
			eyePos += UpVector * ( eyeHeight - downDistance );
		}
	}

	return eyePos - UpVector * eyeHeight;
}