bool ForestItem::castRay( const Point3F &start, const Point3F &end, RayInfo *outInfo, bool rendered ) const
{
   if ( !mWorldBox.collideLine( start, end ) )
      return false;

   Point3F s, e;
   MatrixF mat = getTransform();
   mat.scale( Point3F(mScale) );
   mat.inverse();

   mat.mulP( start, &s );
   mat.mulP( end, &e );

   TSForestItemData *data = (TSForestItemData*)mDataBlock;
   TSShapeInstance *si = data->getShapeInstance();

   if ( !si ) 
      return false;
   
   if ( rendered )
   {
      // Always raycast against detail level zero
      // because it makes lots of things easier.
      if ( !si->castRayRendered( s, e, outInfo, 0 ) )
         return false;

      if ( outInfo->userData != NULL )
         *(ForestItem*)(outInfo->userData) = *this;

      return true;
   }

   RayInfo shortest;  
   shortest.t = 1e8;
   bool gotMatch = false;
   S32 detail;

   const Vector<S32> &details = data->getLOSDetails();
   for (U32 i = 0; i < details.size(); i++) 
   {
      detail = details[i];
      if (detail != -1) 
      {
         //si->animate(data->mLOSDetails[i]);

         if ( si->castRayOpcode( detail, s, e, outInfo ) )         
         {
            if (outInfo->t < shortest.t)
            {
               gotMatch = true;
               shortest = *outInfo;      
            }
         }
      }
   }

   if ( !gotMatch )
      return false;

   // Copy out the shortest time...
   *outInfo = shortest;

   if ( outInfo->userData != NULL )
      *(ForestItem*)(outInfo->userData) = *this;

   return true;   
}