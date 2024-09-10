void ClipMap::calculateClipMapLevels(const F32 near, const F32 far, 
                                          const RectF &texBounds, 
                                          S32 &outStartLevel, S32 &outEndLevel)
{
   PROFILE_START(ClipMap_calculateClipMapLevels);

   // We also have to deal w/ the available data. So let's figure out if our
   // desired TCs are in the loaded textureset.

   // Adjust the specified TC range into a texel range.
   F32 ftexsize = F32(mTextureSize);
   RectF tcR(Point2F(texBounds.point.y * ftexsize, texBounds.point.x * ftexsize), ftexsize * texBounds.extent);

   // If we're tiling, make sure we're only insetting away from the clipmap bounds.
   // This avoids making bad LOD selections at clipmap boundaries.
   // Note: compress several compares into one since a*b=0 iff a==0 or b==0
   bool doInset = true;//mTile || (tcR.point.x * tcR.point.y * (tcR.extent.x+tcR.point.x-mTextureSize) * (tcR.extent.y+tcR.point.y-mTextureSize) != 0); 

   if(doInset)
      tcR.inset(-1, -1);

   // Put some safe defaults in for starters.
   outEndLevel   = mClipStackDepth-1;
   outStartLevel = getMax(outEndLevel-3, S32(0));

   // Now iterate over every clipstack entry and find the smallest that contains
   // the relevant TCs.
   S32 minLevelOverlap = mClipStackDepth - 1;
   S32 maxLevelOverlap = mClipStackDepth - 1;

   for(S32 i=mClipStackDepth-2; i>=0; i--)
   {
      // Find region for entry at this level.
      RectF r;
      F32 biti = F32(BIT(i));
      F32 biticms = F32(BIT(i) * mClipMapSize);
      r.point = Point2F(
         biti * mLevels[i].mToroidalOffset.x, 
         biti * mLevels[i].mToroidalOffset.y);
      r.extent.set(biticms,biticms);

      // Is our tex region fully contained?
      if(r.contains(tcR))
      {
         // If we're fully contained, then this is our new max.
         maxLevelOverlap = i;
         minLevelOverlap = i;
         continue;
      }

      // Or else maybe we've got overlap?
      if (!r.overlaps(tcR))
         break;

      // If we're overlapping then this is our new min...
      minLevelOverlap = getMin(minLevelOverlap, i);
   }

   // Given our level range, do a best fit. We ALWAYS have to have
   // enough for the minimum detail, so we fit that constraint then
   // do our best to give additional detail on top of that.

   // bias the minimum detail to allow smooth transitions to work properly,
   // this avoids a LOT of texture popping.
   maxLevelOverlap++;

   outEndLevel   = mClamp(maxLevelOverlap, 0, mClipStackDepth-1);
   outStartLevel = mClamp(minLevelOverlap, outEndLevel - 3, outEndLevel - 1);

   // Make sure we're not exceeding our max delta.
   const S32 delta = outEndLevel - outStartLevel;
   AssertFatal(delta >= 1 && delta <= 4, 
      "ClipMap::calculateClipMapLevels - range in levels outside of 2..4 range!");

   PROFILE_END();
}