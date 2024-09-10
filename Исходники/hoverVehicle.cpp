void HoverVehicle::updateDustTrail( F32 dt )
{
    // Check to see if we're moving.

    VectorF velocityVector = getVelocity();
    F32 velocity = velocityVector.len();

    if( velocity > 2.0 )
    {
        velocityVector.normalize();
        emitDust( mDustTrailEmitter, mDataBlock->triggerTrailHeight, mDataBlock->dustTrailOffset,
                  ( U32 )( dt * 1000 * ( velocity / mDataBlock->dustTrailFreqMod ) ),
                  velocityVector );
    }
}