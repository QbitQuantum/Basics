void PxSingleActor::sweepTest( MatrixF *mat )
{
   NxVec3 nxCurrPos = getPosition();

   // If the position is zero, 
   // the parent hasn't been updated yet
   // and we don't even need to do the sweep test.
   // This is a fix for a problem that was happening
   // where on the add of the PxSingleActor, it would
   // set the position to a very small value because it would be getting a hit
   // even though the current position was 0.
   if ( nxCurrPos.isZero() )
      return;
   
   // Set up the flags and the query structure.
   NxU32 flags = NX_SF_STATICS | NX_SF_DYNAMICS;

   NxSweepQueryHit sweepResult;
   dMemset( &sweepResult, 0, sizeof( sweepResult ) );

   NxVec3 nxNewPos = mat->getPosition();

   // Get the velocity which will be our sweep direction and distance.
   NxVec3 nxDir = nxNewPos - nxCurrPos;
   if ( nxDir.isZero() )
      return;

   // Get the scene and do the sweep.
   mActor->wakeUp();
   mActor->linearSweep( nxDir, flags, NULL, 1, &sweepResult, NULL );

   if ( sweepResult.hitShape && sweepResult.t < nxDir.magnitude() )
   {
      nxDir.normalize();
      nxDir *= sweepResult.t;
      nxCurrPos += nxDir;

      mat->setPosition( Point3F( nxCurrPos.x, nxCurrPos.y, nxCurrPos.z ) );
   }
}