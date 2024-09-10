ossimRefPtr<ossimImageData> ossimMrSidReader::getTile(
   const ossimIrect& rect, ossim_uint32 resLevel)
{
   LT_STATUS sts = LT_STS_Uninit;

   // This tile source bypassed, or invalid res level, return null tile.
   if(!isSourceEnabled() || !isOpen() || !isValidRLevel(resLevel))
   {
      return ossimRefPtr<ossimImageData>();
   }

   ossimIrect imageBound = getBoundingRect(resLevel);
   if(!rect.intersects(imageBound))
   {
      return ossimRefPtr<ossimImageData>();
   }

   // Check for overview.
   if( resLevel > theMinDwtLevels )
   {
      if(theOverview.valid())
      {
         ossimRefPtr<ossimImageData> tileData = theOverview->getTile(rect, resLevel);
         tileData->setScalarType(getOutputScalarType());
         return tileData;
      }
   }

   theTile->setImageRectangle(rect);

   // Compute clip rectangle with respect to the image bounds.
   ossimIrect clipRect   = rect.clipToRect(imageBound);

   if (rect.completely_within(clipRect) == false)
   {
      // Not filling whole tile so blank it out first.
      theTile->makeBlank();
   }

   lt_uint16 anOssimBandIndex = 0;

   LTIPixel pixel(theReader->getColorSpace(), theNumberOfBands, theReader->getDataType());
   LTISceneBuffer sceneBuffer(pixel, clipRect.width(), clipRect.height(), NULL);

   if (!theGeometry.valid())
   {
      theGeometry = getImageGeometry();
   }
   double mag = theGeometry->decimationFactor(resLevel).lat;
   sts = theImageNavigator->setSceneAsULWH(clipRect.ul().x,
                                           clipRect.ul().y,
                                           clipRect.lr().x - clipRect.ul().x + 1,
                                           clipRect.lr().y - clipRect.ul().y + 1, mag);

   LTIScene scene = theImageNavigator->getScene();
   sts = theReader->read(scene, sceneBuffer);

   if (LT_SUCCESS(sts) == true)
   {
      for(anOssimBandIndex = 0; anOssimBandIndex < theNumberOfBands; anOssimBandIndex++)
      {
         theTile->loadBand(sceneBuffer.getTotalBandData(anOssimBandIndex),
                           clipRect, anOssimBandIndex);
      }
   }

   theTile->validate();
   return theTile;
}