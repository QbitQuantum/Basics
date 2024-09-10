ossimRefPtr<ossimImageData> ossimKakaduJ2kReader::getTile(
   const ossimIrect& rect, ossim_uint32 resLevel)
{
   // This tile source bypassed, or invalid res level, return a blank tile.
   if(!isSourceEnabled() || !isOpen() || !isValidRLevel(resLevel))
   {
      return ossimRefPtr<ossimImageData>();
   }

   if (theTile.valid())
   {
      // Rectangle must be set prior to getOverviewTile call.
      theTile->setImageRectangle(rect);

      if (resLevel)
      {
         if ( getOverviewTile(resLevel, theTile.get() ) == false )
         {
            theTile->makeBlank();
         }
      }
      else
      {
         //---
         // See if the whole tile is going to be filled, if not, start out with
         // a blank tile so data from a previous load gets wiped out.
         //---
         if ( !rect.completely_within(theImageRect) )
         {
            // Start with a blank tile.
            theTile->makeBlank();
         }
         
         //---
         // See if any point of the requested tile is in the image.
         //---
         if ( rect.intersects(theImageRect) )
         {
            ossimIrect clipRect = rect.clipToRect(theImageRect);

            ossimIrect exandedRect  = clipRect;

            //---
            // Shift the upper left corner of the "clip_rect" to the an even
            // j2k tile boundry.  
            //---
            exandedRect.stretchToTileBoundary(ossimIpt(theTileSizeX,
                                                       theTileSizeY));
            
            // Vertical tile loop.
            ossim_int32 y = exandedRect.ul().y;
            while (y < exandedRect.lr().y)
            {
               // Horizontal tile loop.
               ossim_int32 x = exandedRect.ul().x;
               while (x < exandedRect.lr().x)
               {
                  if ( loadTileFromCache(x, y, clipRect) == false )
                  {
                     if ( loadTile(x, y) )
                     {
                        //---
                        // Note: Clip the cache tile to the image clipRect
                        // since there are j2k tiles that go beyond the image
                        // dimensions, i.e., edge tiles.
                        //---    
                        ossimIrect cr =
                           theCacheTile->getImageRectangle().
                           clipToRect(clipRect);
                        
                        theTile->loadTile(theCacheTile->getBuf(),
                                          theCacheTile->getImageRectangle(),
                                          cr,
                                          OSSIM_BSQ);
                     }
                     
                  }
                  
                  x += theTileSizeX; // Go to next tile.
               }
               
               y += theTileSizeY; // Go to next row of tiles.
            }

            // Set the tile status.
            theTile->validate();
            
         } // matches: if ( rect.intersects(theImageRect) )
         
      } // r0 block
      
   } // matches: if (theTile.valid())

   return theTile;
}