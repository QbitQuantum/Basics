vector<ossimImageCacheBase::ossimFrameEntryData> ossimImageCacheBase::getIntersectingEntries(const ossimIrect& rect)
{
   vector<ossimFrameEntryData> result;

   // make sure we have the Toc entry to render
   if(!isOpen()) return result;

   ossimIrect imageRect = getImageRectangle();
   if(rect.intersects(imageRect))
   {
      ossimIrect clipRect  = rect.clipToRect(imageRect);
      ossimIrect frameRect(clipRect.ul().x/m_frame_width,
                           clipRect.ul().y/m_frame_height,
                           clipRect.lr().x/m_frame_width,
                           clipRect.lr().y/m_frame_height);

      for(ossim_int32 row = frameRect.ul().y; row <= frameRect.lr().y; ++row)
      {
         for(ossim_int32 col = frameRect.ul().x; col <= frameRect.lr().x; ++col)
         {
            ossimRpfFrameEntry tempEntry = m_frameEntryArray[row][col];
            if(tempEntry.exists())
            {
               result.push_back(ossimFrameEntryData(row,
                                                    col,
                                                    row*m_frame_height,
                                                    col*m_frame_width,
                                                    tempEntry));
            }
         }
      }
   }

   return result;
}