void BrushAdjustHeightAction::process(Selection * sel, const Gui3DMouseEvent & event, bool, Type type)
{
   if(type == Process)
      return;

   TerrainBlock *terrBlock = mTerrainEditor->getActiveTerrain();
   if ( !terrBlock )
      return;

   if(type == Begin)
   {
      mTerrainEditor->lockSelection(true);
      mTerrainEditor->getRoot()->mouseLock(mTerrainEditor);

      // the way this works is:
      // construct a plane that goes through the collision point
      // with one axis up the terrain Z, and horizontally parallel to the
      // plane of projection

      // the cross of the camera ffdv and the terrain up vector produces
      // the cross plane vector.

      // all subsequent mouse actions are collided against the plane and the deltaZ
      // from the previous position is used to delta the selection up and down.
      Point3F cameraDir;

      EditTSCtrl::smCamMatrix.getColumn(1, &cameraDir);
      terrBlock->getTransform().getColumn(2, &mTerrainUpVector);

      // ok, get the cross vector for the plane:
      Point3F planeCross;
      mCross(cameraDir, mTerrainUpVector, &planeCross);

      planeCross.normalize();
      Point3F planeNormal;

      Point3F intersectPoint;
      mTerrainEditor->collide(event, intersectPoint);

      mCross(mTerrainUpVector, planeCross, &planeNormal);
      mIntersectionPlane.set(intersectPoint, planeNormal);

      // ok, we have the intersection point...
      // project the collision point onto the up vector of the terrain

      mPreviousZ = mDot(mTerrainUpVector, intersectPoint);

      // add to undo
      // and record the starting heights
      for(U32 i = 0; i < sel->size(); i++)
      {
         mTerrainEditor->getUndoSel()->add((*sel)[i]);
         (*sel)[i].mStartHeight = (*sel)[i].mHeight;
      }
   }
   else if(type == Update)
   {
      // ok, collide the ray from the event with the intersection plane:

      Point3F intersectPoint;
      Point3F start = event.pos;
      Point3F end = start + event.vec * 1000;

      F32 t = mIntersectionPlane.intersect(start, end);

      m_point3F_interpolate( start, end, t, intersectPoint);
      F32 currentZ = mDot(mTerrainUpVector, intersectPoint);

      F32 diff = currentZ - mPreviousZ;

      for(U32 i = 0; i < sel->size(); i++)
      {
         (*sel)[i].mHeight = (*sel)[i].mStartHeight + diff * (*sel)[i].mWeight;

         // clamp it
         if((*sel)[i].mHeight < 0.f)
            (*sel)[i].mHeight = 0.f;
         if((*sel)[i].mHeight > 2047.f)
            (*sel)[i].mHeight = 2047.f;

         mTerrainEditor->setGridInfoHeight((*sel)[i]);
      }
      mTerrainEditor->scheduleGridUpdate();
   }
   else if(type == End)
   {
      mTerrainEditor->getRoot()->mouseUnlock(mTerrainEditor);
   }
}