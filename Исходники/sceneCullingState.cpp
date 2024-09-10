bool SceneCullingState::isOccludedByTerrain( SceneObject* object ) const
{
   PROFILE_SCOPE( SceneCullingState_isOccludedByTerrain );

   // Don't try to occlude globally bounded objects.
   if( object->isGlobalBounds() )
      return false;

   const Vector< SceneObject* >& terrains = getSceneManager()->getContainer()->getTerrains();
   const U32 numTerrains = terrains.size();

   for( U32 terrainIdx = 0; terrainIdx < numTerrains; ++ terrainIdx )
   {
      TerrainBlock* terrain = dynamic_cast< TerrainBlock* >( terrains[ terrainIdx ] );
      if( !terrain )
         continue;

      MatrixF terrWorldTransform = terrain->getWorldTransform();

      Point3F localCamPos = getCameraState().getViewPosition();
      terrWorldTransform.mulP(localCamPos);
      F32 height;
      terrain->getHeight( Point2F( localCamPos.x, localCamPos.y ), &height );
      bool aboveTerrain = ( height <= localCamPos.z );

      // Don't occlude if we're below the terrain.  This prevents problems when
      //  looking out from underground bases...
      if( !aboveTerrain )
         continue;

      const Box3F& oBox = object->getObjBox();
      F32 minSide = getMin(oBox.len_x(), oBox.len_y());
      if (minSide > 85.0f)
         continue;

      const Box3F& rBox = object->getWorldBox();
      Point3F ul(rBox.minExtents.x, rBox.minExtents.y, rBox.maxExtents.z);
      Point3F ur(rBox.minExtents.x, rBox.maxExtents.y, rBox.maxExtents.z);
      Point3F ll(rBox.maxExtents.x, rBox.minExtents.y, rBox.maxExtents.z);
      Point3F lr(rBox.maxExtents.x, rBox.maxExtents.y, rBox.maxExtents.z);

      terrWorldTransform.mulP(ul);
      terrWorldTransform.mulP(ur);
      terrWorldTransform.mulP(ll);
      terrWorldTransform.mulP(lr);

      Point3F xBaseL0_s = ul - localCamPos;
      Point3F xBaseL0_e = lr - localCamPos;
      Point3F xBaseL1_s = ur - localCamPos;
      Point3F xBaseL1_e = ll - localCamPos;

      static F32 checkPoints[3] = {0.75, 0.5, 0.25};
      RayInfo rinfo;
      for( U32 i = 0; i < 3; i ++ )
      {
         Point3F start = (xBaseL0_s * checkPoints[i]) + localCamPos;
         Point3F end   = (xBaseL0_e * checkPoints[i]) + localCamPos;

         if (terrain->castRay(start, end, &rinfo))
            continue;

         terrain->getHeight(Point2F(start.x, start.y), &height);
         if ((height <= start.z) == aboveTerrain)
            continue;

         start = (xBaseL1_s * checkPoints[i]) + localCamPos;
         end   = (xBaseL1_e * checkPoints[i]) + localCamPos;

         if (terrain->castRay(start, end, &rinfo))
            continue;

         Point3F test = (start + end) * 0.5;
         if (terrain->castRay(localCamPos, test, &rinfo) == false)
            continue;

         return true;
      }
   }

   return false;
}