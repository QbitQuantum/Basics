rspfAnnotationObject* rspfGeoAnnotationGdBitmapFont::getNewClippedObject(const rspfDrect& rect)const
{
   if(intersects(rect))
   {
      if(theProjectedFont.valid())
      {
         return theProjectedFont->getNewClippedObject(rect);
      }
   }
   
   return (rspfAnnotationObject*)0;
}