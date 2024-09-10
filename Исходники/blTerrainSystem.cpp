void blTerrainProxy::lightVector(LightInfo * light)
{
   // Grab our terrain object
   TerrainBlock* terrain = getObject();
   if (!terrain)
      return;

   // Get the direction to the light (the inverse of the direction
   // the light is pointing)
   Point3F lightDir = -light->getDirection();
   lightDir.normalize();

   // Get the ratio between the light map pixel and world space (used below)   
   F32 lmTerrRatio = (F32)mTerrainBlockSize / (F32) mLightMapSize;
   lmTerrRatio *= terrain->getSquareSize();

   // Get the terrain position
   Point3F terrPos( terrain->getTransform().getPosition() );

   U32 i = 0;
   for (U32 y = 0; y < mLightMapSize; y++)
   {
      for (U32 x = 0; x < mLightMapSize; x++)
      {
         // Get the relative pixel position and scale it
         // by the ratio between lightmap and world space
         Point2F pixelPos(x, y);
         pixelPos *= lmTerrRatio;         
         
         // Start with a default normal of straight up
         Point3F normal(0.0f, 0.0f, 1.0f);
         
         // Try to get the actual normal from the terrain.
         // Note: this won't change the default normal if
         // it can't find a normal.
         terrain->getNormal(pixelPos, &normal);

         // The terrain lightmap only contains shadows.
         F32 shadowed = 0.0f;

         // Get the height at the lightmap pixel's position
         F32 height = 0.0f;
         terrain->getHeight(pixelPos, &height);

         // Calculate the 3D position of the pixel
         Point3F pixelPos3F(pixelPos.x, pixelPos.y, height);

         // Translate that position by the terrain's transform
         terrain->getTransform().mulP(pixelPos3F);

         // Offset slighting along the normal so that we don't
         // raycast into ourself
         pixelPos3F += (normal * 0.1f);

         // Calculate the light's position.
         // If it is a vector light like the sun (no position
         // just direction) then translate along that direction
         // a reasonable distance to get a point sufficiently
         // far away
         Point3F lightPos = light->getPosition();
         if(light->getType() == LightInfo::Vector)
         {
            lightPos = 1000.f * lightDir;            
            lightPos = pixelPos3F + lightPos;
         }

         // Cast a ray from the world space position of the lightmap pixel to the light source.
         // If we hit something then we are in shadow. This allows us to be shadowed by anything
         // that supports a castRay operation.
         RayInfo info;
         if(terrain->getContainer()->castRay(pixelPos3F, lightPos, STATIC_COLLISION_TYPEMASK, &info))
         {
            // Shadow the pixel.
            shadowed = 1.0f;
         }

         // Set the final lightmap color.
         mLightmap[i++] += ColorF::WHITE * mClampF( 1.0f - shadowed, 0.0f, 1.0f );
      }
   }
}