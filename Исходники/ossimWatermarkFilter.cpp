ossimRefPtr<ossimImageData> ossimWatermarkFilter::getTile(
   const ossimIrect& tile_rect, ossim_uint32 resLevel)
{
   // Lock for the length of this method.
   // Check for input.
   if (!theInputConnection)
   {
      if (theTile.valid())
      {
         theTile->setImageRectangle(tile_rect);
         theTile->makeBlank();
      }
      return theTile;
   }

   // Fetch a tile from from the input source.
   ossimRefPtr<ossimImageData> inputTile =
      theInputConnection->getTile(tile_rect, resLevel);

   // Check for bypass.
   if (theEnableFlag == false) return inputTile;

   // Check for weight being 0.0.
   if (theWatermarkWeight == 0.0) return inputTile;

   //---
   // Check for dirty state.
   // Note: This is set in initialize if something changes.
   //---
   if (theDirtyFlag == true)
   {
      if (allocate() == false) // Something not right if false.
      {
         return inputTile;
      }
   }   
   
   // We will only watermark (process) within the input bounding rectangle.
   if (tile_rect.intersects(theInputBoundingRect) == false)
   {
      return inputTile;
   }

   // Capture the rectangle and blank out theTile.
   theTile->setImageRectangle(tile_rect);

   if (inputTile.valid() &&
       (inputTile->getDataObjectStatus() != OSSIM_NULL))
   {
      // Copy the inputTile to theTile.
      theTile->loadTile(inputTile.get());
   }
   else 
   {
      theTile->makeBlank();
   }

   // Write the watermarks...
   switch(theTile->getScalarType())
   {
      case OSSIM_UINT8:
      {
         fill(ossim_uint8(0));
         break;
      }
      case OSSIM_SINT8:
      {
         fill(ossim_sint8(0));
         break;
      }
      case OSSIM_USHORT11:
      case OSSIM_UINT16:
      {
         fill(ossim_uint16(0));
         break;
      }
      case OSSIM_SINT16:
      {
         fill(ossim_sint16(0));
         break;
      }
      case OSSIM_UINT32:
      {
         fill(ossim_uint32(0));
         break;
      }
      case OSSIM_SINT32:
      {
         fill(ossim_sint32(0));
         break;
      }
      case OSSIM_FLOAT32: 
      case OSSIM_NORMALIZED_FLOAT:
      {
         fill(ossim_float32(0));
         break;
      }
      case OSSIM_FLOAT64: 
      case OSSIM_NORMALIZED_DOUBLE:
      {
         fill(ossim_float32(0));
         break;
      }
      case OSSIM_SCALAR_UNKNOWN:
      default:
      {
         ossimNotify(ossimNotifyLevel_WARN)
            << "Scalar type = " << theTile->getScalarType()
            << " Not supported by ossimWatermarkFilter" << std::endl;
         return inputTile;
      }
   }

   return theTile;
}