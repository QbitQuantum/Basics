void ossimQtScrollingImageWidget::convertRequest(const ossimIrect& reqRect)
{
   if(theRgbChain->getInput())
   {
      QImage tempImage(theTileSize.x,
                       theTileSize.y,
                       32);
      tempImage.fill(0);
      ossimIrect shiftedCacheRect = theBackingStoreCache.getCacheRect() - theShiftToZeroZero;
      ossimIrect tempRect = getAbsoluteViewportRect();
      
      tempImage.setOffset(QPoint(theShiftToZeroZero.x + reqRect.ul().x,
                                 theShiftToZeroZero.y + reqRect.ul().y));
      
      if(reqRect.intersects(shiftedCacheRect))
      {
         if(reqRect.intersects(theBoundingRect))
         {
            ossimRefPtr<ossimImageData> data = getTile(reqRect);
            
            if(data.valid() && data->getBuf() &&
               (data->getDataObjectStatus()!=OSSIM_EMPTY))
            {
               fillImage(data, &tempImage);
            }
         }
      }
      else
      {
         return;
      }
      theBackingStoreCache.addTile(tempImage);
      ossimIrect viewClip = reqRect.clipToRect(tempRect);
      viewClip  = viewClip + theShiftToZeroZero;
      int xLoc  = viewClip.ul().x;
      int yLoc  = viewClip.ul().y;
      int xSize = theTileSize.x;
      int ySize = theTileSize.y;
      eraseCursor();
      repaintContents(xLoc, yLoc, xSize, ySize, false);
   }
}