DecalInstance* DecalManager::raycast( const Point3F &start, const Point3F &end, bool savedDecalsOnly )
{
   if ( !mData )
      return NULL;

   const Vector<DecalSphere*> &grid = mData->getGrid();

   DecalInstance *inst = NULL;
   SphereF worldSphere( Point3F( 0, 0, 0 ), 1.0f );

   Vector<DecalInstance*> hitDecals;

   for ( U32 i = 0; i < grid.size(); i++ )
   {
      DecalSphere *decalSphere = grid[i];
      if ( !decalSphere->mWorldSphere.intersectsRay( start, end ) )
         continue;

      const Vector<DecalInstance*> &items = decalSphere->mItems;
      for ( U32 n = 0; n < items.size(); n++ )
      {
         inst = items[n];
         if ( !inst )
            continue;

         if ( savedDecalsOnly && !(inst->mFlags & SaveDecal) )
            continue;

         worldSphere.center = inst->mPosition;
         worldSphere.radius = inst->mSize;

         if ( !worldSphere.intersectsRay( start, end ) )
            continue;
			
			RayInfo ri;
			bool containsPoint = false;
			if ( gServerContainer.castRayRendered( start, end, STATIC_COLLISION_MASK, &ri ) )
			{        
				Point2F poly[4];
				poly[0].set( inst->mPosition.x - (inst->mSize / 2), inst->mPosition.y + (inst->mSize / 2));
				poly[1].set( inst->mPosition.x - (inst->mSize / 2), inst->mPosition.y - (inst->mSize / 2));
				poly[2].set( inst->mPosition.x + (inst->mSize / 2), inst->mPosition.y - (inst->mSize / 2));
				poly[3].set( inst->mPosition.x + (inst->mSize / 2), inst->mPosition.y + (inst->mSize / 2));
				
				if ( MathUtils::pointInPolygon( poly, 4, Point2F(ri.point.x, ri.point.y) ) )
					containsPoint = true;
			}

			if( !containsPoint )
				continue;

         hitDecals.push_back( inst );
      }
   }

   if ( hitDecals.empty() )
      return NULL;

   gSortPoint = start;
   dQsort( hitDecals.address(), hitDecals.size(), sizeof(DecalInstance*), cmpDecalDistance );
   return hitDecals[0];
}