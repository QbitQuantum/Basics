rspfAnnotationObject* rspfGeoAnnotationLineObject::getNewClippedObject(const rspfDrect& rect)const
{
   if(intersects(rect))
   {
      if(theProjectedLineObject)
      {
         return theProjectedLineObject->getNewClippedObject(rect);
      }
   }
   
   return (rspfAnnotationObject*)0;
}