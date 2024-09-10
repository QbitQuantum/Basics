// Used to build potential target list
static void _scanCallback( SceneObject* object, void* data )
{
   AITurretShape* turret = (AITurretShape*)data;

   ShapeBase* shape = dynamic_cast<ShapeBase*>(object);
   if (shape && shape->getDamageState() == ShapeBase::Enabled)
   {
      Point3F targetPos = shape->getBoxCenter();

      // Put target position into the scan node's space
      turret->mScanWorkspaceScanWorldMat.mulP(targetPos);

      // Is the target within scanning distance
      if (targetPos.lenSquared() > turret->getMaxScanDistanceSquared())
         return;

      // Make sure the target is in front and within the maximum
      // heading range
      Point2F targetXY(targetPos.x, targetPos.y);
      targetXY.normalizeSafe();
      F32 headingDot = mDot(Point2F(0, 1), targetXY);
      F32 heading = mAcos(headingDot);
      if (headingDot < 0 || heading > turret->getMaxScanHeading())
         return;

      // Make sure the target is in front and within the maximum
      // pitch range
      Point2F targetZY(targetPos.z, targetPos.y);
      targetZY.normalizeSafe();
      F32 pitchDot = mDot(Point2F(0, 1), targetZY);
      F32 pitch = mAcos(pitchDot);
      if (pitchDot < 0 || pitch > turret->getMaxScanPitch())
         return;

      turret->addPotentialTarget(shape);
   }
}