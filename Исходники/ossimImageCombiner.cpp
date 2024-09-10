void ossimImageCombiner::getOverlappingImages(std::vector<ossim_uint32>& result,
					      const ossimIrect& rect,
                                              ossim_uint32 resLevel)const
{
   if(theComputeFullResBoundsFlag)
   {
      precomputeBounds();
   }
   double scale = 1.0/std::pow(2.0, (double)resLevel);
   ossimDpt scalar(scale, scale);
   
   ossim_uint32 inputIndex;
   ossimIrect boundingRect;
   for(inputIndex = 0; inputIndex < getNumberOfInputs(); ++inputIndex)
   {
      if(!theFullResBounds[inputIndex].hasNans())
      {
         boundingRect = theFullResBounds[inputIndex]*scalar;
         if(rect.intersects(boundingRect))
         {
            result.push_back(inputIndex);
         }
      }
   }
}