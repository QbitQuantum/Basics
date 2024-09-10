btVector3 btKinematicCharacterController::stepUp( btCollisionWorld* world, const btVector3& currentPosition, btScalar& currentStepOffset )
{
    btVector3 targetPosition = currentPosition + getUpAxisDirections()[ m_upAxis ] * ( m_stepHeight + ( m_verticalOffset > btScalar( 0.0 ) ? m_verticalOffset : 0.0 ) );

    //if the no collisions mode is on, no need to go any further
    if(!mCollision)
    {
        currentStepOffset = m_stepHeight;
        return targetPosition;
    }

    // Retrieve the collision shape
    //
    btCollisionShape* collisionShape = externalGhostObject->getCollisionShape();
    btAssert( collisionShape->isConvex() );

    btConvexShape* convexShape = ( btConvexShape* )collisionShape;

    // FIXME: Handle penetration properly
    //
    btTransform start;
    start.setIdentity();
    start.setOrigin( currentPosition + getUpAxisDirections()[ m_upAxis ] * ( convexShape->getMargin() ) );

    btTransform end;
    end.setIdentity();
    end.setOrigin( targetPosition );

    btKinematicClosestNotMeConvexResultCallback callback( externalGhostObject, -getUpAxisDirections()[ m_upAxis ], m_maxSlopeCosine );
    callback.m_collisionFilterGroup = externalGhostObject->getBroadphaseHandle()->m_collisionFilterGroup;
    callback.m_collisionFilterMask = externalGhostObject->getBroadphaseHandle()->m_collisionFilterMask;

    // Sweep test
    //
    if( m_useGhostObjectSweepTest )
        externalGhostObject->convexSweepTest( convexShape, start, end, callback, world->getDispatchInfo().m_allowedCcdPenetration );

    else
        world->convexSweepTest( convexShape, start, end, callback );

    if( callback.hasHit() )
    {
        // Only modify the position if the hit was a slope and not a wall or ceiling.
        //
        if( callback.m_hitNormalWorld.dot(getUpAxisDirections()[m_upAxis]) > btScalar( 0.0 ) )
        {
            // We moved up only a fraction of the step height
            //
            currentStepOffset = m_stepHeight * callback.m_closestHitFraction;

            return currentPosition.lerp( targetPosition, callback.m_closestHitFraction );
        }

        m_verticalVelocity = btScalar( 0.0 );
        m_verticalOffset = btScalar( 0.0 );

        return currentPosition;
    }
    else
    {
        currentStepOffset = m_stepHeight;
        return targetPosition;
    }
}