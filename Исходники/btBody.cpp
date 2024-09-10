void BtBody::applyImpulse( const Point3F &origin, const Point3F &force )
{
   AssertFatal( mActor, "BtBody::applyImpulse - The actor is null!" );
   AssertFatal( isDynamic(), "BtBody::applyImpulse - This call is only for dynamics!" );

   // Convert the world position to local
   MatrixF trans = btCast<MatrixF>( mActor->getCenterOfMassTransform() );
   trans.inverse();
   Point3F localOrigin( origin );
   trans.mulP( localOrigin );

   if ( mCenterOfMass )
   {
      Point3F relOrigin( localOrigin );
      mCenterOfMass->mulP( relOrigin );
      Point3F relForce( force );
      mCenterOfMass->mulV( relForce );
      mActor->applyImpulse( btCast<btVector3>( relForce ), btCast<btVector3>( relOrigin ) );
   }
   else
      mActor->applyImpulse( btCast<btVector3>( force ), btCast<btVector3>( localOrigin ) );

   if ( !mActor->isActive() )
      mActor->activate();
}