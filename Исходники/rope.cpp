void CanopySimulator::Rope::initialize(NxActor* actor1, NxVec3 anchor1, NxActor* actor2, NxVec3 anchor2)
{
    _nxActor1 = actor1; assert( _nxActor1 );
    _nxActor2 = actor2; assert( _nxActor2 );
    _anchor1 = anchor1;
    _anchor2 = anchor2;

    // calculate worldspace positions for connections points
    Matrix4f ltm1  = wrap( _nxActor1->getGlobalPose() );
    Matrix4f ltm2  = wrap( _nxActor2->getGlobalPose() );
    NxVec3 pos1 = wrap( Gameplay::iEngine->transformCoord( wrap( _anchor1 ), ltm1 ) );
    NxVec3 pos2 = wrap( Gameplay::iEngine->transformCoord( wrap( _anchor2 ), ltm2 ) );
    NxVec3 dir  = pos2 - pos1;

    // check distance btw connection points (correction just for stability purpose)
    float idist = dir.magnitude();
    dir.normalize();

    // create intermediate segment bodies
    NxVec3 pos = pos1;
    float step = idist / _numJoints;
    for( unsigned int i=0; i<_numJoints-1; i++ )
    {
        // segment position
        pos += dir * step;
        // create segment body
        NxBodyDesc nxBodyDesc;
        nxBodyDesc.mass = _mass / ( _numJoints - 1 );
        nxBodyDesc.massSpaceInertia.set( nxBodyDesc.mass, nxBodyDesc.mass, nxBodyDesc.mass );
        nxBodyDesc.linearDamping = 2.0f;
        nxBodyDesc.angularDamping = 0.0f;
        nxBodyDesc.flags = NX_BF_VISUALIZATION;
        nxBodyDesc.solverIterationCount = 32;
        NxActorDesc nxActorDesc;
        nxActorDesc.body = &nxBodyDesc;
        nxActorDesc.globalPose.M.id();
        nxActorDesc.globalPose.t = pos;
        _nxSegmentBody[i] = _nxScene->createActor( nxActorDesc );
        assert( _nxSegmentBody[i] );
        // initialize velocity
        _nxSegmentBody[i]->addForce( _nxActor1->getLinearVelocity(), NX_VELOCITY_CHANGE );
    }

    // create joints
    for( i=0; i<_numJoints; i++ )
    {
        // first joint (actor1-segment1)
        if( i == 0 )
        {
            NxDistanceJointDesc jointDesc;
            jointDesc.actor[0] = _nxActor1;
            jointDesc.actor[1] = _nxSegmentBody[0];
            jointDesc.maxDistance = _length / _numJoints;
            jointDesc.minDistance = 0.0f;
            jointDesc.flags = NX_DJF_MAX_DISTANCE_ENABLED;
            jointDesc.localAnchor[0] = _anchor1;
            jointDesc.localAnchor[1].set( 0,0,0 );
            jointDesc.jointFlags = NX_JF_VISUALIZATION;
            _nxSegmentJoint[i] = _nxScene->createJoint( jointDesc );
            assert( _nxSegmentJoint[i] );
        }
        // last joint (segmentN-actor2)
        else if( i == _numJoints-1 )
        {
            NxDistanceJointDesc jointDesc;
            jointDesc.actor[0] = _nxSegmentBody[_numJoints-2];
            jointDesc.actor[1] = _nxActor2;
            jointDesc.maxDistance = _length / _numJoints;
            jointDesc.minDistance = 0.0f;
            jointDesc.flags = NX_DJF_MAX_DISTANCE_ENABLED;
            jointDesc.localAnchor[0].set( 0,0,0 );
            jointDesc.localAnchor[1] = _anchor2;
            jointDesc.jointFlags = NX_JF_VISUALIZATION;
            _nxSegmentJoint[i] = _nxScene->createJoint( jointDesc );
            assert( _nxSegmentJoint[i] );
        }
        // intermediate joint
        else
        {
            NxDistanceJointDesc jointDesc;
            jointDesc.actor[0] = _nxSegmentBody[i-1];
            jointDesc.actor[1] = _nxSegmentBody[i];
            jointDesc.maxDistance = _length / _numJoints;
            jointDesc.minDistance = 0.0f;
            jointDesc.flags = NX_DJF_MAX_DISTANCE_ENABLED;
            jointDesc.localAnchor[0].set( 0,0,0 );
            jointDesc.localAnchor[1].set( 0,0,0 );
            jointDesc.jointFlags = NX_JF_VISUALIZATION;
            _nxSegmentJoint[i] = _nxScene->createJoint( jointDesc );
            assert( _nxSegmentJoint[i] );
        }
    }
}